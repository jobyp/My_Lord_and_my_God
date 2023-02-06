// JMJ

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// open()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// close()
#include <unistd.h>

#define log(msg) { \
        printf("[%s:%d] %s\n", __FILE__, __LINE__, (msg)); \
        } while (0)

#define err(fn_name, msg) { \
        int err_num = errno; \
        fprintf(stderr, "[%s:%d] %s\n", __FILE__, __LINE__, (msg)); \
        errno = err_num; \
        perror((fn_name)); \
        } while (0)

#define BUFFER_LEN 1024


size_t read_from_fd(int fd, char buf[], size_t len, int *error_code);
size_t write_to_fd(int fd, char buf[], size_t len, int *error_code);


int main(int argc, char *argv[])
{
        const char *filename = "test_file";
        int fd = -1;
        int ret = EXIT_SUCCESS;
        char buf[BUFFER_LEN + 1];  // for '\0'

        filename = (argc == 2) ? argv[1] : filename;
        fd = open(filename, O_RDWR|O_APPEND);
        if (fd == -1)
        {
                err("open()", "failed to open file");
                ret = EXIT_FAILURE;
                goto cleanup;
        }

        log("Ok, we have an open file!");


        /*
          Ok, we might have hit EOF, in which case ret == 0.
          Or, we got EGAIN/EWOULDBLOCK (recoverrable error),
          or a more serious error (irrecoverable).

          Caller of read_from_fd() should examine the return value
          from this function and distinguish all 4 cases, plus
          usage error.
          -> read > 0 bytes       ret == +ve
          -> reached EOF          ret == 0
          -> recoverable error    ret == -1
          -> usage error          ret == -2
          -> irrecoverable error  ret == -3

          But errno is lost, so we propogate the 5 conditions
          in return code "ret".
         */


        while (true)
        {
                size_t ret = 0;
                size_t len = 0;
                int error_code = 0;

                memset(buf, '\0', sizeof(buf));
                ret = read_from_fd(fd, buf, BUFFER_LEN, &error_code);
                if (ret == 0)
                {
                        /*
                          check the error code, and if it's a
                          non-recoverable error code break out of the
                          loop.
                        */
                        break;
                }


                // Ok, we have len (> 0) bytes to write
                len = ret;
                error_code = 0;
                while ((len != 0) &&
                       (ret = write_to_fd(STDOUT_FILENO, buf, len,
                                         &error_code)) != 0)
                {
                        len -= ret;
                        but += ret;
                        /*
                          check the error code, and if it's a
                          non-recoverable error code break out of the
                          loop.
                         */

                        if (error_code == -2)
                        {
                                break;
                        }

                        error_code = 0;
                }

        }

        if (close(fd) == -1)
        {
                err("close()", "failed to close file");
                ret = EXIT_FAILURE;
        }

        log("And we closed the file!");

cleanup:
        exit(ret);
}


size_t read_from_fd(int fd, char buf[], size_t len, int *error_code)
{
        ssize_t ret = 0;
        size_t orig_len = 0;

        if (len == 0 || buf == NULL)
        {
                /*
                   function caller didn't give us enough buffer space.

                   A call to read() with len == 0, will return
                   immediately with a value of 0. Nevertheless, it's
                   a usage error to call read_from_fd with len == 0.
                 */

                fprintf(stderr, "[%s:%d] Cannot read into empty buf\n",
                        __FILE__, __LINE__);
                ret = -2;  // usage error
                goto cleanup;
        }

        if (len > SSIZE_MAX)
        {
                // reset len to SSIZE_MAX
                len = SSIZE_MAX;
        }

        orig_len = len;

        while (len != 0 && (ret = read(fd, buf, len)) != 0)
        {
                if (ret < 0)
                {
                        if (errno == EINTR)
                        {
                                continue;
                        }
                        else if (errno == EAGAIN ||
                                 errno == EWOULDBLOCK)
                        {
                                // resubmit later (recoverable error)
                                ret = -1;
                                break;
                        }
                        else
                        {
                                err("read()", "read failed!");
                                // irrecoverable error
                                ret = -3;
                                break;
                        }
                }

                // else (ret > 0)
                buf += (size_t)ret;
                len -= (size_t)ret;
        }


        if (orig_len > len)
        {
                // Ok, so we read some bytes.
                ret = (ssize_t)(orig_len - len);
                return ret;
        }

        /*
          Ok, we might have hit EOF, in which case ret == 0.
          Or, we got EGAIN/EWOULDBLOCK (recoverrable error),
          or a more serious error (irrecoverable).

          Caller of read_from_fd() should examine the return value
          from this function and distinguish all 4 cases, plus
          usage error.
          -> read > 0 bytes       ret == +ve
          -> reached EOF          ret == 0
          -> recoverable error    ret == -1
          -> usage error          ret == -2
          -> irrecoverable error  ret == -3

          But errno is lost, so we propogate the 5 conditions
          in return code "ret".
         */

cleanup:
        assert(ret <= 0);
        return ret;
}


size_t write_to_fd(int fd, char buf[], size_t len, int *error_code)
{
        ssize_t ret = 0;
        size_t orig_len = 0;

        if (len == 0 || buf == NULL)
        {
                fprintf(stderr,
                        "[%s:%d] Cannot proceed. Empty buffer.\n",
                        __FILE__, __LINE__);
                        ret = -1;
                        goto cleanup;
        }

        if (len > SSIZE_MAX)
        {
                len = SSIZE_MAX;
        }

        orig_len = len;

        while (len != 0 && (ret = write(fd, buf, len)) != 0)
        {
                if (ret == -1)
                {
                        if (errno == EINTR)
                        {
                                continue;
                        }
                        else if (errno == EAGAIN ||
                                 errno == EWOULDBLOCK)
                        {
                                break;
                        }
                        else
                        {
                                err("write()", "write failed");
                                break;
                        }
                }

                // Ok, ret > 0
                buf += (size_t)ret;
                len -= (size_t)ret;
        }

        /*
          Different cases to consider
          1. Successful write
          2. Partial write (non-zero)
             -> returned due to EAGAIN or EWOULDBLOCK
             -> returned due to irrecoverable error
          3. Wrote 0 bytes
             -> returned due to EAGAIN or EWOULDBLOCK
             -> returned due to irrecoverable error

          CHECKME: We need to propogate these conditions to the caller.
         */

        if (orig_len > len)
        {
                ret = (ssize_t)(orig_len - len);
                return ret;
        }

cleanup:
        assert (ret <= 0);
        return ret;
}

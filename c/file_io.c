// JMJ

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

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


ssize_t read_from_fd(int fd, char buf[], size_t len);


int main(int argc, char *argv[])
{
        const char *filename = "test_file";
        int fd = -1;
        int ret = EXIT_SUCCESS;

        filename = (argc == 2) ? argv[1] : filename;
        fd = open(filename, O_RDWR|O_APPEND);
        if (fd == -1)
        {
                err("open()", "failed to open file");
                ret = EXIT_FAILURE;
                goto cleanup;
        }

        log("Ok, we have an open file!");

        if (close(fd) == -1)
        {
                err("close()", "failed to close file");
                ret = EXIT_FAILURE;
        }

        log("And we closed the file!");

cleanup:
        exit(ret);
}


ssize_t read_from_fd(int fd, char buf[], size_t len)
{
        ssize_t ret = 0;
        size_t orig_len = len;

        if (len == 0)
        {
                fprintf(stderr, "[%s:%d] Cannot read into empty buf\n",
                        __FILE__, __LINE__);
                return -1;
        }

        while (len != 0 && (ret = read(fd, buf, len)) != 0)
        {
                if (ret < 0)
                {
                        if (errno == EINTR)
                        {
                                continue;
                        }
                        else if (errno == EAGAIN || errno == EWOULDBLOCK)
                        {
                                // resubmit later
                                break;
                        }
                        else
                        {
                                err("read()", "read failed!");
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
                return (ssize_t)(orig_len - len);
        }

        assert(ret <= 0);
        return ret;
}

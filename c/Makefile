PROGS:=$(patsubst %.c,%,$(wildcard *.c))

CC:=musl-gcc -static
#CC:=gcc

# https://developers.redhat.com/blog/2018/03/21/compiler-and-linker-flags-gcc
# https://developers.redhat.com/articles/2022/06/07/how-debug-stack-frames-and-recursion-gdb#

# https://www.tiobe.com/tiobe-index/
# https://godbolt.org/

# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

# gcc 8.5.0 on Centos Stream (8.5++) doesn't support
# -Warith-conversion

# yum install gcc-toolset-10.x86_64
# For GCC 10, do the following in .bashrc
# . /opt/rh/gcc-toolset-10/enable

# gnu18 = c18 + POSIX + GNU extensions

CFLAGS:=-pedantic -Werror -Wextra -O -g3 -Wall -std=gnu18 \
	-Wconversion -Warith-conversion -Wdouble-promotion \
	-Wuninitialized -Wformat=2

LDFLAGS:=-lm

.PHONY: all
all: hw linked_list
	@:

%: %.c
%: %.s

% : %.o
	$(CC) -Wall $(LDFLAGS) -o $@ $^

# -save-temps
%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

#hw: hw.o hw-lib.o

.PHONY: clean
clean:
	rm -vf *.i *.s *.o *~ $(PROGS)

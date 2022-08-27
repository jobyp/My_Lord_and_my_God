PROGS:=$(patsubst %.c,%,$(wildcard *.c))

CC:=musl-gcc -static

# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

# gcc 8.5.0 on Centos Stream (8.5++) doesn't support
# -Warith-conversion

# gnu18 = c18 + POSIX + GNU extensions

CFLAGS:=-pedantic -Werror -Wextra -O -g3 -Wall -std=gnu18 \
	-Wconversion  -Wdouble-promotion -Warith-conversion \
	-Wuninitialized -Wformat=2

LDFLAGS:=-lm

.PHONY: all
all: hw
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

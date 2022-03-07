PROGS:=$(patsubst %.c,%,$(wildcard *.c))
CC:=musl-gcc -static
CFLAGS:=-pedantic -Werror -Wextra -O -g3 -Wall -std=c17
LDFLAGS:=-lm
.PHONY: all
all: hw fixed_width hello
	@:

%: %.c
%: %.s

% : %.o
	$(CC) -Wall $(LDFLAGS) -o $@ $^

# -save-temps
%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

hw: hw.o hw-lib.o

.PHONY: clean
clean:
	rm -vf *.i *.s *.o *~ $(PROGS)

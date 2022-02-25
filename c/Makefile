PROGS:=$(patsubst %.c,%,$(wildcard *.c))

.PHONY: all
all: $(PROGS)
	@:

%: %.c
%: %.s

% : %.o
	$(CC) -Wall -o $@ $<

# -save-temps
%.o : %.c
	$(CC) -c -pedantic -Werror -Wextra -Og -Wall -std=c17 -lm -o $@ $<

.PHONY: clean
clean:
	rm -vf *.i *.s *.o *~ $(PROGS)

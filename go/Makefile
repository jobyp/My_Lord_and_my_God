PROGS:=$(patsubst %.go,%,$(wildcard *.go))

.PHONY: all
all: $(PROGS)
	@:

% : %.go
	go fmt $<
	go vet $<
	go build -o $@ $<

.PHONY: clean
clean:
	@rm -vf *~ $(PROGS)

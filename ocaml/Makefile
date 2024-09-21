PROGS:=$(patsubst %.ml,%,$(wildcard *.ml))

.PHONY: all
all: $(PROGS)
	@:

%.exe: %.ml
	rm -vf $@
	dune build $@ && cp -v _build/default/$@ .

% : %.exe
	mv $< $@

.PHONY: clean
clean:
	rm -vf $(PROGS) *~
	dune clean

# https://ocamlpro.com/blog/2021_09_02_generating_static_and_portable_executables_with_ocaml/

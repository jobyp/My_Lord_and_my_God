PROGS:=$(wildcard *.py)

.PHONY: all
all:
	. ~/.py3_classic_algorithms/bin/activate; black $(PROGS); \
	mypy $(PROGS)
	chmod +x $(PROGS)

.PHONY: setup
setup:
	rm -rf ~/.py3_classic_algorithms
	python3 -mvenv ~/.py3_classic_algorithms
	. ~/.py3_classic_algorithms/bin/activate; \
	pip install --upgrade pip; \
	pip install black mypy

.PHONY: clean
clean:
	rm -vf *~

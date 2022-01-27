PROGS:=$(wildcard *.py)

.PHONY: all
all:
	. ~/.py3_classic_algorithms/bin/activate; black $(PROGS)
	mypy $(PROGS)

.PHONY: setup
setup:
	rm -rf ~/.py3_classic_algorithms
	python3 -mvenv ~/.py3_classic_algorithms
	. ~/.py3_classic_algorithms/bin/activate; \
	pip install --upgrade pip; \
	pip install black

.PHONY: clean
clean:
	rm -vf *~

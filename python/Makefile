.PHONY: setup
setup:
	rm -rf .py3
	python3 -m venv .py3
	. .py3/bin/activate; \
	pip install --upgrade pip; \
	pip install black

.PHONY: clean
clean:
	rm -vf *~
	rm -rf .py3

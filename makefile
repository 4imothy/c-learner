.DEFAULT_GOAL := run

all: clearner
.PHONY: all

clearner: src/main.c
	gcc -o clearner src/main.c

run: clearner
	./clearner

clean:
	rm clearner
.PHONY: clean

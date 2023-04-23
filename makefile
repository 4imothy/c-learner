CC := gcc
CFLAGS := -Wall -Wextra -pedantic
SRCDIR := src
OBJFUNCDIR := obj_funcs

SRCFILES := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/$(OBJFUNCDIR)/*.c)

all: clearner

%.o: %.c %.h
	$(CC) $(CLFAGS) -c $^

clearner: $(SRCFILES)
	$(CC) $(CFLAGS) -o $@ $^

run: clearner
	./clearner

clean:
	rm clearner
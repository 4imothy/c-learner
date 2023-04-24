CC := gcc
CFLAGS := -Wall -Wextra -pedantic
SRC_DIR := src
FORMAT := clang-format

# search for all *.c files
SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')
HEADER_FILES := $(shell find $(SRC_DIR) -name '*.h')

all: clearner

# %.o: %.c %.h
# 	$(CC) $(CLFAGS) -c $^

clearner: $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS) -o $@ $(SRC_FILES)

run: clearner
	./clearner

format:
	$(FORMAT) -i $(SRC_FILES) $(HEADER_FILES)
	
clean:
	rm clearner


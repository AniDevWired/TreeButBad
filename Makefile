CC = gcc

CFLAGS = -Wall \
	-Wextra \
	-Werror \
	-Wpedantic \
	-std=c11 \
	-lm


SRC = src/main.c
OUT = build/tree

all:
	mkdir -p build
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

clean:
	rm -rf build
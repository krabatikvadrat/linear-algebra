CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g

vec:
	$(CC) $(CFLAGS) vectors.c -o bin/vectors.bin -lm

CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11

all: init_test

init_test:
	$(CC) $(CFLAGS) *.c -o test
	./test
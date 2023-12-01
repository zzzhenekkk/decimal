CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11

all: evgeniy

evgeniy:
	$(CC) $(CFLAGS) s21*.c evgeniy.c -o evgeniy
	./evgeniy

andrey:
	$(CC) $(CFLAGS) s21*.c andrey.c -o andrey
	./andrey

gleb:
	$(CC) $(CFLAGS) s21*.c gleb.c -o gleb
	./gleb
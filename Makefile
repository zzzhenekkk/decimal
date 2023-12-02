CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11

all: evgeniy

evgeniy: clean
	$(CC) $(CFLAGS) s21*.c evgeniy.c -o evgeniy_e
	./evgeniy_e

andrey: clean
	$(CC) $(CFLAGS) s21*.c andrey.c -o andrey_e
	./andrey_e

gleb: clean
	$(CC) $(CFLAGS) s21*.c gleb.c -o gleb_e
	./gleb_e

clean: clean
	rm -rf evgeniy_e andrey_e gleb_e

CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11

all: evgeniy

evgeniy: clean
	$(CC) $(CFLAGS) s21*.c evgeniy.c -o evgeniy
	./evgeniy

andrey: clean
	$(CC) $(CFLAGS) s21*.c andrey.c -o andrey
	./andrey

gleb: clean
	$(CC) $(CFLAGS) s21*.c gleb.c -o gleb
	./gleb

clean: clean
	rm -rf evgeniy andrey gleb

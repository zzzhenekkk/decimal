.PHONY: all s21_decimal.a

CC=gcc
FLAGS=-std=c11 -g -Wall -Werror -Wextra
# FLAGS=-std=c11 -Wall -Werror -Wextra
TEST_FLAGS=-lm
S21_DECIMAL_C=s21_*.c
S21_DECIMAL_H=s21_*.h
S21_DECIMAL_O=s21_*.o
TESTS=tests

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS+=-lsubunit
endif

all: s21_decimal.a

s21_decimal.a:
	$(CC) $(S21_DECIMAL_C) -c $(FLAGS)
	ar rc s21_decimal.a $(S21_DECIMAL_O)
	ranlib s21_decimal.a

s21_covered:
	$(CC) $(S21_DECIMAL_C) -c $(FLAGS) --coverage
	ar rc s21_decimal.a $(S21_DECIMAL_O)
	ranlib s21_decimal.a

style:
	clang-format -style=google -i test/$(TESTS)*.c $(TESTS).c $(S21_DECIMAL_C) $(S21_DECIMAL_H)
	python3 ./cpplint.py --extension=c,h test/$(TESTS)*.c $(TESTS).c $(S21_DECIMAL_C) $(S21_DECIMAL_H)
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem s21_decimal.c test/$(TESTS)*.c $(TESTS).c $(S21_DECIMAL_C) $(S21_DECIMAL_H)

test: clean s21_covered
	$(CC) test/$(TESTS)*.c $(TESTS).c -c $(FLAGS) --coverage
	$(CC) -o $(TESTS) $(TESTS)*.o s21_decimal.a -lcheck --coverage $(FLAGS) $(TEST_FLAGS) #-lgcov
	./$(TESTS)

mem: test
ifeq ($(shell uname -s),Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(TESTS)
else
	leaks --atExit -- ./$(TESTS)
endif

clean:
	rm -rf $(TESTS) *.a *.o *.gcda *.gcno *.gcov *.info *.html report

rebuild: clean all

gcov_report: test
	lcov -t "s21_decimal" -o s21_decimal.info -c -d .
	genhtml -o report s21_decimal.info



CFLAGS=-Wall -Werror -Wextra -std=c11

evgeniy: clean
	$(CC) $(CFLAGS) -g s21*.c evgeniy.c -o evgeniy_e
	./evgeniy_e

andrey: clean
	$(CC) $(CFLAGS) -g s21*.c andrey.c -o andrey_e
	./andrey_e

andrey_windows:
	del andrey_e.exe
	$(CC) $(CFLAGS) s21*.c andrey.c -o andrey_e.exe
	andrey_e.exe

gleb: clean
	$(CC) $(CFLAGS) s21*.c gleb.c -o gleb_e
	./gleb_e

# clean: 
# 	rm -rf evgeniy_e andrey_e gleb_e

#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

typedef struct 
{
    unsigned int bits[4];
} s21_decimal;

// узнать значение конкретного бита
int get_bit(s21_decimal num, int cur_bit);

// установить значение конкретного бита
void set_bit(s21_decimal* num, int bit, int result);

// распечатаем наш decimal от 0 до 127
void print_decimal (s21_decimal num);

// узнать значение scale коэфициента масштабирования
int get_scale (s21_decimal num);

// установить значение scale коэфициента масштабирования, 0 - успешно, 1 - еррор
int set_scale (s21_decimal * num, int scale);

// инициализируем децимал
s21_decimal init_decimal(int i1, int i2, int i3, int sign, int exp);

void set_minus(s21_decimal* num);
s21_decimal init_decimal(int i1, int i2, int i3, int sign, int exp);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

#endif  // S21_DECIMAL

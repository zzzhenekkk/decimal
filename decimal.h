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

void set_minus(s21_decimal* num);
s21_decimal init_decimal(int i1, int i2, int i3, int sign, int exp);
int s21_from_int_to_decimal(int src, s21_decimal *dst);

#endif  // S21_DECIMAL

#include "s21_decimal.h"

// распечатаем наш decimal от 0 до 127
void print_decimal(s21_decimal num) {
  for (int i = 3; i >= 0; i--) {
    printf("[");
    for (int j = 31; j >= 0; j--) {
      if (i == 3 && j == 23) printf("->");
      printf("%d", get_bit(num, i * 32 + j));
      if (i == 3 && j == 16) printf("<-");
      if (i == 3 && j == 31) printf(".");
    }
    printf("] ");
  }
}

// инициализируем децимал
s21_decimal init_decimal(int i1, int i2, int i3, int sign, int exp) {
  s21_decimal d;
  d.bits[2] = i3;
  d.bits[1] = i2;
  d.bits[0] = i1;
  if (sign) set_minus(&d, 1);
  if (exp) set_scale(&d, exp);
  return d;
}
#include "s21_decimal.h"

int main() {
  s21_decimal dec = {0};
  dec = init_decimal(1, 2, 3, 1, 10);
  set_minus(&dec, 0);
  printf("%d", get_sign(dec));
  print_decimal(dec);
  big_decimal big = {0};
  init_big(dec, &big);
  print_big_decimal(&big);
  return 0;
}
#include "s21_decimal.h"

int main() {
  s21_decimal dec = {0};
  dec = init_decimal(1, 2, 3, 1, 10);
  set_minus(&dec, 0);
  printf("%d", get_sign(dec));
  print_decimal(dec);
  // set_minus(&dec);
  s21_from_int_to_decimal(5, &dec);
  set_bit(&dec, 112, 1);
  set_bit(&dec, 113, 1);
  set_bit(&dec, 114, 1);
  set_bit(&dec, 119, 1);
  // s21_from_int_to_decimal(-5, &dec);
  // set_bit(&dec, 112, 1);
  // set_bit(&dec, 119, 1);
  // print_decimal(dec);
  printf("\n%d", get_scale(dec));
  set_scale(&dec, 127);
  printf("\n%d\n", get_scale(dec));
  print_decimal(dec);
  return 0;
}
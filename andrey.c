#include "s21_decimal.h"

int main() {
   s21_decimal dec1 = {0}, dec2 = {0};

  /* test division */
  // dec1 = init_decimal(9, 0, 0, 0, 3);
  // dec2 = init_decimal(1, 0, 0, 0, 2);
  // big_decimal big1 = {0}, big2 = {0}, res = {0};
  // init_big(dec1, &big1);
  // init_big(dec2, &big2);
  // print_big_decimal(&big1);
  // print_big_decimal(&big2);
  // division(big1, big2, &res);
  // print_big_decimal(&res);

  /* test comparision */
  dec1 = init_decimal(9, 0, 0, 0, 3);
  dec2 = init_decimal(9, 0, 1, 0, 3);
  print_decimal(dec1);
  print_decimal(dec2);

  int res = s21_is_less(dec1, dec2);
  printf("dec1 < dec2 : %d\n", res);

  res = s21_is_less_or_equal(dec1, dec2);
  printf("dec1 <= dec2 : %d\n", res);

  res = s21_is_greater(dec1, dec2);
  printf("dec1 > dec2 : %d\n", res);

  res = s21_is_greater_or_equal(dec1, dec2);
  printf("dec1 >= dec2 : %d\n", res);

  res = s21_is_equal(dec1, dec2);
  printf("dec1 == dec2 : %d\n", res);

  res = s21_is_not_equal(dec1, dec2);
  printf("dec1 != dec2 : %d\n", res);
  return 0;
}
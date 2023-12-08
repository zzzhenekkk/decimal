#include "s21_decimal.h"
#include <stdio.h>

int main() {
   s21_decimal dec1 = {0}, dec2 = {0}, dec3 = {0};

  /* test division */
  dec1 = init_decimal(125, 0, 0, 0, 0);
  dec2 = init_decimal(10, 0, 0, 0, 0);
  big_decimal big1 = {0}, big2 = {0}, res = {0}, rest = {0};
  // full_decimal(&dec1);
  init_big(dec1, &big1);
  init_big(dec2, &big2);
  init_big(dec3, &rest);
  print_big_decimal(&big1);
  print_big_decimal(&big2);
  division(big1, big2, &res);
  print_big_decimal(&res);
  printf("\n\n");
  zero_big_decimal(&res);
  rest = division_with_rest(big1, big2, &res);
  print_big_decimal(&res);
  print_big_decimal(&rest);

  /* test comparision */
  // dec1 = init_decimal(9, 0, 0, 0, 3);
  // dec2 = init_decimal(9, 0, 1, 0, 3);
  // print_decimal(dec1);
  // print_decimal(dec2);

  // int res = s21_is_less(dec1, dec2);
  // printf("dec1 < dec2 : %d\n", res);

  // res = s21_is_less_or_equal(dec1, dec2);
  // printf("dec1 <= dec2 : %d\n", res);

  // res = s21_is_greater(dec1, dec2);
  // printf("dec1 > dec2 : %d\n", res);

  // res = s21_is_greater_or_equal(dec1, dec2);
  // printf("dec1 >= dec2 : %d\n", res);

  // res = s21_is_equal(dec1, dec2);
  // printf("dec1 == dec2 : %d\n", res);

  // res = s21_is_not_equal(dec1, dec2);
  // printf("dec1 != dec2 : %d\n", res);
  return 0;
}
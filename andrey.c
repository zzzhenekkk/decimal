#include "s21_decimal.h"

int main() {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1 = init_decimal(9, 0, 0, 0, 3);
  // set_minus(&dec1, 1);
  dec2 = init_decimal(1, 0, 0, 0, 2);
  big_decimal big1 = {0}, big2 = {0}, res = {0};
  init_big(dec1, &big1);
  init_big(dec2, &big2);
  // printf("%d", get_sign(dec1));
  // print_decimal(dec1);
  // print_decimal(dec2);
  // s21_is_less(dec1, dec2);
  // big_decimal big = {0};
  // init_big(dec1, &big);
  print_big_decimal(&big1);
  print_big_decimal(&big2);


  division(big1, big2, &res);
  print_big_decimal(&res);
  return 0;
}
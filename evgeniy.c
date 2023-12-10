#include "s21_decimal.h"

int main() {
  s21_decimal val1 = init_decimal (0xffffffff,0xffffffff,0xffffffff,0,0);
  s21_decimal val2 = init_decimal (1,0,0,0,28);
  s21_decimal res = init_decimal (0,0,0,0,0);
  
  // big_decimal val1 = {0};
  // set_bit_big(&val1, 190, 1);
  // set_bit_big(&val1, 188, 1);
  // print_big_decimal(&val1);
  // shift_left_big(&val1, 1);
  // print_big_decimal(&val1);
  s21_add(val1, val2, &res);
  print_decimal(res);


  // s21_decimal val1 = {0};
  // s21_decimal val2 = {0};
  // s21_decimal result = {0};

  // s21_from_int_to_decimal(-123, &val1);
  // s21_from_int_to_decimal(4, &val2);

  // // set_scale(&val1, 2);

  // print_decimal(val1);
  // print_decimal(val2);

  // printf("\n!!!%d!!!\n", s21_add(val1, val2, &result));
  // // printf("\n!!!%d!!!\n", s21_div(val1, val2, &result));

  // print_decimal(result);

  return 0;
}
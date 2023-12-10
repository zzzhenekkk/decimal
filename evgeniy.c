#include "s21_decimal.h"

int main() {
  // big_decimal a = {0};
  // big_decimal b = {0};
  s21_decimal val1 = init_decimal (0xffffffff,0xffffffff,0xffffffff,0,0);
  s21_decimal val2 = init_decimal (1,0,0,0,28);
  s21_decimal res = init_decimal (0,0,0,0,0);
  
  s21_add(val1, val2, &res);
  print_decimal(res);
  //  full_decimal(&val1);
  //  full_decimal(&val1);
  // big_decimal res = {0};
  // s21_decimal ab = {0};
  // full_decimal(&ab);
  // init_big(ab, &a);
  // a.exponenta = 3;
  // b.bits[0]= 10;
  // print_big_decimal(&a);
  // print_big_decimal(&b);

  // print_big_decimal(&a);

  // s21_decimal val1 = {0};
  // s21_decimal val2 = {0};
  // s21_decimal result;
  // full_decimal(&val1);
  // full_decimal(&val2);
  // set_scale(&val1, 7);
  // set_scale(&val2, 24);

  // printf("\n!!!%d!!!\n", s21_add(val1, val2, &result));
  // print_decimal(result);

  // s21_decimal result = {0};

  // s21_from_int_to_decimal(-123, &val1);
  // s21_from_int_to_decimal(4, &val2);

  // print_decimal(val1);
  // print_decimal(val2);

  // division
  // // printf("\n!!!%d!!!\n", s21_add(val1, val2, &result));
  // // printf("\n!!!%d!!!\n", s21_div(val1, val2, &result));

  // print_decimal(result);

  // s21_decimal dec1 = {0}, dec2 = {0};
  // big_decimal big1 = {0}, big2 = {0}, res = {0};
  // dec1 = init_decimal(127, 0, 0, 0, 0);
  // // set_minus(&dec1, 1);
  // dec2 = init_decimal(10, 0, 0, 0, 0);

  // init_big(dec1, &big1);
  // init_big(dec2, &big2);
  // printf("%d", get_sign(dec1));
  // print_decimal(dec1);
  // print_decimal(dec2);
  // s21_is_less(dec1, dec2);
  // big_decimal big = {0};
  // init_big(dec1, &big);
  // print_big_decimal(&big1);
  // print_big_decimal(&big2);

  // big_decimal ostatok = division_without_trace(big1, big2, &res);

  // print_big_decimal(&res);
  // print_big_decimal(&ostatok);
  return 0;
}
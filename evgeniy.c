#include "s21_decimal.h"

int main() {
  s21_decimal num1 = {{-1, -1, -1688, 0}};
  s21_decimal num2 = {{44, 369, 1687, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int status = s21_add(num1, num2, &res);
  printf("status %d", status);

  // ck_assert_int_eq(status, 1);
  // ck_assert_int_eq(res.bits[0], 43);
  // ck_assert_int_eq(res.bits[1], 369);
  // ck_assert_int_eq(res.bits[2], 0);
  // ck_assert_int_eq(res.bits[3], 0);

  // s21_decimal val1 = init_decimal (100,0,0,0,28);
  // s21_decimal val2 = init_decimal (1,0,0,0,28);

  // print_decimal(val1);
  // print_decimal(val2);

  // s21_decimal res;
  // int resss = -2;

  // resss = s21_div(val1, val2, &res);
  // printf("\n!!!%d!!!\n", resss);
  // print_decimal(res);

  // s21_decimal num = {{1, 0, 0, 0}};
  // s21_decimal num2 = {{1, 0, 0, 0}};
  // s21_decimal res = {0};
  // s21_decimal answer = {{2, 0, 0, 0}};

  // (void)answer;
  // s21_add(num, num2, &res);

  // (void)answer;
  // val2 = init_decimal (1,0,0,0,9);
  // resss = s21_add(res, val2, &res);
  // printf("\n!!!%d!!!\n", resss);
  // print_decimal(res);

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
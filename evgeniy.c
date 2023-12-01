#include "s21_decimal.h"

int main() {

  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};
  
  
  // s21_from_int_to_decimal(5, &val1);
  // s21_from_int_to_decimal(10, &val2);

  full_decimal(&val1);
  full_decimal(&val2);
  
  print_decimal(val1);
  print_decimal(val2);
  s21_add(val1, val2, &result);




  // set_minus(&dec);
  // set_bit(&dec, 112, 1);
  // set_bit(&dec, 119, 1);
  // print_decimal(dec);
  // set_scale(&dec, 127);
  // print_decimal(dec);
  return 0;
}
#include "s21_decimal.h"

int main() {
<<<<<<< HEAD
=======

>>>>>>> 66754125b534bb66ddfed62d8de7138c9a3b25bc
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  s21_from_int_to_decimal(-123, &val1);
  s21_from_int_to_decimal(4, &val2);

  // set_scale(&val1, 2);

  print_decimal(val1);
  print_decimal(val2);

  printf("\n!!!%d!!!\n", s21_add(val1, val2, &result));
  // printf("\n!!!%d!!!\n", s21_div(val1, val2, &result));

  print_decimal(result);

  return 0;
}
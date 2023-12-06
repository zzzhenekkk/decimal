#include "s21_decimal.h"

// распечатаем наш decimal от 0 до 127
void print_decimal(s21_decimal num) {
  printf("\n");
  for (int i = 3; i >= 0; i--) {
    if (i != 0 && i != 1) printf("[");
    for (int j = 31; j >= 0; j--) {
      if (i == 3 && j == 23) printf("->");
      printf("%d", get_bit(num, i * 32 + j));
      if (i == 3 && j == 16) printf("<-");
      if (i == 3 && j == 31) printf(".");
    }
    if (i != 1 && i != 2) printf("] ");
  }
}

// инициализируем децимал
s21_decimal init_decimal(int i1, int i2, int i3, int sign, int exp) {
  s21_decimal d;
  d.bits[2] = i3;
  d.bits[1] = i2;
  d.bits[0] = i1;
  if (sign) set_minus(&d, 1);
  if (exp) set_scale(&d, exp);
  return d;
}

// big_decimal* mul_mantissa(big_decimal a, big_decimal b, big_decimal* res) {
//   for (int i = 0; i <= b.one_position_left; i++){
//     int digit = get_bit_big(&b,i);
//     if (digit) {
      
//     }
//   }
// }


// заполняем decimal под макс для проверки
void full_decimal(s21_decimal * num) {
  for (int i = 0; i < 96; i++) {
    set_bit(num, i, 1);
  }
}

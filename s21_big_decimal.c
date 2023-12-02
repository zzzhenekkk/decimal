#include "s21_decimal.h"

// распечатаем наш decimal от 0 до 127
void print_big_decimal(big_decimal* num) {
  printf("\nЭксонента: %d | Отриацтельное: %d |", num->exponenta, num->negative);
    printf(" Позиция старшего бита: %d | Колич нулей слев: %d",
           num->one_position_left, num->zero_left);
  printf("\n");
  for (int i = 7; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      printf("%d", get_bit_big(num, i * 32 + j));
    }
  }
    
}


#include "decimal.h"

// распечатаем наш decimal от 0 до 127
void print_big_decimal(big_decimal* num) {
  printf("\n");
  for (int i = 7; i >= 0; i--) {
    printf("[");
    for (int j = 31; j >= 0; j--) {
      printf("%d", get_bit_big(num, i * 32 + j));
    }
    printf("] ");
    printf("\nЭкс: %d Отриц: %d", num->exponenta, num->negative);
    printf("\nПозиция первой 1: %d Колич нулей слев: %d",
           num->one_position_left, num->zero_left);
  }
}
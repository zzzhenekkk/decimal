#include "s21_decimal.h"


// перевести из int в decimal (всегда успешно)
int s21_from_int_to_decimal(int src, s21_decimal *dst){
    *dst = init_decimal(src<0 ? ~(src) + 1 : src, 0, 0, src<0 ? 1:0, 0);
    return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    int res = 0;
    *dst = 0; // избавляеся от мусора
    //  - 0 - OK
    //  - 1 - ошибка конвертации
    int exp = get_scale(src);
    big_decimal full = {0}, ten = {0};
    int special_case = 0;
    init_big(src, &full);
    if (exp) {
        init_big(init_decimal(10,0,0,0,0), &ten);
        full.exponenta = 0; // отбросить exp (у нас int)
        for (int i = 0; i < exp; i++) {
            division_with_rest(full, ten, &full); // делим мантиссу на 10^exp
            // print_big_decimal(&full);
        }
    }
    zeroes_left_big(&full);
    if (full.one_position_left > 30) // так как 1 бит в int зарезервирован под знак
        res = 1; // decimal > int
    if (full.one_position_left == 31 && full.negative) { // отлавливаем случай отрицательного числа с мантиссой 2147483648
        int all_zeros = 1;
        for (int i = 30; i >= 0; i--) {
            if (get_bit_big(&full, i)) {
                all_zeros = 0;
                break;
            }
        }
        if (all_zeros) {
            res = 0;
            special_case = 1;
            *dst = -2147483648;
        }
    }
    // перевод последнего bits в int
    int bit = 0; 
    for (int i = 30; i >= 0; i--) {
        bit = get_bit_big(&full, i);
        *dst = *dst | bit<<i;
    }
    if (full.negative) {
        if (!special_case)
            *dst = ~(*dst) + 1;
    }
    return res;
}

//Возвращаемое значение - код ошибки:
//  - 0 - OK
//  - 1 - ошибка конвертации

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = S21_OK;

  if (dst) {
    zero_s21_decimal(dst);
  } else {
    status = S21_ERROR;
  }


  if (status || (0 < fabsf(src) && fabsf(src) < 1e-28) || isnan(src) ||
      isinf(src) || 79228162514264337593543950335.f < src) {
    status = S21_ERROR;
  } else {
    char part[128] = {0};
    int scale = 0;
    int decimal_part = 0;
    int length = 0;

    // переводим из float в строку
    sprintf(part, "%.7g", src);
    printf("!!!%s!!!", part);
    s21_get_float_part(part, &scale, &length, &decimal_part);

    if (scale < 0 && 28 < abs(scale) + length) {
      memset(part, 0, 128);
      sprintf(part, "%.*g", 29 - abs(scale), src);
      s21_get_float_part(part, &scale, &length, &decimal_part);
    }

    int number = abs(atoi(part));
    for (int i = 0; i < length; ++i) {
      number *= 10;
    }
    number += decimal_part;
    
    // устанавливаем минус
    if (src < 0) {
      set_minus(dst, 1);
    }

    // устанавливаем экспоненту
    if (scale < 0) {
      set_scale(dst, abs(scale) + length);
    } else if (!scale) {
      set_scale(dst, length);
    }

    for (int i = 0; number; ++i, number /= 2) {
      if (number % 2) {
        set_bit(dst, i, 1);
      }
    }

    // 
    if (0 < scale - length) {
      s21_decimal s21_mul_by_10 = {{10, 0, 0, 0}};
      for (int i = 0; !status && i < scale - length; ++i) {
        status = s21_mul(*dst, s21_mul_by_10, dst);
      }
    }
  }

  return status;
}


void s21_get_float_part(char *part, int *scale, int *length,
                        int *decimal_part) {
  // ищем позицию точки
  char *dot = strchr(part, '.');
  // ищем позицию e
  char *exponenta = strchr(part, 'e');

  *scale = 0;
  *decimal_part = 0;
  *length = 0;

  if (exponenta) {
    *exponenta++ = '\0';
    *scale = atoi(exponenta);
  }

  if (dot) {
    *dot++ = '\0';
    *length = strlen(dot);
    *decimal_part = atoi(dot);
  }
}
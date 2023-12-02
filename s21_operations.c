#include "s21_decimal.h"

// Функции возвращают код ошибки:
// - 0 - OK
// - 1 - число слишком велико или равно бесконечности
// - 2 - число слишком мало или равно отрицательной бесконечности
// - 3 - деление на 0

// суммируем decimal и выводим в result
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  // проверяем указатель на result
  if (result) {
    // обнулили result decimal
    *result = init_decimal(0, 0, 0, 0, 0);

    // переводим все в big_decimal
    big_decimal bvalue_1 = {0};
    init_big(value_1, &bvalue_1);
    big_decimal bvalue_2 = {0};
    init_big(value_2, &bvalue_2);
    big_decimal result_big = {0};
    init_big(*result, &result_big);
    // печатаем для проверки
    print_big_decimal(&bvalue_1);
    print_big_decimal(&bvalue_2);

    // приводим big_decimal к одной экспоненте
    normalize_big(&bvalue_1, &bvalue_2);

    // складываем мантиссы
    sum_mantissa(&bvalue_1, &bvalue_2, &result_big);

    // печатаем для проверки
    print_big_decimal(&result_big);

    // обрабатываем и отдаем в s21_decimal
    status = big_to_s21decimal(result, &result_big);

  } else {
    status = -1;
  }
  return status;
}

int big_to_s21decimal(s21_decimal *result, big_decimal *result_big) {
  int status = 0;
  // сколько нулей слева, если занулеванное, то one_position_left = -1
  zeroes_left_big(result_big);
  // проверка на переполнение
  if ((result_big->one_position_left - result_big->exponenta) > BITS_S21) {
    status = 1;
  }
  // проверка входит ли мантисса в пределы 95 бит, иначе банковское округление
  else if (result_big->one_position_left > BITS_S21) {
    bank_rounding(result_big);
  } else {
    big_to_s21decimal_95();
  }
}

//
void big_to_s21decimal_95();

// складываем мантисы big decimal
void sum_mantissa(big_decimal *bvalue_1, big_decimal *bvalue_2,
                  big_decimal *result) {
  int tmp = 0;
  int var = 0;

  for (int i = 0; i <= BITS_BIG; i++) {
    var = (get_bit_big(bvalue_1, i) + get_bit_big(bvalue_2, i) + tmp);
    if (var == 3) {
      tmp = 1;
      set_bit_big(result, i, 1);
    } else if (var == 2) {
      tmp = 1;
      set_bit_big(result, i, 0);
    } else if (var == 1) {
      set_bit_big(result, i, 1);
      tmp = 0;
    } else if (var == 0) {
      set_bit_big(result, i, 0);
      tmp = 0;
    }
  }
}

// приводим big_decimal к одной экспоненте
void normalize_big(big_decimal *bvalue_1, big_decimal *bvalue_2) {
  int def = bvalue_1->exponenta - bvalue_2->exponenta;
  if (def > 0) {
    multiply_10_mantis(bvalue_2, def);
    multiply_mantis();
    // shift_left_big(bvalue_2, def);
    zeroes_left_big(bvalue_2);
  } else if (def < 0) {
    // shift_left_big(bvalue_1, def);
    zeroes_left_big(bvalue_1);
  }
}

// домножаем мантису на экспоненту 10
multiply_10_mantis(big_decimal *bvalue, int def) { bvalue }

// сдвигаем big_decimal налево по битам
void shift_left_big(big_decimal *bvalue, int def) {
  zeroes_left_big(bvalue);  // устанавливаем нули слева и позицию первой 1
  for (int i = bvalue->one_position_left; i >= 0; i--) {
    set_bit_big(bvalue, i + def, get_bit_big(bvalue, i));
  }
  // обновляем экспоненту на текущую
  bvalue->exponenta += def;
}

// сколько нулей слева, если занулеванное, то one_position_left = -1
void zeroes_left_big(big_decimal *bvalue) {
  int i = BITS_BIG;
  while (1) {
    if (get_bit_big(bvalue, i) != 0) {
      bvalue->zero_left = BITS_BIG - i;
      bvalue->one_position_left = i;
      break;
    }
    i--;
    if (!(i >= 0)) break;
  }
  if (i == -1) {
    bvalue->zero_left = BITS_BIG;
    bvalue->one_position_left = -1;
  }
}

// устанавливаем big_decimal по s21_decimal
void init_big(s21_decimal value, big_decimal *big) {
  big->exponenta = get_scale(value);
  big->negative = get_sign(value);
  big->bits[0] = value.bits[0];
  big->bits[1] = value.bits[1];
  big->bits[2] = value.bits[2];
}

// // если scale не равны, то приводим к общему коэфициенту
// if (get_scale(value_1) != get_scale(value_2)) normalize_decimal(&value_1,
// &value_2); if (get_sign(value_1) ^ get_sign(value_2)) {

// } else {

// }

//   } else {
//     status = 1;
//   }
// // если коэфициент масштабирования равен, то складываем мантисы
// if (get_scale(value_1) == get_scale(value_2)) {

// }

//   return status;
// }

// int normalize_decimal(s21_decimal * value_1, s21_decimal * value_2) {
//     int status = 0;
//     if (value_1 && value_2) {
//         int scale1 = get_scale(*value_1);
//         int scale2 = get_scale(*value_2);
//         if (scale1 > scale2) {
//             if (shift_bits_left (scale2, scale1 - scale2)) status = 1;
//             set_scale(scale2, scale1 - scale2);
//         }
//     } else status = 1;
//     return status;
// }

// int shift_bits_left (s21_decimal * value, int num) {
//     if (zeroes_left(*value) >= num) {

//     }
//     return 0;
// }

// // считает и возвращает количество нулей слева по мантиссе, чтобы
// проверять, можно ли реализовать сдвиг int zeroes_left(s21_decimal value) {
//     int result = 0;
//     for (int i = 95; i >= 0; i--) {
//         if (get_bit(value, i) != 0) break;
//     }
//     return 95-result;
// }

// int sum_mantis(){
//     for (int i = 0; i < 96; i++) {
//             int tmp = 0;
//             int var = 0;
//             var = (get_bit(value_1, i) + get_bit(value_2, i) + tmp);
//             if (var == 3) {
//                 tmp = 1;
//                 set_bit (result, i, 1);
//             } else if (var == 2) {
//                 tmp = 1;
//                 set_bit (result, i, 0);
//             } else if (var == 1) {
//                 set_bit (result, i, 1);
//                 tmp = 0;
//             } else {
//                 set_bit (result, i, 0);
//                 tmp = 0;
//             }

//             // ситуация когда переполнение
//             if (i == 95 && tmp > 0) {
//                 res_ret = 1;
//             }

//     }
// }
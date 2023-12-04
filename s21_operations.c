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
    big_decimal result_b = {0};
    // print_decimal(*result);

    normalize_big(&bvalue_1, &bvalue_2);
    //     print_big_decimal(&bvalue_1);
    // print_big_decimal(&bvalue_2);


    sum_mantissa(&bvalue_1, &bvalue_2, &result_b);
    result_b.exponenta = bvalue_1.exponenta;
    // print_big_decimal(&bvalue_1);
    // print_big_decimal(&bvalue_2);
    // print_big_decimal(&result_b);




    big_to_s21decimal(result, &result_b);

  } else {
    status = -1;
  }
  return status;
}

// для приведения к одной экспоненте, домножаем на 10 биг децимал
int multiply_10_mantis_big(big_decimal * bvalue, int def) {
  int status = 0;

  // создаем 10 для биг децимал
  s21_decimal ten_s = {0};
  s21_from_int_to_decimal(10, &ten_s);
  big_decimal ten = {0};
  init_big (ten_s,&ten);
  // big_decimal result = {0};

  for (int i = 1; i <= def; i++) {
    if (multiply_mantis_big(*bvalue, &ten, bvalue)) status = 1;
  }
  bvalue->exponenta += def;
  return status;
}


// из бига в s21
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
    // bank_rounding(result_big);
  } else {
    big_to_s21decimal_95(result_big, result);
  }
  return status;
}

// переводим из биг ту с21 со старшим битом не больше 95
void big_to_s21decimal_95(big_decimal * result_big, s21_decimal * result) {
  for (int i = 95; i >= 0; i--) {
    set_bit(result, i, get_bit_big(result_big, i));
  }
  set_scale(result, result_big->exponenta);
}

// складываем мантисы big decimal
int sum_mantissa(big_decimal *bvalue_1, big_decimal *bvalue_2,
                  big_decimal *result) {
  int status = 0;
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
  if (tmp == 1) status = 1;
  return status;
}

// приводим big_decimal к одной экспоненте
void normalize_big(big_decimal *bvalue_1, big_decimal *bvalue_2) {
  int def = bvalue_1->exponenta - bvalue_2->exponenta;
  if (def > 0) {
    multiply_10_mantis_big(bvalue_2, def);
    zeroes_left_big(bvalue_2);
  } else if (def < 0) {
    multiply_10_mantis_big(bvalue_1, def);
    zeroes_left_big(bvalue_1);
  }
}

// домножаем мантису на экспоненту 10
// multiply_10_mantis(big_decimal *bvalue, int def) { bvalue }

// умножение мантис биг децимал
int multiply_mantis_big(big_decimal bvalue_1, big_decimal *bvalue_2, big_decimal *result) {
  int status = 0;
  // big_decimal result = {0};
  // обнуляем мантиссу
  zero_mantisa_big(result);

  zeroes_left_big(bvalue_2);
  zeroes_left_big(&bvalue_1);
  for (int i = 0; i <= bvalue_2->one_position_left; i++) {
    if (i != 0) if (shift_left_big(&bvalue_1, 1) == 1) {
      status = 1;
      break;
    }
    if (get_bit_big(bvalue_2, i)) if (sum_mantissa(result, &bvalue_1, result)) status = 1;
  }
  return status;
}

// обнуялем мантису биг децимал
void zero_mantisa_big(big_decimal * result) {
  for (int i = 0; i < BITS_B; i++) {
    result->bits[i] = 0;
  } 
}

// сдвигаем big_decimal налево по битам, если вылезли за пределы, вернет 1, если все ок то 0
int shift_left_big(big_decimal *bvalue, int def) {
  int status = 0;

  zeroes_left_big(bvalue);  // устанавливаем нули слева и позицию первой 1

  if ((BITS_BIG - bvalue->one_position_left) < def) status = 1;

  for (int i = bvalue->one_position_left; i >= 0; i--) {
    // для того, чтобы не выходить за пределы массива
    if ((i+def) <= BITS_BIG) {
    set_bit_big(bvalue, i + def, get_bit_big(bvalue, i));
    }
  }
  // доставляем нули справа
  for (int i = 0; i < def; i++) {
    set_bit_big(bvalue, i, 0);
  }
  zeroes_left_big(bvalue);  // устанавливаем нули слева и позицию первой 1

  return status;
}

// сдвигаем big_decimal налево по битам, если вылезли за пределы, вернет 1, если все ок то 0
int shift_right_big(big_decimal *bvalue, int def) {
  int status = 0;

  zeroes_left_big(bvalue);  // устанавливаем нули слева и позицию первой 1

  if ((bvalue->one_right - def) < 0) status = 1;

  for (int i = bvalue->one_right; i <= BITS_BIG; i++) {
    // для того, чтобы не выходить за пределы массива
    if ((i-def) >= 0) {
    set_bit_big(bvalue, i - def, get_bit_big(bvalue, i));
    }
  }
  // доставляем нули слева
  for (int i = BITS_BIG; i > (bvalue->one_position_left - def); i--) {
    set_bit_big(bvalue, i, 0);
  }
  zeroes_left_big(bvalue);  // устанавливаем нули слева и позицию первой 1

  return status;
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
  for (int j = 0; j <= BITS_BIG; j++) {
    if (get_bit_big(bvalue, j) != 0) {
      bvalue->one_right = j;
      break;
    }
  }
}

// устанавливаем big_decimal по s21_decimal
void init_big(s21_decimal value, big_decimal *big) {
  big->exponenta = get_scale(value);
  big->negative = get_sign(value);
  big->bits[0] = value.bits[0];
  big->bits[1] = value.bits[1];
  big->bits[2] = value.bits[2];
  zeroes_left_big(big);
}
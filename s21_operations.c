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
    int equal_signs = 0;
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
    // print_big_decimal(&bvalue_1);
    // print_big_decimal(&bvalue_2);
    // равные ли у нас знаки
    if (get_sign(value_1) == get_sign(value_2)) equal_signs = 1;

    // если равные, то складываем мантисы
    if (equal_signs) {
      sum_mantissa(&bvalue_1, &bvalue_2, &result_b);
      result_b.negative = bvalue_1.negative;
    } else {  // если разные, то вычитаем
      int compare = compare_mantis_big(&bvalue_1, &bvalue_2);
      if (compare > 0) {
        sub_mantis_big(bvalue_1, bvalue_2, &result_b);
        result_b.negative = bvalue_1.negative;
      } else if (compare < 0) {
        sub_mantis_big(bvalue_2, bvalue_1, &result_b);
        result_b.negative = bvalue_2.negative;
      }
    }

    // дописываем экспоненту
    result_b.exponenta = bvalue_1.exponenta;
    print_big_decimal(&result_b);
    // print_big_decimal(&bvalue_2);
    // print_big_decimal(&bvalue_1);
    // print_big_decimal(&bvalue_2);
    // print_big_decimal(&result_b);

    big_to_s21decimal(result, &result_b);

  } else {
    status = -1;
  }
  return status;
}

// вычитание decimal
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int znak = get_sign(value_2);
  set_minus(&value_2, !znak);
  return s21_add(value_1, value_2, result);
}

// умножение decimal
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  // проверяем указатель на result
  if (result) {
    int equal_signs = 0;
    // обнулили result decimal
    *result = init_decimal(0, 0, 0, 0, 0);

    // переводим все в big_decimal
    big_decimal bvalue_1 = {0};
    init_big(value_1, &bvalue_1);
    big_decimal bvalue_2 = {0};
    init_big(value_2, &bvalue_2);
    big_decimal result_b = {0};
    // print_decimal(*result);

    // normalize_big(&bvalue_1, &bvalue_2);

    // print_big_decimal(&bvalue_1);
    // print_big_decimal(&bvalue_2);

    // равные ли у нас знаки
    if (get_sign(value_1) == get_sign(value_2)) equal_signs = 1;

    if (equal_signs) {
      result_b.negative = 0;
    } else {
      result_b.negative = 1;
    }

    // дописываем экспоненту
    result_b.exponenta = bvalue_1.exponenta + bvalue_2.exponenta;

    if (multiply_mantis_big(bvalue_1, &bvalue_2, &result_b)) status = 1;

    // при умножении на 0
    zeroes_left_big(&result_b);
    if (result_b.one_position_left == -1) {
      result_b.negative = 0;
      result_b.exponenta = 0;
    }

    print_big_decimal(&result_b);
    // print_big_decimal(&bvalue_2);
    // print_big_decimal(&bvalue_1);
    // print_big_decimal(&bvalue_2);
    // print_big_decimal(&result_b);

    // // если есть возможность, снижаем экспоненту
    // normilize_before_push(&result_b);

    big_to_s21decimal(result, &result_b);

  } else {
    status = -1;
  }
  return status;
}

// 0 - OK 1 - число слишком велико или равно бесконечности 2 - число
/// слишком мало или равно отрицательной бесконечности 3 - деление на 0
// деление
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  int zero1 = 0;
  if (!is_zero_s21_decimal(value_1)) zero1 = 1;

  // проверка на 0, делить на 0 нельзя
  if (is_zero_s21_decimal(value_2)) {
    // создаем биг бецимал
    big_decimal bvalue1 = {0}, bvalue2 = {0}, b_result = {0};
    // переносим из децимал в биг
    init_big(value_1, &bvalue1);
    init_big(value_2, &bvalue2);

    int scale = 0, res_scale = 0;
    /////////// делим в биг децимал
    scale = div_big(bvalue1, bvalue2, &b_result);

    // добавляем в экспоненту value_1 scale
    set_scale(&value_1, get_scale(value_1) + scale);

    // итоговая экспонента value_1 - value_2 + scale
    res_scale = get_scale(value_1) - get_scale(value_2);

    // разбираемся со scale и нормализуем
    if (res_scale > 0) {
      res_scale = preparation_big_decimal(&b_result, res_scale);
    } else if (res_scale < 0) {
      multiply_10_mantis_big_w_e(&b_result, abs(res_scale));
      res_scale = preparation_big_decimal(&b_result, 0);
    }

    if (res_scale >= 0) {
      big_to_s21decimal_95(&b_result, result);
      set_scale(result, res_scale);
    } else {
      status = 1;
    }

    // устанавливаем знак в результат
    if (get_sign(value_1) != get_sign(value_2)) set_minus(result, 1);

  } else {
    status = 3;
  }
  if (status == 1 && get_sign(*result)) status = 2;
  if (status || zero1) zero_s21_decimal(result);
  return status;
}

// зануляем s21_decimal
void zero_s21_decimal(s21_decimal *value) {
  value->bits[0] = value->bits[1] = value->bits[2] = value->bits[3] = 0;
}

// деление биг децимал
int div_big(big_decimal value_1, big_decimal value_2, big_decimal *result) {
  // временный биг децимал
  big_decimal tmp = {0};
  int b_2 = 0, bit_2 = 0, scale = 0, diff = 0, save_scale = 0;

  // находим старшие разряды в биг децимал
  zeroes_left_big(&value_1);
  zeroes_left_big(&value_2);
  b_2 = value_2.one_position_left;
  bit_2 = b_2;

  // проходимся в цикле до тех пор пока value 1 не пустой или не переберем все
  // биты
  for (int i = 0; i < 96 && is_zero_big_decimal(value_1);) {
    // для первого прогона это нам не нужно
    if (i > 0) {
      // value_2 сдвигаем на 1 влево
      shift_left_big(&value_2, 1);
      // увеличиваем scale в результатирующем на 1
      multiply_10_mantis_big_w_e(result, 1);
      // увеличиваем scale в value_1 на 1
      multiply_10_mantis_big_w_e(&value_1, 1);
      save_scale++;
    }

    // ураниваем
    scale = equal_bits_big_decimal(&value_1, &value_2);
    save_scale += scale;
    b_2 = 0;

    // находим старшие разряды
    zeroes_left_big(&value_1);
    zeroes_left_big(&value_2);
    b_2 = value_2.one_position_left;

    diff = b_2 - bit_2;
    if (diff < 0) diff = 0;

    // до тех пор пока разница больше 0 или value1 не пустой
    for (; diff >= 0 && is_zero_big_decimal(value_1);) {
      if (is_greater_big_decimal(value_2, value_1)) {
        set_bit_big(&tmp, 0, 0);
      } else {
        sub_mantis_big(value_1, value_2, &value_1);
        set_bit_big(&tmp, 0, 1);
      }
      i++;
      diff--;
      if (diff >= 0) shift_right_big(&value_2, 1);
      shift_left_big(&tmp, 1);
    }
    if (diff >= 0) shift_left_big(&tmp, diff + 1);
    shift_right_big(&tmp, 1);
    sum_mantissa(result, &tmp, result);
    zero_mantisa_big(&tmp);
  }
  return save_scale;
}

// подготовка к переводу к s21_decimal
int preparation_big_decimal(big_decimal *result, int scale) {
  int dop = 0;
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6] || result->bits[7]) &&
         scale > 0) {
    if (scale == 1 && result->bits[3]) dop = 1;
    div_10_big_decimal(result, 1);
    scale--;
  }
  if (dop && scale == 0 && result->bits[3] == 0 && get_bit_big(result, 0))
    set_bit_big(result, 0, 0);
  if ((result->bits[3] || result->bits[4] || result->bits[5] ||
       result->bits[6] || result->bits[7]))
    scale = -1;
    
  return scale;
}

// делим на 10 биг децимал уменьшая скейл
void div_10_big_decimal(big_decimal *dst, int n) {
  big_decimal tmp = {0};
  s21_decimal ten_s = {0};
  s21_from_int_to_decimal(10, &ten_s);
  big_decimal ten = {0};
  init_big(ten_s, &ten);

  for (int i = 0; i < n; i++) {
    div_big(*dst, ten, &tmp);
    *dst = tmp;
    zero_mantisa_big(&tmp);
  }
}

// уравнивание биг децимал
int equal_bits_big_decimal(big_decimal *value_1, big_decimal *value_2) {
  int scale = 0;

  // до тех пор пока value 2 больше value 1, домножаем value_1
  while (is_greater_big_decimal(*value_2, *value_1)) {
    multiply_10_mantis_big_w_e(value_1, 1);
    scale++;
  }

  // до тех пор пока больше или равно value_1 value_2
  while (is_greater_or_equal_big_decimal(*value_1, *value_2)) {
    shift_left_big(value_2, 1);
  }
  shift_right_big(value_2, 1);
  return scale;
}

// больше или равно биг дец 1 биг дец 2
int is_greater_or_equal_big_decimal(big_decimal value_1, big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !out && !result; i--) {
    if (value_1.bits[i] != 0 || value_2.bits[i] != 0) {
      if (value_1.bits[i] >= value_2.bits[i]) {
        result = 1;
      }
      out = 1;
    }
  }
  return result;
}

// больше ли биг дец 1 биг дец 2
int is_greater_big_decimal(big_decimal value_1, big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !result && !out; i--) {
    if (value_1.bits[i] || value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) out = 1;
    }
  }
  return result;
}

// если big decimal = 0, то возвращает 0
int is_zero_big_decimal(big_decimal big) {
  int result = 0;
  for (int i = 7; i >=0; i--) {
    if (big.bits[i] != 0) {
      result = 1;
      break;
    }
  }
  return result;
}

// проверяет на ноль s21_decimal
int is_zero_s21_decimal(s21_decimal value) {
  int res = 0;
  res = value.bits[0] + value.bits[1] + value.bits[2];
  return res;
}

// // если есть возможность, снижаем экспоненту
// void normalize_big(big_decimal *bvalue_1, big_decimal *bvalue_2) {
//   int def = bvalue_1->exponenta - bvalue_2->exponenta;
//   if (def > 0) {
//     multiply_10_mantis_big(bvalue_2, def);
//     zeroes_left_big(bvalue_2);
//   } else if (def < 0) {
//     multiply_10_mantis_big(bvalue_1, def);
//     zeroes_left_big(bvalue_1);
//   }
// }

// // деление мантис биг децимала
// int div_mantis_big(big_decimal *value_1, big_decimal *value_2,
//                     big_decimal *result) {
//     int status = 0;
//     while (1) {

//     }

//   return status;
// }

// вычитание в формате большого децимала
void sub_mantis_big(big_decimal value_1, big_decimal value_2,
                    big_decimal *result) {
  int tmp = 0, res = 0;
  for (int i = 0; i <= BITS_BIG; i++) {
    res = get_bit_big(&value_1, i) - get_bit_big(&value_2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    set_bit_big(result, i, res % 2);
  }
}

// для приведения к одной экспоненте, домножаем на 10 биг децимал
int multiply_10_mantis_big(big_decimal *bvalue, int def) {
  int status = 0;

  // создаем 10 для биг децимал
  s21_decimal ten_s = {0};
  s21_from_int_to_decimal(10, &ten_s);
  big_decimal ten = {0};
  init_big(ten_s, &ten);
  // big_decimal result = {0};

  for (int i = 1; i <= def; i++) {
    if (multiply_mantis_big(*bvalue, &ten, bvalue)) status = 1;
  }
  bvalue->exponenta += def;
  return status;
}

// для приведения к одной экспоненте, домножаем на 10 биг децимал, не прибавляя
// результатирующую экспу
int multiply_10_mantis_big_w_e(big_decimal *bvalue, int def) {
  int status = 0;

  // создаем 10 для биг децимал
  s21_decimal ten_s = {0};
  s21_from_int_to_decimal(10, &ten_s);
  big_decimal ten = {0};
  init_big(ten_s, &ten);
  // big_decimal result = {0};

  for (int i = 1; i <= def; i++) {
    if (multiply_mantis_big(*bvalue, &ten, bvalue)) status = 1;
  }
  return status;
}

// сравнение мантис big, 1 больше = 1, 2 больше = -1, по ровну = 0
int compare_mantis_big(big_decimal *bvalue1, big_decimal *bvalue2) {
  int result = 0;
  for (int i = BITS_BIG; i >= 0; i--) {
    int rvalue1 = 0, rvalue2 = 0;
    rvalue1 = get_bit_big(bvalue1, i);
    rvalue2 = get_bit_big(bvalue2, i);
    if (rvalue1 != rvalue2) {
      result = rvalue1 - rvalue2;
      break;
    }
  }
  return result;
}

// из бига в s21
int big_to_s21decimal(s21_decimal *result, big_decimal *result_big) {
  int status = 0;
  // сколько нулей слева, если занулеванное, то one_position_left = -1
  zeroes_left_big(result_big);

  if (result_big->negative) set_minus(result, 1);

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
void big_to_s21decimal_95(big_decimal *result_big, s21_decimal *result) {
  for (int i = 0; i < 3; i++) {
    result->bits[i]=result_big->bits[i];
  }
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
    multiply_10_mantis_big(bvalue_1, -def);
    zeroes_left_big(bvalue_1);
  }
}

// домножаем мантису на экспоненту 10
// multiply_10_mantis(big_decimal *bvalue, int def) { bvalue }

// умножение мантис биг децимал
int multiply_mantis_big(big_decimal bvalue_1, big_decimal *bvalue_2,
                        big_decimal *result) {
  int status = 0;
  // big_decimal result = {0};
  // обнуляем мантиссу
  zero_mantisa_big(result);

  zeroes_left_big(bvalue_2);
  zeroes_left_big(&bvalue_1);
  for (int i = 0; i <= bvalue_2->one_position_left; i++) {
    if (i != 0)
      if (shift_left_big(&bvalue_1, 1) == 1) {
        status = 1;
        break;
      }
    if (get_bit_big(bvalue_2, i))
      if (sum_mantissa(result, &bvalue_1, result)) status = 1;
  }
  return status;
}

// обнуялем мантису биг децимал
void zero_mantisa_big(big_decimal *result) {
  for (int i = 0; i < BITS_B; i++) {
    result->bits[i] = 0;
  }
}

// полное обнуление decimal
void zero_big_decimal(big_decimal *result) {
  zero_mantisa_big(result);
  result->exponenta = 0;
  result->negative = 0;
  result->one_position_left = 0;
  result->one_right = 0;
  result->zero_left = 0;
}


// сдвигаем big_decimal налево по битам, если вылезли за пределы, вернет 1, если
// все ок то 0
int shift_left_big(big_decimal *bvalue, int def) {
  int status = 0;

  zeroes_left_big(bvalue);  // устанавливаем нули слева и позицию первой 1

  if ((BITS_BIG - bvalue->one_position_left) < def) status = 1;

  for (int i = bvalue->one_position_left; i >= 0; i--) {
    // для того, чтобы не выходить за пределы массива
    if ((i + def) <= BITS_BIG) {
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

// сдвигаем big_decimal налево по битам, если вылезли за пределы, вернет 1, если
// все ок то 0
int shift_right_big(big_decimal *bvalue, int def) {
  int status = 0;

  zeroes_left_big(bvalue);  // устанавливаем нули слева и позицию первой 1

  if ((bvalue->one_right - def) < 0) status = 1;

  for (int i = bvalue->one_right; i <= BITS_BIG; i++) {
    // для того, чтобы не выходить за пределы массива
    if ((i - def) >= 0) {
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

// деление с big_decimal
void division(big_decimal val1, big_decimal val2, big_decimal *res) {
  int scale_dif = (val1.exponenta - val2.exponenta); // чисел с разными экспонентами
  int q = 0;
  big_decimal part = {0}; //вычитаемое из делителя при найденном q
  big_decimal part_next = {0};  // вычитаемое из делителя при найденном q+1
  big_decimal sum = {0}; // текущая сумма, которая должна знать ответом
  big_decimal before_sum = {0}; // новый член в сумме
  while (is_zero_big_decimal(val1) && sum.exponenta < 31) { // остаток (val1) != нулю или exp суммы < 31 
    if (is_greater_big_decimal(val2, val1)) { // если остаток (изначально - это делимое) < делителя
      multiply_10_mantis_big(&val1, 1); // домнажение остатка на 10 с учетом экспоненты
      multiply_10_mantis_big(&sum, 1); // домнажение суммы на 10 с учетом экспоненты
    }
    q = 0;
    zero_big_decimal(&part);
    zero_big_decimal(&before_sum);
    part_next = val2;
    part = val2;
    zeroes_left_big(&val1);
    while (is_greater_or_equal_big_decimal(val1, part_next)) { // пока делитель(val2)*2^q < остаток
      if (q == 0)  {
        int difference_elder_bit = val1.one_position_left - val2.one_position_left;
        if (difference_elder_bit > 2) {
          q = difference_elder_bit - 2;
          shift_left_big(&part_next, q);
        }
      }
      part = part_next;
      shift_left_big(&part_next, 1); // Домнажение на 2 (формирование 2^q)
      q++;
    }
    q--;
    set_bit_big(&before_sum, q, 1); // формирование нового член в сумме
    sum_mantissa(&sum, &before_sum, &sum); // добавление нового члена к сумме
    // printf("\nval1");
    // print_big_decimal(&val1);
    // printf("\npart");
    // print_big_decimal(&part);
     if (is_greater_or_equal_big_decimal(val1, part))
      sub_mantis_big(val1, part, &val1); // остаток записываем в val1
  }
  sum.exponenta += scale_dif; // учет экспоненты (если < 0, то нужно умножить мантиссу на 10)
  if (scale_dif < 0) {
    multiply_10_mantis_big(&sum, -scale_dif);
  }
  *res = sum;
}

big_decimal division_with_rest(big_decimal val1, big_decimal val2, big_decimal *res) {
  // int scale_dif = (val1.exponenta - val2.exponenta); // чисел с разными экспонентами
  int q = 0;
  big_decimal part = {0}; //вычитаемое из делителя при найденном q
  big_decimal part_next = {0};  // вычитаемое из делителя при найденном q+1
  big_decimal sum = {0}; // текущая сумма, которая должна знать ответом
  big_decimal before_sum = {0}; // новый член в сумме
  normalize_big(&val1, &val2);
  while (is_zero_big_decimal(val1) && is_greater_or_equal_big_decimal(val1, val2)) { // остаток (val1) != нулю или exp суммы < 31 
    q = 0;
    zero_big_decimal(&part);
    zero_big_decimal(&before_sum);
    part_next = val2;
    part = val2;
    zeroes_left_big(&val1);
    while (is_greater_or_equal_big_decimal(val1, part_next)) { // пока делитель(val2)*2^q < остаток
      if (q == 0)  {
        int difference_elder_bit = val1.one_position_left - val2.one_position_left;
        if (difference_elder_bit > 2) {
          q = difference_elder_bit - 2;
          shift_left_big(&part_next, q);
        }
      }
      part = part_next;
      shift_left_big(&part_next, 1); // Домнажение на 2 (формирование 2^q)
      q++;
    }
    q--;
    set_bit_big(&before_sum, q, 1); // формирование нового членa в сумме
    sum_mantissa(&sum, &before_sum, &sum); // добавление нового члена к сумме
    if (is_greater_or_equal_big_decimal(val1, part))
      sub_mantis_big(val1, part, &val1); // остаток записываем в val1
  }
  // sum.exponenta += scale_dif; // учет экспоненты (если < 0, то нужно умножить мантиссу на 10)
  // if (scale_dif < 0) {
  //   multiply_10_mantis_big(&sum, -scale_dif);
  // }
  *res = sum;
  return val1;
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
#include "decimal.h"


// Функции возвращают код ошибки:  
// - 0 - OK  
// - 1 - число слишком велико или равно бесконечности
// - 2 - число слишком мало или равно отрицательной бесконечности
// - 3 - деление на 0 

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0;
    // проверяем указатель на result
    if (result) {
        // обнулили decimal
        init_decimal(0,0,0,0,0);
        // если scale не равны, то привели к общему коэфициенту
        if (get_scale(value_1) != get_scale(value_2)) normalize_decimal(&value_1, &value_2);
        if (get_sign(value_1) ^ get_sign(value_2)) {

        } else {

        }




    } else status = 1;

    // если коэфициент масштабирования равен, то складываем мантисы
    if (get_scale(value_1) == get_scale(value_2)) {
    
    }





    return status;
}

int normalize_decimal(s21_decimal * value_1, s21_decimal * value_2) {
    int status = 0;
    if (value_1 && value_2) {
        int scale1 = get_scale(*value_1);
        int scale2 = get_scale(*value_2);
        if (scale1 > scale2) {
            if (shift_bits_left (scale2, scale1 - scale2)) status = 1;
            set_scale(scale2, scale1 - scale2);
        }
    } else status = 1;
    return status;
}

int shift_bits_left (s21_decimal * value_1, int num) {
    return 0;
}

int sum_mantis {
    for (int i = 0; i < 96; i++) {
            int tmp = 0;
            int var = 0;
            var = (get_bit(value_1, i) + get_bit(value_2, i) + tmp);
            if (var == 3) {
                tmp = 1;
                set_bit (result, i, 1);
            } else if (var == 2) {
                tmp = 1;
                set_bit (result, i, 0);
            } else if (var == 1) {
                set_bit (result, i, 1);
                tmp = 0;
            } else {
                set_bit (result, i, 0);
                tmp = 0;
            }

            // ситуация когда переполнение 
            if (i == 95 && tmp > 0) {
                res_ret = 1;
            }

    }
}
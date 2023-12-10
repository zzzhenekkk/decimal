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
#include "s21_decimal.h"

// division to 10 (shift)
// void del_10_mantissa(s21_decimal *x) {
//     s21_decimal shifted = {0};

// }

// перевести из int в decimal (всегда успешно)
int s21_from_int_to_decimal(int src, s21_decimal *dst){
    *dst = init_decimal(src<0 ? ~(src) + 1 : src, 0, 0, src<0 ? 1:0, 0);
    return 0;
}

// int s21_from_decimal_to_int(s21_decimal src, int *dst) {
//     int res = 0;
//     //  - 0 - OK
//     //  - 1 - ошибка конвертации
//     int exp = get_scale(src);
//     if (exp) {
//         big_decimal big = {0};
//         init_big(src, &big);

//         // move mantissa
//     }
//     if (src.bits[2] || src.bits[1])
//         res = 1;
//     return res;
// }
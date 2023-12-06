#include "s21_decimal.h"

void shift(big_decimal *x) {
    int extra_bit_prev = 0, extra_bit_cur = 0;
    for (int i = 0; i < 7; i++) {
        extra_bit_prev =  extra_bit_cur;
        extra_bit_cur = get_bit_big(x, i*32 + 31);
        x->bits[i]<<=1;
        // extra_bit_cur = get_bit_big(x, (i+1)*32 + 31);
        set_bit_big(x, i*32, extra_bit_prev);
    }
    if (extra_bit_cur == 1)
        printf("выход за пределы мантиссы");
}

int comparator(s21_decimal *x1, s21_decimal *x2) {
    // 1 : x1 > x2
    // 0 : x1 == x2
    // -1 : x1 < x2
    // 0 0, 1 1, 1 0 , 0 1
    int res = 0;
    int sign1 = get_sign(*x1), sign2 = get_sign(*x2);
    int both_negative = 0, both_positive = 0;

    // проверка чисел на разные знаки
    if (sign1 == 1 && sign2 == 0)
        res = -1;
    else if (sign1 == 0 && sign2 == 1)
        res = 1;
    else if (sign1 == 1 && sign2 == 1)
        both_negative = 1;
    else
        both_positive = 1;

    if (!res) {
        // приведение к одной степени
        big_decimal big1 = {0}, big2 = {0};
        init_big(*x1, &big1);
        init_big(*x2, &big2);
        // shift(&big2);
        normalize_big(&big1, &big2);
        print_big_decimal(&big1);
        print_big_decimal(&big2);
        printf("\n1) %d\t2) %d", big1.one_position_left, big2.one_position_left);
        // проверка мантисс
        // int dif = 0;
        // for (int i = big1.one_position_left; i >=0; i--) {

        // }
        int scale1 = get_scale(*x1), scale2 = get_scale(*x2);
        if (scale1 < scale2 && both_positive){
            if (both_positive)
                res = 1;
            if (both_negative)
                res = -1;
        }
    }

    return res;
}

int s21_is_less(s21_decimal x1, s21_decimal x2) {
    return comparator(&x1, &x2);
}

int s21_is_less_or_equal(s21_decimal x1, s21_decimal x2);

int s21_is_greater(s21_decimal x1, s21_decimal x2);

int s21_is_greater_or_equal(s21_decimal x1, s21_decimal x2);

int s21_is_equal(s21_decimal x1, s21_decimal x2);

int s21_is_not_equal(s21_decimal x1, s21_decimal x2);
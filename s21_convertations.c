#include "s21_decimal.h"

// перевести из int в decimal (всегда успешно)
int s21_from_int_to_decimal(int src, s21_decimal *dst){
    *dst = init_decimal(src<0 ? ~(src) + 1 : src, 0, 0, src<0 ? 1:0, 0);
    return 0;
}
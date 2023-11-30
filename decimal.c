#include "decimal.h"


// узнать значение конкретного бита
int get_bit(s21_decimal num, int cur_bit) {
  int bit;
  if ((num.bits[cur_bit / 32] & (1 << cur_bit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }

  return bit;
}

// установить значение конкретного бита
void set_bit(s21_decimal* num, int bit, int result) {
  if (result == 1) {
    num->bits[bit / 32] = num->bits[bit / 32] | (1 << bit % 32);
  } else if (result == 0) {
    num->bits[bit / 32] = num->bits[bit / 32] & ~(1 << bit % 32);
  }
}

// распечатаем наш decimal от 0 до 32*
void print_decimal (s21_decimal num){
    for (int i = 3; i >= 0; i--) {
        printf("[");
        for (int j = 31; j >= 0; j--) {
            if (i==3 && j==23) printf("->");
            printf("%d", get_bit(num, i*32 + j));
            if (i==3 && j==16) printf("<-");
            if (i==3 && j==31) printf(".");
        }
        printf("] ");
    }
} 

// устанавливает минус
void set_minus(s21_decimal* num){
   set_bit(num, 127, 1);
}

// инициализируем децимал
s21_decimal init_decimal(int i1, int i2, int i3, int sign, int exp){
    s21_decimal d;
    d.bits[2] = i3;
    d.bits[1] = i2;
    d.bits[0] = i1;
    if (sign)   set_minus(&d);
    return d;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst){
    *dst = init_decimal(
    src<0 ? ~(src) + 1 : src,
    0,
    0, 
    src<0 ? 1:0, 
    0
    );
    return 0;
}



int main(){
    s21_decimal dec = {0};
    // set_minus(&dec);
    s21_from_int_to_decimal(-5, &dec);
    print_decimal(dec);
    return 0;
}
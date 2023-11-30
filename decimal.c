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

// распечатаем наш decimal от 0 до 127
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
    if (sign) set_minus(d.bits[3]);
    return d;
}

// узнать значение scale коэфициента масштабирования
int get_scale (s21_decimal num) {
    int mask = 0b11111111;
    mask <<= 16;
    mask = num.bits[3] & mask;
    mask >>= 16;
    return mask;
}

// установить значение scale коэфициента масштабирования, 0 - успешно, 1 - еррор
int set_scale (s21_decimal * num, int scale) {
    int result = 0;
    if (scale < 256 && scale >=0) {
        for (int i = 0; i < 8; i++) {
            set_bit(num, i + 16 + 96, scale % 2);
            scale >>= 1;
        }
    } else {
        result = 1;
    }
    return result;
}


int main(){
    s21_decimal dec = {0};
    set_minus(&dec);
    set_bit(&dec, 112, 1);
    set_bit(&dec, 113, 1);
    set_bit(&dec, 114, 1);
    set_bit(&dec, 119, 1);
    // set_bit(&dec, 119, 1);
    print_decimal(dec);
    printf("\n%d", get_scale(dec));
    set_scale(&dec, 127);
    printf("\n%d\n", get_scale(dec));
    print_decimal(dec);
    return 0;
}
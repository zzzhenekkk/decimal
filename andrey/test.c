#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define MASK_BITS 0b11111111111111111111111111111111
#define MINUS 0b10000000000000000000000000000000

typedef struct 
{
    unsigned int bits[4];
} s21_decimal;

unsigned int set_minus(unsigned int n){
    return (1<<31)|n;
}

void from_10_to_2(int n) {
    if (n == 0)  return;
    from_10_to_2(n/2);
    printf("%d", n%2);
}

// распечатать decimal в двоичном виде
void from_dec_2_bin(s21_decimal d) {
    for (int i = 3; i >=0; i--) {
        int shift = 30;
        for (unsigned int mask = 0x80000000; mask; mask>>=1){
            printf("%d", (mask&d.bits[i])>>(shift+1));
            shift--;
        }
        printf(" ");
    }
}

void show_decimal(s21_decimal d){
    for (int i = 3; i >= 0; i--){
        from_10_to_2(d.bits[i]);
        printf(" ");
    }
}

s21_decimal  init_decimal(int i1, int i2, int i3, int sign, int exp){
    s21_decimal d;
    d.bits[2] = i3;
    d.bits[1] = i2;
    d.bits[0] = i1;
    if (sign)   set_minus(d.bits[3]);
    return d;
}


int s21_from_int_to_decimal(int src, s21_decimal *dst){
    int i = 0;
    src = abs(src);
    while(i<96 && src > 0){
        int bits_grade = i/32;
        dst->bits[bits_grade] += pow(10,i)*(src%2);
        src/=2;
        i++;
    }
    for(int j = 0; j < i; j++){
        
    }
    printf("%i\n", dst->bits[0]);
    printf("%i\n", dst->bits[1]);
    printf("%i", dst->bits[2]);
    return 1;
}


int main(){
    // int n = set_minus(-2147483642);
    // printf("%i", n);
    s21_decimal dst = {0};
    dst = init_decimal(1,2,3,1,0);

    show_decimal(dst);
    printf("\n");

    from_dec_2_bin(dst);
    // for(int i = 0; i<4; i++)
    //     dst->bits[i] = 0;
    // int a = 7;
    // printf("%i", a<<3);
    // from_10_to_2(-3);
    // int res = s21_from_int_to_decimal(~(0b111), dst);
    return 0;
}
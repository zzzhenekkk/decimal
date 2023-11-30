#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct 
{
    unsigned int bits[4];
} s21_decimal;

void from_10_to_2(int n) {
    if (n == 0)  return;
    from_10_to_2(n/2);
    printf("%d", n%2);
}

void show_decimal(s21_decimal *d){
    
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
    s21_decimal *dst;
    for(int i = 0; i<4; i++)
        dst->bits[i] = 0;
    int a = 7;
    // printf("%i", a<<3);
    from_10_to_2(-3);
    // int res = s21_from_int_to_decimal(~(0b111), dst);
    return 0;
}
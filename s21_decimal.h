#ifndef S21_DECIMAL
#define S21_DECIMAL

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// количество битов большого массива
#define BITS_BIG 255
#define BITS_S21 95
#define BITS_B 8

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// биг децимал, для удобства операций сложения и проч чтобы не запариваться
typedef struct {
  unsigned int bits[BITS_B];  // мантисса
  int exponenta;              // экспонента
  int negative;               // отрицательное ли число
  int zero_left;              // количество нулей слева
  int one_position_left;      // старший бит
  int one_right;              // первая единица справа
} big_decimal;


//////////////////// для работы с big_decimal //////////////////////////

// приводим big_decimal к одной экспоненте
void normalize_big(big_decimal* bvalue_1, big_decimal* bvalue_2);

// сравнение мантис big, 1 больше = 1, 2 больше = -1, по ровну = 0
int compare_mantis_big(big_decimal* bvalue1, big_decimal* bvalue2);

// из бига в s21
int big_to_s21decimal(s21_decimal* result, big_decimal* result_big);

// переводим из биг ту с21 со старшим битом не больше 95
void big_to_s21decimal_95(big_decimal* result_big, s21_decimal* result);

// умножение мантис
int multiply_mantis_big(big_decimal bvalue_1, big_decimal* bvalue_2,
                        big_decimal* result);

// обнуялем мантису биг децимал
void zero_mantisa_big(big_decimal* result);

// полное обнуление decimal
void zero_big_decimal(big_decimal *result);

// для приведения к одной экспоненте, домножаем на 10 биг децимал
int multiply_10_mantis_big(big_decimal* bvalue, int def);

// для приведения к одной экспоненте, домножаем на 10 биг децимал не прибавляем экспоненту
int multiply_10_mantis_big_w_e(big_decimal *bvalue, int def);

// складываем мантисы big decimal
int sum_mantissa(big_decimal* bvalue_1, big_decimal* bvalue_2,
                 big_decimal* result);

// вычитание мантисы big decimal
void sub_mantis_big(big_decimal value_1, big_decimal value_2,
                    big_decimal* result);

// установить значение конкретного бита для big_decimal
void set_bit_big(big_decimal* num, int bit, int result);

// узнать значение конкретного бита для big decimal
int get_bit_big(big_decimal* num, int cur_bit);

// распечатаем наш decimal от 0 до 127
void print_big_decimal(big_decimal* num);

// сколько нулей слева, если занулеванное, то one_position_left = -1
void zeroes_left_big(big_decimal* bvalue);

// сдвигаем big_decimal налево по битам, если вылезли за пределы, вернет 1, если
// все ок то 0
int shift_left_big(big_decimal* bvalue, int def);

// сдвигаем big_decimal направо по битам, если вылезли за пределы, вернет 1,
// если все ок то 0
int shift_right_big(big_decimal* bvalue, int def);

// устанавливаем big_decimal по s21_decimal
void init_big(s21_decimal value, big_decimal* big);

// больше ли биг децимал 
int is_greater_big_decimal(big_decimal value_1,
                               big_decimal value_2);

// уравнивание биг децимал
int equal_bits_big_decimal(big_decimal *value_1,
                                  big_decimal *value_2);

// деление биг децимал
int div_big(big_decimal value_1, big_decimal value_2,
                        big_decimal *result);

// делим на 10 биг децимал уменьшая скейл
void div_10_big_decimal(big_decimal *dst, int n);

// подготовка к переводу к s21_decimal
int preparation_big_decimal(big_decimal *result, int scale);

// если big decimal = 0, то возвращает 0
int is_zero_big_decimal(big_decimal big);

// больше или равно биг дец 1 биг дец 2
int is_greater_or_equal_big_decimal(big_decimal value_1,
                                        big_decimal value_2);
                                        
// деление с big_decimal
void division(big_decimal val1, big_decimal val2, big_decimal *res, int mod);


//////////////////////////////////////////////////////////////////////////

// суммируем decimal и выводим в result
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// вычитание decimal
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// деление
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// узнать значение конкретного бита
int get_bit(s21_decimal num, int cur_bit);

// установить значение конкретного бита, bit - номер бита, result - какое
// значение записать
void set_bit(s21_decimal* num, int bit, int result);

// распечатаем наш decimal от 0 до 127
void print_decimal(s21_decimal num);

// узнать значение scale коэфициента масштабирования
int get_scale(s21_decimal num);

// установить значение scale коэфициента масштабирования, return 0 - успешно, 1
// - выход за границы
int set_scale(s21_decimal* num, int scale);

// инициализируем децимал
s21_decimal init_decimal(int i1, int i2, int i3, int sign, int exp);

// установить минус
void set_minus(s21_decimal* num, int sign);

// получить знак
int get_sign(s21_decimal num);

// перевести из int в decimal (всегда успешно)
int s21_from_int_to_decimal(int src, s21_decimal* dst);

// считает и возвращает количество нулей слева по мантиссе, чтобы проверять,
// можно ли реализовать сдвиг
int zeroes_left(s21_decimal value);

// зануляем s21_decimal
void zero_s21_decimal(s21_decimal * value);

// заполняем decimal под макс для проверки
void full_decimal(s21_decimal* num);

// проверяет на ноль s21_decimal
int is_zero_s21_decimal (s21_decimal value);


//////////////////////////////cравнения////////////////////////////////////

int s21_is_less(s21_decimal x1, s21_decimal x2);

int s21_is_less_or_equal(s21_decimal x1, s21_decimal x2);

int s21_is_greater(s21_decimal x1, s21_decimal x2);

int s21_is_greater_or_equal(s21_decimal x1, s21_decimal x2);

int s21_is_equal(s21_decimal x1, s21_decimal x2);

int s21_is_not_equal(s21_decimal x1, s21_decimal x2);


#endif  // S21_DECIMAL

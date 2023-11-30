

typedef struct 
{
    unsigned int bits[4];
} s21_decimal;


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

// распечатаем наш decimal от 0 до 
void print_decimal (s21_decimal* num){
    for (int i = 0; i < 4; i++) {
        printf("[");
        for (int j = 0; j < 32; i++) {
            printf("%d", get_bit(*num, i*32 + j));
        }
        printf("] ");
    }
}

int main(){
    s21_decimal dec;
    print_decimal(&dec);
    return 0;
}
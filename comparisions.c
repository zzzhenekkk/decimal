#include "decimal.h"

void manage_answer(int bit1, int bit2, int* ans){
    *ans = bit1-bit2;
    if(bit1 < bit2)
        *ans = -1;
    else if(bit1 > bit2)
        *ans = 1;
}
//если отрицательное, то скейл второго больше скейла первого
int scale_comparision(s21_decimal dec1, s21_decimal dec2){
    return get_scale(dec1) - get_scale(dec2);
}
void move_bits_by_one(s21_decimal *dec){
    for(int i = 2;i>=0;i--){
        dec->bits[i] = dec->bits[i] << 1;
        // если это старший и средний разряды, то мы должны перенести крайний бит в них, дабы его не потерять
        if(i>0){
            int bit = get_bit(*dec, i*32-1);
            set_bit(dec,i*32,bit);
        }
    }
}

//если влезло, то вернет 0, иначе 1
int equalize_scale(s21_decimal *dec, int scale_diff){
    int cur_scale = 0, last_bit = 0, ans = 0;
    while(cur_scale<scale_diff && (last_bit = get_bit(*dec,95)) == 0){
        move_bits_by_one(dec);
        cur_scale++;
    }
    // значит вышел раньше и это число больше, чем другое
    if(cur_scale<scale_diff)
        ans = 1;
    return ans;
}

int mantissa_comparision(s21_decimal dec1, s21_decimal dec2){
    int bit1 = 0;
    int bit2 = 0;
    //идти по битам, как только различие -> меняем анс и break
    for(int i = 95; i>=0; i--){
        bit1 = get_bit(dec1,i);
        bit2 = get_bit(dec2,i);
        if(bit1 ^ bit2)
            break;
    }
    return bit1-bit2;
}

// ans = -1, если левое меньше правого; ans = 0, если равны; 
// ans = 0, если равны
// ans = 1, если правое больше левого
int universal_comparision(s21_decimal dec1, s21_decimal dec2){
    int ans = 0, sign = 0;
    ans = get_sign(dec2) - get_sign(dec1);
    if(ans==0){
        sign = get_sign(dec1);
    //сравнить скейлы, у кого меньше, то сдвигаем побитово влево, но если крайний левый бит == 1
    //  -> значит это число больше, тк не влезать
        int scale_dif = scale_comparision(dec1,dec2);
        if(scale_dif>0){
            ans = equalize_scale(&dec2,scale_dif);
        }else if(scale_dif < 0){
            ans = -equalize_scale(&dec1,-scale_dif); //-1, тк второе выходит больше первого
        }
    }
    if(ans==0){
        ans = mantissa_comparision(dec1,dec2);
    }
    return (sign==0) ? ans : -ans;
}


int s21_is_less(s21_decimal dec1, s21_decimal dec2){
    return universal_comparision(dec1,dec2) == -1 ? 1:0;
}

int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2){
    return universal_comparision(dec1,dec2) != 1 ? 1:0;
}

int s21_is_greater(s21_decimal dec1, s21_decimal dec2){
    return universal_comparision(dec1,dec2) == 1 ? 1:0;
}

int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2){
    return universal_comparision(dec1,dec2) != -1 ? 1:0;
}

int s21_is_equal(s21_decimal dec1, s21_decimal dec2){
    return universal_comparision(dec1,dec2) == 0 ? 1:0;
}

int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2){
    return universal_comparision(dec1,dec2) != 0 ? 1:0;
}
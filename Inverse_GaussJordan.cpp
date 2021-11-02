#include <cassert>
#include "RationalMatrix.h"

RationalMatrix RationalMatrix::inverse_GaussJordan() const
{
    assert(rows==cols); //перевірка, що матриця квадратна
    RationalMatrix tmp = *this; //копіювання поточної матриці для проведення перетворень без її зміни
    RationalMatrix res(rows, cols); //створення результуючої матриці такого ж розміру (поки що нульової)
    for(size_t i=0; i<rows; i++) res(i,i)=Rational(1,1); //перетворення результуючої матриці на одиничну
    Rational k;
    for(size_t i=0; i<rows; i++) //цикл по всім рядкам
    {
        if(tmp(i,i).numerator==0) //діагональний елемент = 0 (треба переставляти рядки)
        {
            size_t c = i;
            while(tmp(c,i).numerator==0) //пошук першого не нульового елемента в тому ж стовпці
            {
                c++;
                if(c==rows) return {1,1}; //якщо такого елемента немає - оберненої матриці не існує (повертається нульова матриця 1х1)
            }
            tmp.swapRows(i,c); //перестановка рядків
            res.swapRows(i,c); //повторення попередньої операції над результуючою матрицею
        }
        k = tmp(i,i);
        tmp(i) /= k; //перетворення діагонального елемента на 1 діленням всього i-го рядка [tmp(i) = tmp(i)/k]
        res(i) /= k; //повторення попередньої операції над результуючою матрицею [res(i) = res(i)/k]
        for(size_t j=0; j<rows; j++) //занулення інших елементів стовпчика
        {
            if(j==i) continue; //сам діагональний елемент змінювати не потрібно
            k = tmp(j,i);
            tmp(j) -= tmp(i)*k; //занулення елемента [tmp(j) = tmp(j)-tmp(i)*k]
            res(j) -= res(i)*k; //повторення попередньої операції над результуючою матрицею [res(j) = res(j)-res(i)*k]
        }
    }
    return res;
}

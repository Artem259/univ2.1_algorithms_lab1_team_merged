#include <cassert>
#include "RationalMatrix.h"
//-----------------------------------------------------------------------------------
//функція для знаходження окремих стовпчиків матриці, оберненої до L
void RationalMatrix::col_L_inverse(RationalMatrix &L, std::vector<Rational>& E,
    std::vector<Rational>& Z, const size_t &rows)
{
    Rational sum(0, 1);
    for (size_t i = 0; i < rows; i++) {
        sum = Rational(0, 1);
        for (size_t k = 0; k < i; k++)
            sum = sum + Z[k] * L(i, k);
        Z[i] = E[i] - sum;
    }
}
//функція для знаходження окремих стовпчиків матриці, оберненої до A (така матриця позначена через В)
void RationalMatrix::col_A_inverse(RationalMatrix &U, std::vector<Rational>& Z, 
    std::vector<Rational>& B, const size_t &rows)
{
    Rational sum(0, 1);
    for (int i = rows - 1; i >= 0; i--) {
        sum = Rational(0, 1);
        for (int k = i + 1; k < rows; k++) {
            sum = sum + (B[k] * (U(i, k) / U(i, i)));
        }
        B[i] = Z[i] / U(i, i) - sum;
    }
}
//перевіряємо, чи є матриця перестановок одиничною
bool RationalMatrix::matrix_isE(RationalMatrix& P, const size_t& rows) {
    int counter = 0;
    for (int i = 0; i < rows; i++) {
        if (P(i, i) == Rational(1, 1))
            counter++;
    }
    if (counter == rows) return true;
    return false;
}
RationalMatrix RationalMatrix::inverse_byLU() {
    assert(rows == cols); //перевірка, що матриця квадратна
    RationalMatrix U = *this; //створення матриці U, ідентичної початковій 
    RationalMatrix L(rows, cols); //створення L-матриці такого ж розміру (поки що нульової)
    RationalMatrix E(rows, cols); //створення одиничної матриці такого ж розміру (поки що нульової)
    RationalMatrix B(rows, cols); //створення результуючої матриці такого ж розміру (поки що нульової)
    RationalMatrix P(rows, cols); //створення матриці перестановок рядків (поки що нульової)
    Rational l;
    std::vector<Rational> tempL(cols), tempB(cols);
    for (size_t i = 0; i < rows; i++) {
        L(i, i) = Rational(1, 1); //перетворення L-матриці на одиничну
        E(i, i) = Rational(1, 1); //перетворення E-матриці на одиничну
        P(i, i) = Rational(1, 1); //перетворення P-матриці на одиничну
        tempL.push_back(Rational(0, 1));//заповнення допоміжних векторів  нулями
        tempB.push_back(Rational(0, 1));
    }
    for (size_t i = 0; i < rows; i++) //цикл по всім рядкам
    {
        if (U(i, i).numerator == 0) //діагональний елемент = 0 (треба переставляти рядки)
        {
            size_t c = i;
            while (U(c, i).numerator == 0) //пошук першого не нульового елемента в тому ж стовпці
            {
                c++;
                if (c == rows) return { 1,1 }; //якщо такого елемента немає - помилка (повертається порожня матриця)
            }
            U.swapRows(i, c); //переставляємо рядки матриці U
            P.swapRows(i, c); //переставляємо рядки матриці P, на яку в кінці будемо домножати оберенену
        }
        for (size_t j = i + 1; j < rows; j++) //занулення інших елементів стовпчика (елементи на головній діагоналі і вище неї змінювати не потрібно)
        {
            l = U(j, i) / U(i, i);
            U(j) -= U(i) * l; //занулення елемента під головною діагоналлю
            L(j, i) = l; // присвоюємо значення l відповідному елементу матриці L
        }
        for (size_t e = 0; e < cols; e++) {
            col_L_inverse(L, E(e), tempL, rows);
            col_A_inverse(U, tempL, tempB, rows);
            for (size_t r = 0; r < rows; r++)
                B(r, e) = tempB[r];
        }
    }
    bool check = matrix_isE(P, rows);
    if (check) return B;
    quick_matrix_mul(B, P, E, rows);
    return E;
}
//-----------------------------------------------------------------------------------

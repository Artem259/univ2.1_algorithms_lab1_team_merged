#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "Rational.h"

class RationalMatrix
{
private:
    size_t rows, cols;
    std::vector<std::vector<Rational>> matrix;
public:
    RationalMatrix();
    RationalMatrix(const size_t &_rows, const size_t &_cols); //конструктор нульової матриці заданого розміру
    explicit RationalMatrix(const std::vector<std::vector<Rational>> &matrix); //конструктор заповненої матриці
    void resize(const size_t &_rows, const size_t &_cols); //змінити розмір матриці
    void swapRows(const size_t &row1, const size_t &row2); //поміняти місцями рядки матриці
    std::vector<Rational>& operator ()(const size_t &row); //повертяє посилання на рядок матриці
    Rational& operator ()(const size_t &row, const size_t &col); //повертяє посилання на елемент матриці

    friend std::ostream& operator <<(std::ostream &ofs, const RationalMatrix &matrix);
    friend bool operator ==(const RationalMatrix &m1, const RationalMatrix &m2);
    friend bool operator !=(const RationalMatrix &m1, const RationalMatrix &m2);


    //---------------------------------------------------------------------------------------------------------------//
    //Поляков Артем
    RationalMatrix inverse_GaussJordan() const; //повертає обернену матрицю
    //---------------------------------------------------------------------------------------------------------------//
    //Дзюгал Ольга
    RationalMatrix inverse_byLU(); //повертає обернену матрицю, використовуючи метод LU-розкладу
    void col_L_inverse(RationalMatrix &L, std::vector<Rational>& E, std::vector<Rational>& Z, const size_t &rows);
    void col_A_inverse(RationalMatrix &U, std::vector<Rational>& Z, std::vector<Rational>& B, const size_t &rows);
    //---------------------------------------------------------------------------------------------------------------//
    //Кілко Павло
    void make(const size_t &n, const size_t &m);
    void random(const long long &n);
    void copy(const RationalMatrix &m, const size_t &v0, const size_t &h0, const size_t &v1, const size_t &h1);
    friend bool matrix_sum (const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c);
    friend bool matrix_sub (const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c);
    friend bool check(RationalMatrix &a, RationalMatrix &b, RationalMatrix &c);
    friend void quad_matrix_fusion(RationalMatrix &m, const RationalMatrix &a, const RationalMatrix &b, const RationalMatrix &c, const RationalMatrix &d, const size_t &k);
    friend bool normal_matrix_mul(const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c);
    friend void quick_matrix_mul(const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c, const size_t &k);
    friend bool strassen_matrix_mul(RationalMatrix &a, RationalMatrix &b, RationalMatrix &c);
    //---------------------------------------------------------------------------------------------------------------//


};

bool matrix_sum (const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c);
bool matrix_sub (const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c);
bool check(RationalMatrix &a, RationalMatrix &b, RationalMatrix &c);
void quad_matrix_fusion(RationalMatrix &m, const RationalMatrix &a, const RationalMatrix &b, const RationalMatrix &c, const RationalMatrix &d, const size_t &k);
bool normal_matrix_mul(const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c);
void quick_matrix_mul(const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c, const size_t &k);
bool strassen_matrix_mul(RationalMatrix &a, RationalMatrix &b, RationalMatrix &c);

std::vector<Rational> operator +(const std::vector<Rational> &row, const Rational &k); //рядок=рядок+константа
std::vector<Rational> operator -(const std::vector<Rational> &row, const Rational &k); //рядок=рядок-константа
std::vector<Rational> operator *(const std::vector<Rational> &row, const Rational &k); //рядок=рядок*константа
std::vector<Rational> operator /(const std::vector<Rational> &row, const Rational &k); //рядок=рядок/константа
std::vector<Rational> operator +(const std::vector<Rational> &row1, const std::vector<Rational> &row2); //рядок=рядок+рядок
std::vector<Rational> operator -(const std::vector<Rational> &row1, const std::vector<Rational> &row2); //рядок=рядок-рядок
std::vector<Rational> operator *(const std::vector<Rational> &row1, const std::vector<Rational> &row2); //рядок=рядок*рядок
std::vector<Rational> operator /(const std::vector<Rational> &row1, const std::vector<Rational> &row2); //рядок=рядок/рядок

void operator +=(std::vector<Rational> &row, const Rational &k); //рядок+=константа
void operator -=(std::vector<Rational> &row, const Rational &k); //рядок-=константа
void operator *=(std::vector<Rational> &row, const Rational &k); //рядок*=константа
void operator /=(std::vector<Rational> &row, const Rational &k); //рядок/=константа
void operator +=(std::vector<Rational> &row1, const std::vector<Rational> &row2); //рядок+=рядок
void operator -=(std::vector<Rational> &row1, const std::vector<Rational> &row2); //рядок-=рядок
void operator *=(std::vector<Rational> &row1, const std::vector<Rational> &row2); //рядок*=рядок
void operator /=(std::vector<Rational> &row1, const std::vector<Rational> &row2); //рядок/=рядок

#endif
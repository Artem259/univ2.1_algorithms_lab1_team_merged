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
    RationalMatrix(const size_t &_rows, const size_t &_cols); //конструктор нульової матриці заданого розміру
    explicit RationalMatrix(const std::vector<std::vector<Rational>> &matrix); //конструктор заповненої матриці
    void resize(const size_t &_rows, const size_t &_cols); //змінити розмір матриці
    void swapRows(const size_t &row1, const size_t &row2); //поміняти місцями рядки матриці
    void fillRandom(const long long &n); //заповнення матриці випадковими значеннями
    std::vector<Rational>& operator ()(const size_t &row); //повертяє посилання на рядок матриці
    Rational& operator ()(const size_t &row, const size_t &col); //повертяє посилання на елемент матриці
    RationalMatrix inverse() const; //повертає обернену матрицю

    friend std::ostream& operator <<(std::ostream &ofs, const RationalMatrix &matrix);
    friend bool operator ==(const RationalMatrix &m1, const RationalMatrix &m2);
    friend bool operator !=(const RationalMatrix &m1, const RationalMatrix &m2);
};

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
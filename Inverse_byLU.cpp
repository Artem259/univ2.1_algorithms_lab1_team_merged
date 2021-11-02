#include <cassert>
#include "RationalMatrix.h"
//-----------------------------------------------------------------------------------
//������� ��� ����������� ������� ��������� �������, �������� �� L
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
//������� ��� ����������� ������� ��������� �������, �������� �� A (���� ������� ��������� ����� �)
void RationalMatrix::col_A_inverse(RationalMatrix &U, std::vector<Rational>& Z, std::vector<Rational>& B, const size_t &rows)
{
    Rational sum(0, 1);
    for (int i = rows - 1; i >= 0; i--) {
        sum = Rational(0, 1);
        for (size_t k = i + 1; k < rows; k++) {
            sum = sum + (B[k] * (U(i, k) / U(i, i)));
        }
        B[i] = Z[i] / U(i, i) - sum;
    }
}
RationalMatrix RationalMatrix::inverse_byLU() {
    assert(rows == cols); //��������, �� ������� ���������
    RationalMatrix U = *this; //��������� ������� U, ��������� ��������� 
    RationalMatrix L(rows, cols); //��������� L-������� ������ � ������ (���� �� �������)
    RationalMatrix E(rows, cols); //��������� �������� ������� ������ � ������ (���� �� �������)
    RationalMatrix B(rows, cols); //��������� ����������� ������� ������ � ������ (���� �� �������)
    Rational l;
    std::vector<Rational> tempL(cols), tempB(cols);
    for (size_t i = 0; i < rows; i++) {
        L(i, i) = Rational(1, 1); //������������ L-������� �� ��������
        E(i, i) = Rational(1, 1); //������������ E-������� �� ��������
        tempL.push_back(Rational(0, 1));//���������� ��������� �������  ������
        tempB.push_back(Rational(0, 1));
    }
    for (size_t i = 0; i < rows; i++) //���� �� ��� ������
    {
        if (U(i, i).numerator == 0) //����������� ������� = 0 (����� ������������ �����)
        {
            size_t c = i;
            while (U(c, i).numerator == 0) //����� ������� �� ��������� �������� � ���� � �������
            {
                c++;
                if (c == rows) return { 1,1 }; //���� ������ �������� ���� - ������� (����������� ������� �������)
            }
            U.swapRows(i, c); 
        }
        for (size_t j = 0; j < rows; j++) //��������� ����� �������� ���������
        {
            if (j <= i) continue; //�������� �� ������� ������� � ���� �� �������� �� �������
            l = U(j, i) / U(i, i);
            U(j) -= U(i) * l; //��������� �������� �� �������� ���������
            L(j, i) = l; // ���������� �������� l ���������� �������� ������� L
        }
        for (size_t e = 0; e < cols; e++) {
            col_L_inverse(L, E(e), tempL, rows);
            col_A_inverse(U, tempL, tempB, rows);
            for (size_t r = 0; r < rows; r++)
                B(r, e) = tempB[r];
        }
    }
    return B;
}
//-----------------------------------------------------------------------------------
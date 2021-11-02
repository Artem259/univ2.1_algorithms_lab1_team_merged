#include "RationalMatrix.h"

void RationalMatrix::make(const size_t &n, const size_t &m)
{
    rows = n;
    cols = m;
    matrix.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        matrix[i].resize(m);
        for (size_t j = 0; j < m; j++)
        {
            long long a, b;
            char c;
            while(true)
            {
                std::cin >> a >> c >> b;
                if (c == '/') break;
            }
            Rational r(a, b);
            matrix[i][j] = r;
        }
    }
}

void RationalMatrix::random(const long long &n)
{
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < cols; j++)
        {
            matrix[i][j].random(std::abs(n));
        }
    }
}

void RationalMatrix::copy(const RationalMatrix &m, const size_t &v0, const size_t &h0, const size_t &v1, const size_t &h1)
{
    if(v0 < 0 || v0 >= m.rows || v1 < 0 || v1 >= m.rows || v0 > v1)
        return;
    if(h0 < 0 || h0 >= m.cols || h1 < 0 || h1 >= m.cols || h0 > h1)
        return;
    size_t v01 = v1 - v0 + 1;
    size_t h01 = h1 - h0 + 1;
    rows = v01;
    cols = h01;
    matrix.resize(v01);
    for (size_t i = 0; i < v01; i++)
    {
        matrix[i].assign(m.matrix[v0+i].begin() + h0, m.matrix[v0+i].begin() + h1 + 1);
    }
}

bool matrix_sum (const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c)
{
    if (a.rows != b.rows || a.cols != b.cols)
        return false;

    c.rows = a.rows;
    c.cols = a.cols;

    c.matrix.resize(c.rows);
    for (size_t i = 0; i < c.rows; i++)
    {
        c.matrix[i].resize(c.cols);
        for (size_t j = 0; j < c.cols; j++)
        {
            c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        }
    }
    return true;
}

bool matrix_sub (const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c)
{
    if (a.rows != b.rows || a.cols != b.cols)
        return false;

    c.rows = a.rows;
    c.cols = a.cols;

    c.matrix.resize(c.rows);
    for (size_t i = 0; i < c.rows; i++)
    {
        c.matrix[i].resize(c.cols);
        for (size_t j = 0; j < c.cols; j++)
        {
            c.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
        }
    }
    return true;
}

bool check(RationalMatrix &a, RationalMatrix &b, RationalMatrix &c)
{
    if (a.cols != b.rows)
        return false;

    size_t k = std::max(std::max(a.rows, b.cols), a.cols);

    if ((k & (k - 1)))
    {
        size_t t = 1;
        while (k > t) t <<= 1;
        k = t;
    }

    a.resize(k, k);
    b.resize(k, k);
    c.resize(k, k);

    return true;
}

void quad_matrix_fusion(RationalMatrix &m, const RationalMatrix &a, const RationalMatrix &b, const RationalMatrix &c, const RationalMatrix &d, const size_t &k)
{
    for (size_t i = 0; i < k/2; i++)
    {
        for (size_t j = 0; j < k/2; j++)
        {
            m.matrix[i][j] = a.matrix[i][j];
            m.matrix[i][j+k/2] = b.matrix[i][j];
            m.matrix[i+k/2][j] = c.matrix[i][j];
            m.matrix[i+k/2][j+k/2] = d.matrix[i][j];
        }
    }
}

bool normal_matrix_mul(const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c)
{
    if (a.cols != b.rows)
        return false;

    c.rows = a.rows;
    c.cols = b.cols;

    c.matrix.resize(c.rows);
    for (size_t i = 0; i < c.rows; i++)
    {
        c.matrix[i].resize(c.cols);
        for (size_t j = 0; j < c.cols; j++)
        {
            Rational r;
            c.matrix[i][j] = c.matrix[i][j] * r;
            for (size_t t = 0; t < c.cols; t++)
                c.matrix[i][j] = c.matrix[i][j] + a.matrix[i][t] * b.matrix[t][j];
        }
    }

    return true;
}

void quick_matrix_mul(const RationalMatrix &a, const RationalMatrix &b, RationalMatrix &c, const size_t &k)
{
    if(k <= 64) // k can range from 32 to 128 depending on the computing power
    {
        // Normal multiplication
        normal_matrix_mul(a, b, c);
        return;
    }

    RationalMatrix a11, a12, a21, a22;
    RationalMatrix b11, b12, b21, b22;
    RationalMatrix c11, c12, c21, c22;
    RationalMatrix d1, d2; // additional sub-matrices for calculations
    RationalMatrix p1(k/2, k/2), p2(k/2, k/2), p3(k/2, k/2), p4(k/2, k/2), p5(k/2, k/2), p6(k/2, k/2), p7(k/2, k/2);

    // Division of matrices A and B into 4 sub-matrices
    a11.copy(a, 0, 0, k/2-1, k/2-1);
    a12.copy(a, 0, k/2, k/2-1, k-1);
    a21.copy(a, k/2, 0, k-1, k/2-1);
    a22.copy(a, k/2, k/2, k-1, k-1);

    b11.copy(b, 0, 0, k/2-1, k/2-1);
    b12.copy(b, 0, k/2, k/2-1, k-1);
    b21.copy(b, k/2, 0, k-1, k/2-1);
    b22.copy(b, k/2, k/2, k-1, k-1);

    // These calculations can be parallelized across multiple processor cores
    matrix_sum(a11, a22, d1);
    matrix_sum(b11, b22, d2);
    quick_matrix_mul(d1, d2, p1, k/2);

    matrix_sum(a21, a22, d1);
    quick_matrix_mul(d1, b11, p2, k/2);

    matrix_sub(b12, b22, d2);
    quick_matrix_mul(a11, d2, p3, k/2);

    matrix_sub(b21, b11, d2);
    quick_matrix_mul(a22, d2, p4, k/2);

    matrix_sum(a11, a12, d1);
    quick_matrix_mul(d1, b22, p5, k/2);

    matrix_sub(a21, a11, d1);
    matrix_sum(b11, b12, d2);
    quick_matrix_mul(d1, d2, p6, k/2);

    matrix_sub(a12, a22, d1);
    matrix_sum(b21, b22, d2);
    quick_matrix_mul(d1, d2, p7, k/2);

    matrix_sum(p1, p4, d1);
    matrix_sub(p7, p5, d2);
    matrix_sum(d1, d2, c11);

    matrix_sum(p3, p5, c12);

    matrix_sum(p2, p4, c21);

    matrix_sub(p1, p2, d1);
    matrix_sum(p3, p6, d2);
    matrix_sum(d1, d2, c22);

    // Merging 4 submatrices into one
    quad_matrix_fusion(c, c11, c12, c21, c22, k);
}

bool strassen_matrix_mul(RationalMatrix &a, RationalMatrix &b, RationalMatrix &c)
{
    // Maintain the initial sizes of matrices to return their previous configurations after multiplication.
    size_t n = a.rows;
    size_t m = a.cols;
    size_t p = b.cols;

    // Testing the criterion for matrix multiplication.
    // Function when returning true, matrix sizes will be powers of two
    if(!check(a, b, c))
        return false;

    // Quick multiplication
    quick_matrix_mul(a, b, c, a.cols);

    // Return to original dimensions
    a.resize(n, m);
    b.resize(m, p);
    c.resize(n, p);

    return true;
}
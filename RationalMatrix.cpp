#include <cassert>
#include "RationalMatrix.h"

RationalMatrix::RationalMatrix(const size_t &_rows, const size_t &_cols)
{
    matrix = {};
    rows = 0;
    cols = 0;
    this->resize(_rows, _cols);
}
RationalMatrix::RationalMatrix(const std::vector<std::vector<Rational>> &_matrix)
{
    matrix = {};
    rows = 0;
    cols = 0;
    this->resize(_matrix.size(), _matrix[0].size());
    for(size_t i=0; i<rows; i++)
    {
        assert(_matrix[i].size()==cols);
        for(size_t j=0; j<cols; j++)
        {
            matrix[i][j] = _matrix[i][j];
        }
    }
}
void RationalMatrix::resize(const size_t &_rows, const size_t &_cols)
{
    assert(_rows!=0 && _cols!=0);
    matrix.resize(_rows);
    for(auto &row: matrix)
    {
        row.resize(_cols);
    }
    rows = _rows;
    cols = _cols;
}
void RationalMatrix::swapRows(const size_t &row1, const size_t &row2)
{
    assert(row1<rows && row2<rows);
    swap(matrix[row1], matrix[row2]);
}
void RationalMatrix::fillRandom(const long long &n)
{
    for(auto &row: matrix)
    {
        for(auto &col: row)
        {
            col.random(n);
        }
    }
}
std::vector<Rational>& RationalMatrix::operator ()(const size_t &row)
{
    assert(row<rows);
    return matrix[row];
}
Rational& RationalMatrix::operator ()(const size_t &row, const size_t &col)
{
    assert(row<rows && col<cols);
    return matrix[row][col];
}

std::vector<Rational> operator +(const std::vector<Rational> &row, const Rational &k)
{
    size_t len = row.size();
    std::vector<Rational> res(len);
    for(size_t i=0; i<len; i++)
    {
        res[i] = row[i]+k;
    }
    return res;
}
std::vector<Rational> operator -(const std::vector<Rational> &row, const Rational &k)
{
    return row+(k*Rational{-1,1});
}
std::vector<Rational> operator *(const std::vector<Rational> &row, const Rational &k)
{
    size_t len = row.size();
    std::vector<Rational> res(len);
    for(size_t i=0; i<len; i++)
    {
        res[i] = row[i]*k;
    }
    return res;
}
std::vector<Rational> operator /(const std::vector<Rational> &row, const Rational &k)
{
    size_t len = row.size();
    std::vector<Rational> res(len);
    for(size_t i=0; i<len; i++)
    {
        res[i] = row[i]/k;
    }
    return res;
}
std::vector<Rational> operator +(const std::vector<Rational> &row, const std::vector<Rational> &row2)
{
    size_t len = row.size();
    assert(row2.size()==len);
    std::vector<Rational> res(len);
    for(size_t i=0; i<len; i++)
    {
        res[i] = row[i]+row2[i];
    }
    return res;
}
std::vector<Rational> operator -(const std::vector<Rational> &row1, const std::vector<Rational> &row2)
{
    return row1+(row2*Rational{-1,1});
}
std::vector<Rational> operator *(const std::vector<Rational> &row1, const std::vector<Rational> &row2)
{
    size_t len = row1.size();
    assert(row2.size()==len);
    std::vector<Rational> res(len);
    for(size_t i=0; i<len; i++)
    {
        res[i] = row1[i]*row2[i];
    }
    return res;
}
std::vector<Rational> operator /(const std::vector<Rational> &row1, const std::vector<Rational> &row2)
{
    size_t len = row1.size();
    assert(row2.size()==len);
    std::vector<Rational> res(len);
    for(size_t i=0; i<len; i++)
    {
        res[i] = row1[i]/row2[i];
    }
    return res;
}

void operator +=(std::vector<Rational> &row, const Rational &k)
{
    size_t len = row.size();
    for(size_t i=0; i<len; i++)
    {
        row[i] = row[i]+k;
    }
}
void operator -=(std::vector<Rational> &row, const Rational &k)
{
    size_t len = row.size();
    for(size_t i=0; i<len; i++)
    {
        row[i] = row[i]-k;
    }
}
void operator *=(std::vector<Rational> &row, const Rational &k)
{
    size_t len = row.size();
    for(size_t i=0; i<len; i++)
    {
        row[i] = row[i]*k;
    }
}
void operator /=(std::vector<Rational> &row, const Rational &k)
{
    size_t len = row.size();
    for(size_t i=0; i<len; i++)
    {
        row[i] = row[i]/k;
    }
}
void operator +=(std::vector<Rational> &row1, const std::vector<Rational> &row2)
{
    size_t len = row1.size();
    assert(row2.size()==len);
    for(size_t i=0; i<len; i++)
    {
        row1[i] = row1[i]+row2[i];
    }
}
void operator -=(std::vector<Rational> &row1, const std::vector<Rational> &row2)
{
    size_t len = row1.size();
    assert(row2.size()==len);
    for(size_t i=0; i<len; i++)
    {
        row1[i] = row1[i]-row2[i];
    }
}
void operator *=(std::vector<Rational> &row1, const std::vector<Rational> &row2)
{
    size_t len = row1.size();
    assert(row2.size()==len);
    for(size_t i=0; i<len; i++)
    {
        row1[i] = row1[i]*row2[i];
    }
}
void operator /=(std::vector<Rational> &row1, const std::vector<Rational> &row2)
{
    size_t len = row1.size();
    assert(row2.size()==len);
    for(size_t i=0; i<len; i++)
    {
        row1[i] = row1[i]/row2[i];
    }
}

std::ostream& operator <<(std::ostream &ofs, const RationalMatrix &matrix)
{
    for(auto &row: matrix.matrix)
    {
        for(auto &col: row)
        {
            ofs << col << " ";
        }
        ofs << std::endl;
    }
    return ofs;
}
bool operator ==(const RationalMatrix &m1, const RationalMatrix &m2)
{
    if((m1.rows!=m2.rows) || (m1.cols!=m2.cols)) return false;
    for(size_t i=0; i<m1.rows; i++)
    {
        for(size_t j=0; j<m1.cols; j++)
        {
            if(m1.matrix[i][j] != m2.matrix[i][j]) return false;
        }
    }
    return true;
}
bool operator !=(const RationalMatrix &m1, const RationalMatrix &m2)
{
    return !(m1==m2);
}
//
// Created by Pavel on 10/16/2021.
//

#ifndef LAB1_RATIONAL_H
#define LAB1_RATIONAL_H

#include <iostream>

long long gcd(long long x, long long y);
void reduction(long long &x, long long &y);

class Rational
{
public:
    long long numerator;
    long long denominator;

    Rational();

    explicit Rational(long long n, long long d = 1);

    void random(const long long &n);

    friend std::ostream& operator << (std::ostream &out, const Rational &r);

    friend Rational operator + (const Rational &r1,const Rational &r2);
    friend Rational operator - (const Rational &r1,const Rational &r2);
    friend Rational operator * (const Rational &r1,const Rational &r2);
    friend Rational operator / (const Rational &r1, const Rational &r2);

    friend bool operator == (const Rational &r1, const Rational &r2);
};

#endif //LAB1_RATIONAL_H

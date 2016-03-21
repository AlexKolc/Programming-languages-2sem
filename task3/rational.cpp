#include "rational.h"

int rational::simplify(int& a, int& b)
{
    int x = gcd(a, b);
    a = a / x;
    b = b / a;
}

int rational::gcd(int a, int b) 
{
    while (a && b)
        if (a > b)
            a %= b;
        else
            b %= a;
    return a + b;
}

rational::rational(int i)
{
    n = i;
    d = 1;
}

rational::rational(int num, int denom)
{
    n = num;
    d = denom;
    simplify(n, d);
}

int rational::getNum() const
{
    return n;
}

int rational::getDenom() const
{
    return d;
}


rational rational::operator +(rational const & x) const
{
    int xNum = n * x.d + d * x.n;
    int xDenom = d * x.d;
    simplify(xNum, xDenum);
    return rational(xNum, xDenom);
}

rational rational::operator -(rational const & x) const
{
    int xNum = n * x.d - d * x.n;
    int xDenom = d * x.d;
    simplify(xNum, xDenum);
    return rational(xNum, xDenom);
}

rational rational::operator *(rational const & x) const
{
    int xNum = n * x.n;
    int xDenom = d * x.d;
    simplify(xNum, xDenum);
    return rational(xNum, xDenom);
}

rational rational::operator /(rational const & x) const
{
    int xNum = n * x.d;
    int xDenom = d * x.n;
    simplify(xNum, xDenum);
    return rational(xNum, xDenom);
}

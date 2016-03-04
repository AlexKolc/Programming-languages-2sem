#include "rational.h"

int gcd(int a, int b) 
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
    int x = gcd(num, denom);
    n = num / x;
    d = denom / x;
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
    return rational(xNum, xDenom);
}

rational rational::operator -(rational const & x) const
{
    int xNum = n * x.d - d * x.n;
    int xDenom = d * x.d;
    return rational(xNum, xDenom);
}

rational rational::operator *(rational const & x) const
{
    int xNum = n * x.n;
    int xDenom = d * x.d;
    return rational(xNum, xDenom);
}

rational rational::operator /(rational const & x) const
{
    int xNum = n * x.d;
    int xDenom = d * x.n;
    return rational(xNum, xDenom);
}

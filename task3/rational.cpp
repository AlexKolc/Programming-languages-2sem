#include "rational.h"

int rational::gcd(int a, int b) const {
    while (a != b) 
        if (a > b)
            a -= b;
        else
            b -= a;
    return a;
}

rational::rational(int num, int denom) {
    int temp = gcd(num, denom);
    n = num / temp;
    d = denom / temp;
}

rational::rational(int num) {
    n = num;
    d = 1;
}

int rational::getNum() const {
    return n;
}

int rational::getDenom() const {
    return d;
}

rational rational::operator +(rational const & x) const
{
    int xNum1 = getNum();
    int xDenom1 = getDenom();
    int xNum2 = x.getNum();
    int xDenom2 = x.getDenom();
    return rational(xNum1 * xDenom2 + xDenom1 * xNum2, xDenom1 * xDenom2);
}

rational rational::operator -(rational const & x) const
{
    int xNum1 = getNum();
    int xDenom1 = getDenom();
    int xNum2 = x.getNum();
    int xDenom2 = x.getDenom();
    return rational(xNum1 * xDenom2 - xDenom1 * xNum2, xDenom1 * xDenom2);
}

rational rational::operator *(rational const & x) const
{
    return rational(getNum() * x.getNum(), getDenom() * x.getDenom());
}

rational rational::operator /(rational const & x) const
{
    return rational(getNum() * x.getDenom(), getDenom() * x.getNum());
}

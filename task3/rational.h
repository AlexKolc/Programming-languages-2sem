#ifndef TASK3_RATIONAL_H
#define TASK3_RATIONAL_H

class rational
{
    private:
        int n;
        int d;
        static int gcd(int, int);
    public:
        rational(int i);
        rational(int num, int denom);
        int getNum() const;
        int getDenom() const;
        rational operator +(rational const & x) const;
        rational operator -(rational const & x) const;
        rational operator *(rational const & x) const;
        rational operator /(rational const & x) const;
};

#endif

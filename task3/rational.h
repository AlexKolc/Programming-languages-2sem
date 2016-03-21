#ifndef TASK3_RATIONAL_H
#define TASK3_RATIONAL_H

class rational
{
    private:
        int n;
        int d;
    public:
        rational(int i);
        rational(int num, int denum);
        int getNum() const;
        int getDenom() const;
        rational operator +(rational const & x) const;
        rational operator -(rational const & x) const;
        rational operator *(rational const & x) const;
        rational operator /(rational const & x) const;
};

#endif

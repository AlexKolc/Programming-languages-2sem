class rational
{
    private:
        int n;
        int d;
        int gcd(int, int) const;
    public:
        rational(int);
        rational(int, int);
        int getNum() const;
        int getDenom() const;
        rational operator +(rational const & x) const;
        rational operator -(rational const & x) const;
        rational operator *(rational const & x) const;
        rational operator /(rational const & x) const;
};


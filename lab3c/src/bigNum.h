#ifndef LAB3C_BIGNUM_H
#define LAB3C_BIGNUM_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <limits>

namespace Prog3c {

    class bigNum{

    private:
        static const int SZ = 47;
        char *Num;
        int n; //кол-во разрядов

    public:
        bigNum();
        bigNum(long int x);
        bigNum(const char* str);
        bigNum& Set(const char* str);
        bigNum(bigNum&& t)  noexcept :n(t.n), Num(t.Num) { t.Num = nullptr; }
        ~bigNum() { delete[]Num; }
        bigNum(const bigNum&);

        friend bigNum operator +(const bigNum& first, const bigNum& second);
        friend bigNum operator -(const bigNum& first, const bigNum& second) { return first + (-second); };
        const bigNum operator -() const;
        bigNum operator ~() const;
        bigNum& operator =(const bigNum&);
        bigNum& operator =(bigNum&&) noexcept ;
        bigNum& operator <<=(int);
        bigNum& operator >>=(int);
        friend bool operator >(const bigNum&, const bigNum&);
        friend bool operator <(const bigNum&, const bigNum&);
        friend bool operator ==(const bigNum&, const bigNum&);
        friend std::ostream& operator <<(std::ostream&, const bigNum&);
        friend std::istream& operator >>(std::istream&, bigNum&);
        bool CompareAbs(const bigNum&) const;
        operator int() const;
        bigNum& resize(int, bool);
    };
    int digit_plus(const char *);
}


#endif //LAB3C_BIGNUM_H
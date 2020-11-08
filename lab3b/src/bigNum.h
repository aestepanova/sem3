#ifndef LAB3B_BIGNUM_H
#define LAB3B_BIGNUM_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <limits>

namespace Prog3b {

    class bigDecNum{

    private:
        static const int SZ = 47;
        char Num[SZ + 1];
        int n; //кол-во разрядов

    public:
        bigDecNum();
        bigDecNum(long int x);
        bigDecNum(const char* str);
        bigDecNum& Set(const char* str);
        friend bigDecNum operator +(const bigDecNum& first, const bigDecNum& second);
        friend bigDecNum operator -(const bigDecNum& first, const bigDecNum& second) { return first + (-second); };
        bigDecNum operator -() const;
        bigDecNum operator~() const;
        bigDecNum& operator <<=(int);
        bigDecNum& operator >>=(int);
        friend bool operator >(const bigDecNum&, const bigDecNum&); //перегрузка друзьями
        friend bool operator <(const bigDecNum&, const bigDecNum&);
        friend bool operator ==(const bigDecNum&, const bigDecNum&);
        friend std::ostream& operator <<(std::ostream&, const bigDecNum&);
        friend std::istream& operator >>(std::istream&, bigDecNum&);
        bool CompareAbs(const bigDecNum&) const;
        operator int() const;
        int digit_plus(const char *); //реализовать как внешнюю функции
    };

}


#endif //LAB3B_BIGNUM_H

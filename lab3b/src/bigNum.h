
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
        friend bigDecNum operator +(bigDecNum, bigDecNum);
        friend bigDecNum operator -(const bigDecNum& first, const bigDecNum& second) { return first + (-second); };
        bigDecNum operator -() const;
        bigDecNum operator~() const;
        bigDecNum& operator <<=(int);
        bigDecNum operator >>=(int);
        bool operator >(const bigDecNum&);
        bool operator <(const bigDecNum&);
        bool operator ==(const bigDecNum&);
        friend std::ostream& operator <<(std::ostream&, const bigDecNum&);
        friend std::istream& operator >>(std::istream&, bigDecNum&);
        bool CompareAbs(const bigDecNum&) const;
        operator int() const;
        static int digit_plus(const char *);
    };

    inline int getInt(int& n, const int max=std::numeric_limits<int>::max()) { //for natural int
        std::cin >> n;
        if (!std::cin.good())	// обнаружена ошибка ввода или конец файла
            return -1;
        if (n>=max) return -2;
        if (n<0) return 0;
        return 1;
    }

    int dialog(const char *[], int);

    int dialog_getAddCode(bigDecNum &);
    int dialog_inc10(bigDecNum &);
    int dialog_dec10(bigDecNum &);
    int dialog_print(bigDecNum &);

}


#endif //LAB3B_BIGNUM_H

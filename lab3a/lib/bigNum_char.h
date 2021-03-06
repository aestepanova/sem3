#ifndef LAB3A_BIGNUM_CHAR_H
#define LAB3A_BIGNUM_CHAR_H

#include <cmath>
#include <sstream>
#include <iostream>
#include <limits>

namespace Prog3a_char {

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
        bigDecNum Inc10() const;
        bigDecNum Dec10() const;
        bigDecNum AddCode() const;
        bool Large(const bigDecNum& t) const;
        bigDecNum Sum(const bigDecNum& t) const;
        bigDecNum Subtraction(bigDecNum) const;
        bigDecNum InputStr() const;
        void Print() const;
        int ToInt() const;
        int digit_plus(const char *);
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

#endif //LAB3A_BIGNUM_CHAR_H

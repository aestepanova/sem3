#include <iosfwd>
#ifndef __HEX_NUMBER_H__
#define __HEX_NUMBER_H__

namespace Prog3 {
    class HexNumber
    {
    private:
        static const int MAX_LEN = 32;
        char hex[MAX_LEN];
        int length;//длина введённого пользователем символьного массива
    public:
        HexNumber();
        HexNumber(const char* str);
        HexNumber(const long  a);
        HexNumber(const HexNumber& number);

        HexNumber& operator= (const HexNumber& num);

        char getSign()const { return hex[0] ;};

        std::ostream& output(std::ostream& o) const;
        std::istream& input(std::istream& i);

        HexNumber& setN( const char* str);
        HexNumber& Convert();
        HexNumber& Add(const HexNumber& num);
        HexNumber& Sub(const HexNumber& num);

        HexNumber& moveRight(int a);
        HexNumber& moveLeft(int a);

        char Compare(const HexNumber& num) const;//сравнение
        int Parity() const;//чётность
    };
    void out(const HexNumber& op1, const HexNumber& op2, const HexNumber& res, const char*);
    void dialog(HexNumber&, HexNumber&);
    int CharToHex(char num);
    char HexToChar(int num);

}//namespace Prog3
#endif /*!__HEX_NUMBER_H */

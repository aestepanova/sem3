#ifndef HEX_H
#define HEX_H
#include <iostream>

namespace H16_3 {
    class Hex {
    private:
        int length;
        char* number;
    public:
        Hex();
        Hex(const char*, int);
        Hex(const int);
        Hex(const Hex&);
        Hex(Hex &&);
        ~Hex();
        void Formate(int);
        char getSign() const{ return number[0]; }
        unsigned char Check() const;
        Hex& Convert();
        char Compare(const Hex&) const;
        Hex operator +(const Hex&) const;
        Hex operator -(const Hex&) const;
        Hex& operator <<=(int);
        Hex& operator >>=(int);
        Hex& operator =(const Hex&);
        Hex& operator =(Hex&&);
        friend std::istream& operator >>(std::istream&, Hex&);
        friend std::ostream& operator <<(std::ostream&, const Hex&);
    };
    char upper(const char);
    char HexToChar(int);
    int CharToHex(char);
}
#endif
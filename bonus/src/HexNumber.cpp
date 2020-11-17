#include "HexNumber.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <stdexcept>
#include <algorithm>

namespace Prog3 {
    HexNumber::HexNumber(): hex {},length(1)//пустой конструктор
    {
        std::fill(hex, hex + HexNumber::MAX_LEN ,'0');
    }
    HexNumber::HexNumber(const char* str)//инициализирующий строкой конструктор
    {
        try {
            setN(str);
        }
        catch (std::runtime_error& ) {
            throw std::invalid_argument("Wrong data");
        }
    }

    HexNumber::HexNumber(const long  a)
    {
        int a2 = a;
        if (a < 0) {
            hex[0] = 'F';
            a2 = -a;
        }
        else
            hex[0] = '0';
        int i = HexNumber::MAX_LEN - 1;
        for (; a2; i--) {
            hex[i] = HexToChar(a2 & 0xf);
            a2 >>= 4;
        }
        for (int j = 1; j <= i; j++)
            hex[j] = '0';
        length = HexNumber::MAX_LEN - i - 1;
        if (!length)
            length = 1;
    }

    HexNumber::HexNumber(const HexNumber& number):hex{}, length(number.length)
    {
        std::copy(number.hex, number.hex + HexNumber::MAX_LEN, hex);
    }

    HexNumber& HexNumber::operator=(const HexNumber& num)
    {
        if(this!= &num){
            length = num.length;
            std::copy(num.hex, num.hex + HexNumber::MAX_LEN, hex);
        }
        return *this;
    }

    HexNumber& HexNumber::setN(const char* str) {
        int leng = strlen(str), i = 0;
        if (!leng)
            throw std::runtime_error("Wrong data");
        switch (str[0]) {//Проверка знака
            case '+':
                i++;
                break;
            case '-':
                hex[0] = 'F';
                i++;
                break;
            default:
                hex[0] = '0';
        }
        if (str[i] == '0' && str[i + 1] == 'x')//проверка ввода числа, начинающегося с 0x
            i += 2;
        while (str[i] == '0')//проверка ввода числа, начинающегося с 0
            i += 1;
        int ll = HexNumber::MAX_LEN - leng + i;//место, с которого начинаем вводить число в массив
        if (ll < 1)
            ll = 1;
        for (int j = 1; j < ll; j++)// заполняем массив нулями до значащих цифр
            hex[j] = '0';
        length = ((leng - i) > 31) ? 31 : leng - i;
        for (int j = i; j < leng && ll < HexNumber::MAX_LEN; j++, ll++) {
            if ((str[j] < '0' || ('9' < str[j] && toupper(str[j]) < 'A') || 'F' < toupper(str[j])))//проверка попадания символа в диапазон шестнадцатиричных цифр
                throw std::runtime_error("Invalid symbol");
            hex[ll] = toupper(str[j]);
        }
        if (leng - i > 31)
            std::cout << "Only first 31 digits will be read" << std::endl;
        if ((hex[0] == 'F' && length == 1 && hex[HexNumber::MAX_LEN - 1] == '0') || !length) {
            HexNumber c;
            *this = c;
        }
        return *this;
    }

    HexNumber& HexNumber::Add(const HexNumber& num) {
        HexNumber add = num, result, first = *this;
        if (add.length == 1 && add.hex[1] == '0')//второй оператор просто 0
            return first;
        if (first.hex[0] == 'F')
            first.Convert();
        if (add.hex[0] == 'F')
            add.Convert();
        int t = 0;//перенос из младшего разряда
        for (int i = HexNumber::MAX_LEN - 1; i > -1; i--) {
            int sum = CharToHex(first.hex[i]) + CharToHex(add.hex[i]);
            result.hex[i] = HexToChar((sum) % 0x10);
            t = 0;
            if (sum >>= 4)
                t = 1;
        }
        if (first.hex[0] == add.hex[0] && add.hex[0] != result.hex[0])//знаки слагаемых равны,но отличны от знака суммы-переполнение!
            throw std::runtime_error("Overflow");
        if (result.hex[0] == 'F') {
            try {
                result.Convert();
            }
            catch (std::runtime_error& a) {
                throw std::runtime_error("Overflow");
            }
        }
        int k = 1;
        while (result.hex[k] == '0')
            k++;
        result.length = HexNumber::MAX_LEN - k;
        if (!result.length)//значит, результат 0
            result.length = 1;
        return result;
    }

    HexNumber& HexNumber::Sub(const HexNumber& num)
    {
        HexNumber sub = num, result;
        if (sub.hex[0] == '0')//положительное число
            sub.hex[0] = 'F';
        else
            sub.hex[0] = '0';
        try {
            result = Add(sub);
        }
        catch (std::runtime_error& a) {
            throw std::runtime_error("Overflow");
        }
        return result;
    }

    HexNumber& HexNumber::moveRight(int a)
    {
        if (a < 0)
            throw std::runtime_error("Invalid input");
        if (a == 0)
            return *this;
        if (a >= length) { //перемещаем всё число за разрядную сетку
            HexNumber object;//пустой конструктор on
            *this = object;
            return *this;
        }
        int stop = HexNumber::MAX_LEN - length;
        for (int i = HexNumber::MAX_LEN - 1; i >= stop; i--) {
            if ((i + a) < HexNumber::MAX_LEN)
                hex[i + a] = hex[i];
            hex[i] = '0';
        }
        length -= a;
        return *this;
    }
    HexNumber& HexNumber::moveLeft(int a) {
        if (a < 0)
            throw std::runtime_error("Invalid input");
        if (a == 0)
            return *this;
        if (a > (HexNumber::MAX_LEN - length)) {//выходим за пределы 32 знаков
            HexNumber object;//пустой конструктор on
            *this = object;
            return *this;
        }
        for (int i = HexNumber::MAX_LEN - length; i < HexNumber::MAX_LEN; i++) {
            if ((i - a) > 0)
                hex[i - a] = hex[i];
        }
        for (int i = 0; i < a; i++) {//дополняем нулями справа
            hex[HexNumber::MAX_LEN - i - 1] = '0';
        }
        length += a;
        if (length > 31)
            length = 31;
        return *this;
    }

    std::ostream& HexNumber::output(std::ostream& o) const
    {
        if (hex[0] == 'F')
            o << "-";
        //пошли ненулевые элементы
        for (int j = HexNumber::MAX_LEN - length;j < HexNumber::MAX_LEN; j++) {
            o << hex[j];
        }
        return o;
    }

    std::istream& HexNumber::input(std::istream& i)
    {
        char* s = (char*)malloc(1), buf[35];
        int n = 0, l = 0;
        s[0] = '\0';
        do {
            n = scanf("%34[^\n]", buf, 35);
            if (n < 0)
            {
                free(s);
            }
            if (n > 0) {
                l += strlen(buf);
                s = (char*)realloc(s, l + 1);
                strcat_s(s, l + 1, buf);
            }
            if (n == 0)
                scanf("%*c");
        } while (n > 0);
        try {
            setN(s);
        }
        catch (std::runtime_error& a) {
            i.setstate(std::ios::failbit);
        }
        free(s);
        return i;
    }

    HexNumber& HexNumber::Convert()//перевод в допкод с добавлением единицы для отрицательных чисел
    {
        for (int i = 1; i < HexNumber::MAX_LEN; i++) {
            int n = 0xF - CharToHex(hex[i]);
            hex[i] = HexToChar(n);
        }
        int l = HexNumber::MAX_LEN - 1;
        while (l > 0 && hex[l] == 'F')//поиск места для добавления единицы
            l--;
        if (l == 0)
            throw std::runtime_error("Overflow");
        int k = CharToHex(hex[l] + 1);
        hex[l] = HexToChar(k);
        for (int i = l + 1; i < HexNumber::MAX_LEN; i++)
            hex[i] = '0';
        return *this;
    }

    char HexNumber::Compare(const HexNumber& num) const
    {
        if (hex[0] < num.hex[0])//проверяем знаки
            return '>';
        if (hex[0] > num.hex[0])
            return '<';
        int l = length;
        if (num.length > length)
            l = num.length;
        char sgn = getSign();
        //HexNumber::MAX_LEN-l-позиция, начиная с которой сравниваем цифры
        for (int i = HexNumber::MAX_LEN - l; i < HexNumber::MAX_LEN; i++) {
            if (hex[i] > num.hex[i]) {
                if (sgn == '0')
                    return '>';
                else
                    return '<';
            }
            if (hex[i] < num.hex[i]) {
                if (sgn == '0')
                    return '<';
                else
                    return '>';
            }
        }
        return '=';
    }

    int HexNumber::Parity() const {
        if (hex[31] >= '0' && hex[31] <= '9') {
            return ((int)hex[31] - 48) % 2;
        }
        switch (hex[31]) {
            case 'B':
            case 'D':
            case 'F':
                return 1;
            case 'A':
            case 'C':
            case 'E':
                return 0;
        }
        return -1;
    }

    int CharToHex(const char c)
    {
        if (std::isdigit(c)) // in <cctype>
            return c - '0';
        else if (c >= 'A' && c <= 'F')
            return c - 'A' + 10;

        return -1;
    }

    char HexToChar(const int num)
    {
        if (std::isdigit(num)) // in <cctype>
            return '0' + num;
        else if (num > 9 && num < 16)
            return 'A' + num - 10;

        return '/';
    }

}//namespace Prog3
#include "bigNum.h"
#include <iostream>

namespace Prog3c {
    bigNum::bigNum() {
        Num = new char[2];
        n = 1;
        Num[0] = '0';
        Num[1] = '0';
    }
    bigNum::bigNum(long x) {
        long a = abs(x);
        n = 0;
        while (a) {
            ++n;
            a /= 10;
        }
        Num = new char[n + 1];
        if (x < 0) Num[0] = '1';
        else Num[0] = '0';
        int i = 1;
        a = abs(x);
        while (a) {
            Num[i] = (a % 10) + '0';
            a /= 10;
            i++;
        }
    }
    bigNum::bigNum(const char* str) {
        Num = nullptr;
        n = 0;
        Set(str);
    }
    bigNum& bigNum::Set(const char* str) {
        std::string STR = str;
        int check = STR.std::string::find_first_not_of("-0123456789");
        if (check >= 0) {
            throw std::runtime_error("Incorrect data. Your can only have 0-9 chars");
        }
        int l = STR.std::string::length();
        n = l;
        if (str[0] == '-') {
            n--;
        }
        int z = 0, i = str[0] == '-' ? 1 : 0;
        if ((str[0] == '-' && str[1] == '0') || str[0] == '0') {
            while (str[i] == '0') {
                i++;
                z++;
            }
            if (i == l) {
                Num = new char[2];
                n = 1;
                Num[0] = '0';
                Num[1] = '0';
                return *this;
            }
        }
        n -= z;
        delete[] Num;
        Num = new char[n + 1];
        i = l - 1;
        for (int k = 1; k <= n; k++) {
            Num[k] = str[i];
            i--;
        }
        if (str[0] == '-') {
            Num[0] = '1';
        }
        else Num[0] = '0';
        return *this;
    }
    bigNum::bigNum(const bigNum& t) {

        n = t.n;
        Num = new char[n + 1];
        for (int i = 0; i < n + 1; i++)
            Num[i] = t.Num[i];

    }

    //изменение мантиссы числа (flag = 1 - при сдвиге, flag = 0 при суммировании)
    bigNum& bigNum::resize(int amount, bool flag) {
        char* tmp = new char[n + 1];
        for (int i = 0; i <= n; i++) tmp[i] = Num[i];
        delete[] Num;
        Num = new char[amount + 1];
        Num[0] = tmp[0];
        if (flag) {
            if (amount > n) {
                int pr = amount - n;
                for (int i = n; i >= 1; i--) Num[i + pr] = tmp[i];
                for (int i = 1; i <= pr; i++) Num[i] = '0';
            }
            if (amount < n) {
                int pr = n - amount;
                for (int i = n; i >= pr + 1; i--) Num[i - pr] = tmp[i];
            }
        } else {
            for (int i = n; i >= 1; i--) Num[i] = tmp[i];
            for (int i = amount; i > n; i--) Num[i] = '0';
        }
        n = amount;
        delete[] tmp;
        return *this;
    }

    bigNum operator +(const bigNum& first, const bigNum& second) {
        int transfer = 0;
        bool index = (first.Num[0] == second.Num[0]);
        int j = first.n >= second.n ? first.n : second.n; //определение порядка суммы
        bigNum s1 = first, s2 = second;
        if (j + 1 < first.SZ) {
            s1.resize(j + 1, false), s2.resize(j + 1, false);
            j++;
        }
        else {
            if (s1.n < first.SZ) s1.resize(j, false);
            else s2.resize(j, false);
        }
        s1 = ~s1, s2 = ~s2; //получение обратного кода числа
        for (int i = 0; i <= j; i++) {
            if (s1.Num[i] - '0' + s2.Num[i] - '0' + transfer < 10) {
                s1.Num[i] = s1.Num[i] - '0' + s2.Num[i] - '0' + transfer + '0';
                transfer = 0;
            }
            else {
                s1.Num[i] = s1.Num[i] - '0' + s2.Num[i] - '0' + transfer - 10 + '0';
                transfer = 1;
            }
        }
        if (!index) {
            if (first.compareAbs(second)) s1.Num[0] = first.Num[0];
            else if (second.compareAbs(first)) s1.Num[0] = second.Num[0];
            else { //если модули чисел равны, то возвращаем ноль нашего класса
                s1.Num[0] = '0';
                s1.n = 1;
                return s1;
            }
        }
        else s1.Num[0] = first.Num[0];

        s1 = ~s1;

        for (int i = j; i > 0; i--) {
            if (s1.Num[i] != '0') {
                char* tmp = new char[i + 1];
                for (int k = 0; k <= i; k++) tmp[k] = s1.Num[k];
                delete[] s1.Num;
                s1.Num = new char[i + 1];
                for (int k = 0; k <= i; k++) s1.Num[k] = tmp[k];
                s1.n = i;
                delete[]tmp;
                break;
            }
        }
        return s1;
    }
    bigNum& bigNum::operator = (const bigNum& t) {
        if (this->Num != t.Num) {
            if (Num != nullptr)
                delete[]Num;
            if (t.n != 0) {
                n = t.n;
                Num = new char[t.n + 1];
                for (int i = 0; i <= n; i++)
                    Num[i] = t.Num[i];
            }
        }
        return *this;
    }
    bigNum& bigNum::operator = (bigNum&& t) noexcept {
        if (Num != nullptr) {
            delete[]Num;
            Num = t.Num;
            n = t.n;
            t.Num = nullptr;
        }
        return*this;
    }

    // сдвиг вправо на pr разрядов с присваиванием (уменьшение числа)
    bigNum& bigNum::operator >>=(int pr) {
        if ((n - pr) <= 0) {
            delete[]Num;
            Num = new char[2];
            Num[0] = '0';
            Num[1] = '0';
            n = 1;
            return *this;
        }
        this->resize(n - pr, true);
        return *this;
    }

    // сдвиг влево на pr разрядов с присваиванием (увеличение числа)
    bigNum& bigNum::operator <<=(int pr) {
        if (n == 1 && Num[1] == '0') {
            return *this;
        }
        this->resize(n + pr, true);
        return *this;
    }

    //обратный код числа
    bigNum bigNum::operator~() const {
        bigNum a;
        if (Num[0] == '0') //если положительное число, то оставляем как есть
            return *this;
        int f = 1; // флаг для первого вычитания из 10
        a.Num = new char[n + 1];
        for (int i = 1; i <= n; i++) {
            if (f && Num[i] != '0') {
                a.Num[i] = 10 - (Num[i] - '0') + '0';
                f = 0;
            }
            else if (!f)
                a.Num[i] = 9 - (Num[i] - '0') + '0';
        }
        a.n = n;
        a.Num[0] = Num[0];
        return a;
    }
    //больше ли модуль первого числа?
    bool bigNum::compareAbs(const bigNum&second) const {
        if (n > second.n) return true;
        if (second.n > n) return false;
        if (second.n == n) {
            for (int i = n; i >= 1; i--) {
                if (Num[i] > second.Num[i]) return true;
                if (second.Num[i] > Num[i]) return false;
            }
        }
        return false;
    }
    bool operator >(const bigNum& first, const bigNum& second) {
        if (first.Num[0] == '1' && second.Num[0] == '0') return false;
        if (first.Num[0] == '0' && second.Num[0] == '1') return true;
        if (first.n > second.n) return true;
        if (first.n < second.n) return false;
        if (second.n == first.n && first.Num[0] == '0') {
            for (int i = first.n; i >= 1; i--) {
                if (first.Num[i] > second.Num[i]) return true;
                if (second.Num[i] > first.Num[i]) return false;
            }
        }
        if (first.n == second.n && first.Num[0] == '1') {
            for (int i = first.n; i >= 1; i--) {
                if (first.Num[i] > second.Num[i]) return false;
                if (second.Num[i] > first.Num[i]) return true;
            }
        }
        return false;
    }
    bool operator <(const bigNum& first, const bigNum& second) {
        if (first.Num[0] == '1' && second.Num[0] == '0') return true;
        if (first.Num[0] == '0' && second.Num[0] == '1') return false;
        if (first.n < second.n) return true;
        if (first.n > second.n) return false;
        if (first.n == second.n && first.Num[0] == '0') {
            for (int i = first.n; i >= 1; i--) {
                if (first.Num[i] < second.Num[i]) return true;
                if (second.Num[i] < first.Num[i]) return false;
            }
        }
        if (first.n == second.n && first.Num[0] == '1') {
            for (int i = first.n; i >= 1; i--) {
                if (first.Num[i] < second.Num[i]) return false;
                if (second.Num[i] < first.Num[i]) return true;
            }
        }
        return false;
    }
    bool operator ==(const bigNum& first, const bigNum& second) {
        if (first.n != second.n) return false;
        if (first.n == second.n && first.Num[0] == second.Num[0]) {
            for (int i = second.n; i >= 0; i--) {
                if (first.Num[i] != second.Num[i]) return false;
            }
            return true;
        }
        return false;
    }
    const bigNum bigNum::operator -() const {
        bigNum neg = *this;
        if ((n == 1 && Num[1] != '0') || (n != 1)) {
            neg.Num[0] = Num[0] == '0' ? '1' : '0';
        }
        neg.n = n;
        return neg;
    }

    std::istream& operator >>(std::istream& s, bigNum& t) {
        char ptr[100] = "";
        s >> ptr;
        std::cin.clear();
        t.Set(ptr);
        return s;
    }
    std::ostream& operator <<(std::ostream& s, const bigNum& t) {
        if (t.Num[0] == '1')
            s << "-";
        if (t.n == 1 && t.Num[1] == '0') s << '0';
        else {
            for (int i = t.n; i >= 1; i--) {
                s << t.Num[i];
            }
        }
        return s;
    }

    bigNum::operator int() const {
        int i = 0;
        int pow = 1;
        if (n > 50)
            throw - 1;
        for (int k = 1; k <= n; k++) {
            i += (Num[k] - '0') * pow;
            pow *= 10;
        }
        i = Num[0] == '0' ? i : -i;
        return i;
    }
}
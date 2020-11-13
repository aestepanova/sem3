#include "bigNum.h"
#include "bigNum.h"
#include <cstdio>
#include <cstring>

namespace Prog3b {

    bigNum::bigNum() {
        //знак +, первая цифра - ноль
        Num = new char[2];
        n = 1; //количество разрядов
        Num[0] = '0';
        Num[1] = '0';
    }

    //формирование из типа long int
    bigNum::bigNum(long int x) {
        long int a = abs(x);
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

    //конструирование большого числа из строки
    bigNum::bigNum(const char *str) {
        this->Num = nullptr;
        this->n = 0;
        Set(str);
    }

    bigNum &bigNum::Set(const char *str) {

        if (str == nullptr)
            throw "Nullptr";
        //определяем длину строки
        int l = strlen(str);
        if (l > SZ + 1) throw std::invalid_argument("Too many chars!");
        n = l;
        if (str[0] == '-') {
            Num[0] = 1;
            n--;
        }
        //проверка, есть ли в строке нецифровые символы
        int pr1 = digit_plus(str);
        if (pr1 == 0) {
            Num[0] = 0;
            throw std::invalid_argument("Incorrect data. Your can only have 0-9 chars");
        }

        int z = 0;
        //установка знака
        int i = str[0] == '-' ? 1 : 0;
        if ((str[0] == '-' && str[1] == '0') || str[0] == '0') {
            while (str[i] == '0') { //считаем лидирующие нули
                i++;
                z++;
            }
            if (i == l) { //если вся строка состоит из нулей, то создаем ноль нашего класса
                Num = new char[2];
                Num[0] = '0';
                n = 1;
                Num[1] = '0';
                return *this;
            }
        }
        n -= z; //количество разрядов не учитывает лидирующие нули
        delete [] Num;
        this->Num = new char[2];
        i = l - 1; //идем со старших разрядов
        for (int k = 1; k <= n; k++) {
            Num[k] = str[i] - '0';
            i--;
        }
        if (str[0] == '-') {
            Num[0] = '1';
        }
        else Num[0] = '0';
        return *this;
    }

    //сравнение абсолютных значений чисел
    bool bigNum::CompareAbs(const bigNum &t) const {
        if (n > t.n) return true;
        if (t.n > n) return false;
        if (t.n == n) {
            for (int i = n; i >= 1; i--) {
                if (Num[i] > t.Num[i]) return true;
                if (t.Num[i] > Num[i]) return false;
            }
        }
        return false;
    }

    // перегрузка оператора побитового not для нашего класса
    bigNum bigNum::operator~() const {
        bigNum a;
        if (Num[0] == 0)
            return *this;
        int pr = 1;
        a.Num = new char[n+1];
        for (int i = 1; i <= SZ; i++) {
            if (pr && Num[i] != 0) {
                a.Num[i] = 10 - Num[i] + '0';
                pr = 0;
            } else if (!pr)
                a.Num[i] = 9 - Num[i] + '0';
        }
        a.n = n;
        a.Num[0] = Num[0];
        return a;
    }

    // перегрузка оператора сложения
    bigNum operator+(const bigNum &fir, const bigNum &sec) {
        int dop = 0;
        bool index = (fir.Num[0] == sec.Num[0]);
        int j = fir.n >= sec.n ? fir.n : sec.n;
        BigNum s1 = fir, s2 = sec;
        if (!(j + 1 >= fir.SZ)) {
            s1.Resize(j + 1, false), s2.Resize(j + 1, false);
            j++;
        }
        else {
            if (s1.n < fir.SZ)s1.Resize(j, false);
            else s2.Resize(j, false);
        }
        s1 = ~s1, s2 = ~s2;
        for (int i = 0; i <= j; i++) {
            if (s1.Num[i] - '0' + s2.Num[i] - '0' + dop < 10) {
                s1.Num[i] = s1.Num[i] - '0' + s2.Num[i] - '0' + dop + '0';
                dop = 0;
            }
            else {
                s1.Num[i] = s1.Num[i] - '0' + s2.Num[i] - '0' + dop - 10 + '0';
                dop = 1;
            }
        }
        if (!index) {
            if (fir.CompareAbs(sec)) s1.Num[0] = fir.Num[0];
            else if (sec.CompareAbs(fir)) s1.Num[0] = sec.Num[0];
            else {
                s1.Num[0] = '0';
                s1.n = 1;
                return s1;
            }
        }
        else s1.Num[0] = fir.Num[0];
        s1 = ~s1;
        if (!(j < fir.SZ)) j -= 1;
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

    // перегрузка оператора сравнения больше
    bool operator>(const bigNum &first, const bigNum &second) {

        if (first.Num[0] == '1' && second.Num[0] == 0) return false;
        if (first.Num[0] == '0' && second.Num[0] == 1) return true;
        if (first.n > second.n) return true;
        if (first.n < second.n) return false;
        if (second.n == first.n && first.Num[0] == 0) {
            for (int i = first.n; i >= 1; i--) {
                if (first.Num[i] > second.Num[i]) return true;
                if (second.Num[i] > first.Num[i]) return false;
            }
        }
        if (second.n == first.n && first.Num[0] == 1) {
            for (int i = first.n; i >= 1; i--) {
                if (first.Num[i] > second.Num[i]) return false;
                if (second.Num[i] > first.Num[i]) return true;
            }
        }
        return false;
    }

    // перегрузка опреатора сравнения меньше
    bool operator<(const bigNum &first, const bigNum &second) {
        if (first.Num[0] == 1 && second.Num[0] == 0) return true;
        if (first.Num[0] == 0 && second.Num[0] == 1) return false;
        if (first.n < second.n) return true;
        if (first.n > second.n) return false;
        if (second.n == first.n && first.Num[0] == 0) {
            for (int i = first.n; i >= 1; i--) {
                if (first.Num[i] < second.Num[i]) return true;
                if (second.Num[i] < first.Num[i]) return false;
            }
        }
        if (second.n == first.n && first.Num[0] == 1) {
            for (int i = first.n; i >= 1; i--) {
                if (first.Num[i] < second.Num[i]) return false;
                if (second.Num[i] < first.Num[i]) return true;
            }
        }
        return false;
    }

    // перегрузка оператора сравнивания
    bool operator==(const bigNum &first, const bigNum &second) {
        if (first.n != second.n) return false;
        if (first.n == second.n && first.Num[0] == second.Num[0]) {
            for (int i = second.n; i >= 0; i--) {
                if (first.Num[i] != second.Num[i]) return false;
            }
            return true;
        }
        return false;
    }

    // сдвиг влево на pr разрядов с присваиванием (увеличение числа)
    bigNum &bigNum::operator>>=(int pr) {
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

    // сдвиг вправо на pr разрядов с присваиванием (уменьшение числа)
    bigNum &bigNum::operator<<=(int pr) {
        if (n == 1 && Num[1] == '0') {
            return *this;
        }
        this->resize(n + pr, true);
        return *this;
    }

    // перегрузка оператора ввода
    std::istream &operator>>(std::istream &s, bigNum &t) {
        char ptr[100] = "";
        s >> ptr;
        std::cin.clear();
        t.Set(ptr);
        return s;
    }

    // перегрузка оператора вывода
    std::ostream &operator<<(std::ostream &s, const bigNum &t) {
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

    int digit_plus(const char *str) {
        int l = strlen(str);
        //если первый символ минус, то проверяем символы, начиная со второго, в ином случае с первого
        if (str[0] == '-') {
            for (int i = 1; i < l; i++) {
                if (!(isdigit(str[i]))) {
                    return 0;
                }
            }
        } else {
            for (int i = 0; i < l; i++) {
                if (!(isdigit(str[i]))) {
                    return 0;
                }
            }
        }

        return 1;
    }

    bigNum bigNum::operator-() const {
        bigNum neg = *this;
        if ((n == 1 && Num[1] != 0) || (n != 1)) {
            neg.Num[0] = Num[0] == 0 ? 1 : 0;
        }
        neg.n = n;
        return neg;
    }

    bigNum::bigNum(const bigNum &t) {
        try {
            n = t.n;
            Num = new char[n + 1];
            for (int i = 0; i < n + 1; i++)
                Num[i] = t.Num[i];
        }
        catch (...) {
            std::cout << "Empty initialization";
            n = 1;
            Num = new char[2];
            Num[0] = Num[1] = '0';
        }
    }

    bigNum &bigNum::operator=(const bigNum &t) {
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
        return*this;

    }

    bigNum &bigNum::operator=(bigNum &&t) noexcept {
        if (Num != nullptr) {
            delete[]Num;
            Num = t.Num;
            n = t.n;
            t.Num = nullptr;
        }
        return*this;
    }

    bigNum &bigNum::resize(int amount, bool flag) {
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
        }
        if (!flag) {
            for (int i = n; i >= 1; i--) Num[i] = tmp[i];
            for (int i = amount; i > n; i--) Num[i] = '0';
        }
        n = amount;
        delete[] tmp;
        return *this;
    }
}
#include "bigNum.h"
#include <cstdio>
#include <cstring>



namespace Prog3b {

    bigDecNum::bigDecNum() {
        //знак +, все цифры - нули
        for (char &i : Num) i = 0;
        n = 1; //количество разрядов
    }

    //формирование из типа long int
    bigDecNum::bigDecNum(long int x) {
        //устанавливаем знак
        if (x < 0)
            Num[0] = 1;
        else
            Num[0] = 0;
        long int a = abs(x);
        int i = 1;
        n = 0;
        while (a) {
            ++n; //считаем количество разрядов
            Num[i] = (a % 10);
            a /= 10;
            i++;
            if (n > SZ)
                throw std::invalid_argument("Overflow");
        }
        for (int j = SZ; j >= SZ - n + 1; j--) Num[j] = 0; //заполнение лидирующими нулями
    }

    //конструирование большого числа из строки
    bigDecNum::bigDecNum(const char *str) {
        Set(str);
    }

    bigDecNum &bigDecNum::Set(const char *str) {

        if (str == nullptr)
            throw "Nullptr";
        //определяем длину строки
        int l = strlen(str);
        if (l > SZ + 1) throw std::invalid_argument("Too many chars!");
        n = l;
        if (str[0] == '-') {
            Num[0] = 1;
            n--;
        } else Num[0] = 0;

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
                Num[0] = 0;
                n = 1;
                for (int i = 1; i < SZ + 1; ++i) Num[i] = 0;
                return *this;
            }
        }
        n -= z; //количество разрядов не учитывает лидирующие нули

        i = l - 1; //идем со старших разрядов
        for (int k = 1; k <= n; k++) {
            Num[k] = str[i] - '0';
            i--;
        }

        //заполнение лидирующими нулями
        for (int k = SZ; k >= n + 1; k--)
            Num[k] = 0;

        return *this;
    }

    //сравнение абсолютных значений чисел
    bool bigDecNum::CompareAbs(const bigDecNum &t) const {
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
    bigDecNum bigDecNum::operator~() const {
        bigDecNum a;
        if (Num[0] == 0)
            return *this;
        int pr = 1;
        for (int i = 1; i <= SZ; i++) {
            if (pr && Num[i] != 0) {
                a.Num[i] = 10 - Num[i];
                pr = 0;
            } else if (!pr)
                a.Num[i] = 9 - Num[i];
        }
        a.n = n;
        if (Num[1] == 0) a.Num[1] = 0;
        a.Num[0] = Num[0];
        return a;
    }

    // перегрузка оператора сложения
    bigDecNum operator+(const bigDecNum fir, const bigDecNum sec) {
        int dop = 0;
        bool index = (fir.Num[0] == sec.Num[0]);
        int j = fir.n >= sec.n ? fir.n : sec.n;
        bigDecNum s1 = ~fir, s2 = ~sec;
        for (int i = 0; i < fir.SZ; i++) {
            if (s1.Num[i] + s2.Num[i] + dop < 10) {
                s1.Num[i] = s1.Num[i] + s2.Num[i] + dop;
                dop = 0;
            } else {
                s1.Num[i] = s1.Num[i] + s2.Num[i] + dop - 10;
                dop = 1;
            }
        }
        if ((dop > 0) && index && ((fir.Num[fir.SZ] != 0) || (sec.Num[sec.SZ] != 0)))
            throw std::runtime_error("Overflow!");
        if (!index) {
            if (fir.CompareAbs(sec)) s1.Num[0] = fir.Num[0];
            else if (sec.CompareAbs(fir)) s1.Num[0] = sec.Num[0];
            else {
                s1.Num[0] = 0;
                s1.n = 1;
                return s1;
            }
        } else s1.Num[0] = fir.Num[0];
        s1 = ~s1;
        if (j < fir.SZ) j += 1;
        for (int i = j; i > 0; i--) {
            if (s1.Num[i] != 0) {
                s1.n = i;
                break;
            }
        }
        return s1;
    }

    // перегрузка оператора сравнения больше
    bool bigDecNum::operator>(const bigDecNum &second) {
        if (Num[0] == '1' && second.Num[0] == 0) return false;
        if (Num[0] == '0' && second.Num[0] == 1) return true;
        if (n > second.n) return true;
        if (n < second.n) return false;
        if (second.n == n && Num[0] == 0) {
            for (int i = n; i >= 1; i--) {
                if (Num[i] > second.Num[i]) return true;
                if (second.Num[i] > Num[i]) return false;
            }
        }
        if (second.n == n && Num[0] == 1) {
            for (int i = n; i >= 1; i--) {
                if (Num[i] > second.Num[i]) return false;
                if (second.Num[i] > Num[i]) return true;
            }
        }
        return false;
    }

    // перегрузка опреатора сравнения меньше
    bool bigDecNum::operator<(const bigDecNum &second) {
        if (Num[0] == 1 && second.Num[0] == 0) return true;
        if (Num[0] == 0 && second.Num[0] == 1) return false;
        if (n < second.n) return true;
        if (n > second.n) return false;
        if (second.n == n && Num[0] == 0) {
            for (int i = n; i >= 1; i--) {
                if (Num[i] < second.Num[i]) return true;
                if (second.Num[i] < Num[i]) return false;
            }
        }
        if (second.n == n && Num[0] == 1) {
            for (int i = n; i >= 1; i--) {
                if (Num[i] < second.Num[i]) return false;
                if (second.Num[i] < Num[i]) return true;
            }
        }
        return false;
    }

    // перегрузка оператора сравнивания
    bool bigDecNum::operator==(const bigDecNum &first) {
        if (n != first.n) return false;
        if (first.n == n && Num[0] == first.Num[0]) {
            for (int i = n; i >= 0; i--) {
                if (Num[i] != first.Num[i]) return false;
            }
            return true;
        }
        return false;
    }

    // сдвиг влево на pr разрядов с присваиванием (увеличение числа)
    bigDecNum bigDecNum::operator>>=(int pr) {
        if (n == 1 && Num[1] == 0) {
            n = 1;
            return *this;
        }
        Num[0] = Num[0];
        if (Num[SZ - pr] != 0)
            throw std::runtime_error("Overflow");
        for (int i = n; i >= 1; i--) Num[i + pr] = Num[i];
        for (int i = 1; i <= pr; i++) Num[i] = 0;
        n = n + pr;
        return *this;
    }

    // сдвиг вправо на pr разрядов с присваиванием (уменьшение числа)
    bigDecNum &bigDecNum::operator<<=(int pr) {
        if (n - pr <= 0) {
            for (int i = 0; i <= n; i++) {
                Num[i] = 0;
            }
            n = 1;
            return *this;
        }
        for (int i = 1; i <= n; i++) Num[i] = Num[i + pr];
        n = n - pr;
        return *this;
    }

    // перегрузка оператора ввода
    std::istream &operator>>(std::istream &s, bigDecNum &t) {
        try {
            char *ptr = (char *) malloc(1);
            *ptr = '\0';
            char buf[81];
            int n;
            int len = 0;
            do {
                n = scanf("%80[^\n]", buf, 81);
                if (n < 0) {
                    free(ptr);
                    ptr = nullptr;
                    continue;
                }
                if (n == 0)
                    scanf("%*c");
                else {
                    len += strlen(buf);
                    ptr = (char *) realloc(ptr, len + 1);
                    strcat_s(ptr, len + 1, buf);
                }
            } while (n > 0);
            if (strlen(ptr) > t.SZ + 1) {
                std::cout << "Overflow. You enter too big number" << std::endl;
                return s;
            }
            std::cin.clear();
            t.Set(ptr);
        }

        catch (const std::exception &msg) {
            std::cout << msg.what() << std::endl;
        }
        return s;
    }

    // перегрузка оператора вывода
    std::ostream &operator<<(std::ostream &s, const bigDecNum &t) {
        if (t.Num[0] == 1)
            s << "-";
        if (t.n == 1) {
            if (t.Num[1] == 0){
                s<<0;
                return s;
            }
        }
        for (int i = t.n; i >= 1; i--) {
            int print = t.Num[i];
            s << print;
            }
        return s;
    }

    bigDecNum::operator int() const {
        int i = 0;
        int pow = 1;
        if (n > 50)
            throw -1;
        for (int k = 1; k <= n; k++) {
            i += Num[k] * pow;
            pow *= 10;
        }
        i = Num[0] == 0 ? i : -i;
        return i;
    }

    int bigDecNum::digit_plus(const char *str) {
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

    bigDecNum bigDecNum::operator-() const {
        bigDecNum neg = *this;
        if ((n == 1 && Num[1] != 0) || (n != 1)) {
            neg.Num[0] = Num[0] == 0 ? 1 : 0;
        }
        neg.n = n;
        return neg;
    }
}
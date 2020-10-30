#include "bigNumber.h"
#include <cstdio>
#include <iostream>


namespace Prog3a {

    bigDecNum::bigDecNum()
    {
        //знак +, все цифры - нули
        for (int i = 0; i < SZ + 1; ++i) Num[i] = 0;
        n = 1; //количество разрядов
    }

    //формирование из типа long int
    bigDecNum::bigDecNum(long int x){
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
    bigDecNum::bigDecNum(const char* str) {
            Set(str);
    }

    bigDecNum& bigDecNum::Set(const char* str){
        std::string STR = str;
        //определяем длину строки
        int l = STR.std::string::length();
        if (l>SZ+1) throw std::invalid_argument("Too many chars!");
        n = l;
        if (str[0] == '-'){
            Num[0] = 1;
            n--;
        }
        else Num[0] = 0;

        //проверка, есть ли в строке нецифровые символы
        int pr1 = STR.std::string::find_first_not_of("-0123456789");
        if (pr1 >= 0) {
            Num[0] = 0;
            throw std::runtime_error("Incorrect data. Your can only have 0-9 chars");
//            throw std::invalid_argument("Incorrect data. Your can only have 0-9 chars");
        }

        int z = 0;
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
            Num[k] = str[i]-'0';
            i--;
        }

        //заполнение лидирующими нулями
        for (int k = SZ; k >= n + 1; k--)
            Num[k] = 0;

        return *this;
    }


    bigDecNum bigDecNum::AddCode() const{
        bigDecNum a;
        if (Num[0] == 0)
            return *this;
        int pr = 1;
        for (int i = 1; i <= SZ; i++) {
            if (pr && Num[i] != 0) {
                a.Num[i] = 10 - Num[i];
                pr = 0;
            }
            else if (!pr)
                a.Num[i] = 9 - Num[i];
        }
        a.n = n;
        if (Num[1] == 0) a.Num[1] = 0;
        a.Num[0] = Num[0];
        return a;
    }
    bool bigDecNum::Large(const bigDecNum& t) const {
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

    bigDecNum bigDecNum::Sum(const bigDecNum& t) const {
        int dop = 0;
        bool index = (Num[0] == t.Num[0]);
        int j = n >= t.n ? n : t.n;
        bigDecNum s1 = (this)->AddCode(), s2(t.AddCode());
        try{
            for (int i = 0; i <= SZ; i++) {
                if (s1.Num[i] + s2.Num[i] + dop < 10) {
                    s1.Num[i] = s1.Num[i] + s2.Num[i] + dop;
                    dop = 0;
                } else {
                    s1.Num[i] = s1.Num[i] + s2.Num[i] + dop - 10;
                    dop = 1;
                }
            }
            if ((dop > 0) && index && ((Num[SZ] != 0) || (t.Num[SZ] != 0)))
                throw std::invalid_argument("Overflow!");
            if (!index) {
                if ((this)->Large(t)) {
                    s1.Num[0] = Num[0];
                } else if (t.Large(*this)) {
                    s1.Num[0] = t.Num[0];
                } else {
                    s1.Num[0] = 0;
                    s1.n = 1;
                    return s1;
                }
            } else
                s1.Num[0] = Num[0];
            s1 = s1.AddCode();
            if (j < SZ) j += 1;
            for (int i = j; i > 0; i--) {
                if (s1.Num[i] != 0) {
                    s1.n = i;
                    break;
                }
            }
            return s1;
        }
        catch (const std::exception &msg) {
            std::cout << msg.what() << std::endl;
            return s1;
        }
   }

    bigDecNum bigDecNum::Subtraction(bigDecNum t) const{
        bigDecNum s2 = t, s1 = *this;
        if (s2.Num[0] == 0) s2.Num[0] = 1;
        else s2.Num[0] = 0;
        s1 = s1.Sum(s2);
        return s1;
    }

    bigDecNum bigDecNum::Inc10() const
    {
        bigDecNum inc;
        inc.n = n + 1;
        if (n == 1 && Num[1] == 0) {
            inc.n = 1;
            return inc;
        }
        if (Num[SZ] != 0)
            throw std::invalid_argument("Overflow!");
        inc.Num[0] = Num[0];
        inc.Num[1] = 0;
        for (int i = n; i >= 1; i--)
            inc.Num[i + 1] = Num[i];
        return inc;
    }
    bigDecNum bigDecNum::Dec10() const
    {
        bigDecNum inc;
        inc.n = n - 1;
        if (n == 1) {
            inc.n = 1;
            return inc;
        }
        inc.Num[0] = Num[0];
        for (int i = n; i >= 2; i--)
            inc.Num[i - 1] = Num[i];
        return inc;
    }

    bigDecNum bigDecNum::InputStr() const{
        const char* ptr = "";
        std::string ss;
        std::cin >> ss;
        if (ss.std::string::length() > SZ + 1)
            throw std::runtime_error("Overflow!");
        ptr = ss.c_str();
        std::cin.clear();
        bigDecNum decNum(ptr);
        std::cout<<std::endl;
        return decNum;
    }

    void bigDecNum::Print() const{
        if (Num[0] == 1)
            std::cout << "-";
        bool k = false;
        if (n == 1) {
            if (Num[1] == 0) k = true;
        }
        if (n == 1 && Num[1] == 0) std::cout << 0;
        else {
            for (int i = n; i >= 1; i--) {
                int t = Num[i];
                std::cout << t;
            }
        }
        std::cout<<std::endl;
    }

    //для тестов
    int bigDecNum::ToInt() const{
        int i = 0;
        int pow = 1;
        if (n > 50)
            throw std::invalid_argument("Too many chars!");
        for (int k = 1; k <= n; k++) {
            i += Num[k] * pow;
            pow *= 10;
        }
        i = Num[0] == 0 ? i : -i;
        return i;
    }


/// dialog functions

    int dialog(const char *msgs[], int N) {
        std::string errmsg;
        int rc, n;
        do {
            std::cout << errmsg;
            errmsg = "You are wrong. Repeat, please\n";
            for (int j = 0; j < N; ++j)
                puts(msgs[j]);
            puts("Make your choice: --> ");

            n = getInt(rc);
            if (n == 0)
                rc = 0;
        } while (rc < 0 || rc >= N);
        return rc;
    }

    int dialog_getAddCode(bigDecNum &f) {

        try {
            std::cout<<"There is an add-code for your first num: ";
            f.AddCode().Print();
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }

        return 1;
    }

    int dialog_inc10(bigDecNum &f) {
        try {
            bigDecNum f1=f.Inc10();
            std::cout << "Received number: ";
            f1.Print();
            std::cout << std::endl;
        }
        catch (const std::exception& msg) {
            std::cout << msg.what() << std::endl;
        }
        return 1;
    }

    int dialog_dec10(bigDecNum &f) {
        try {
            bigDecNum f1=f.Dec10();
            std::cout << "Received number: ";
            f1.Print();
            std::cout << std::endl;
        }
        catch (const std::exception& msg) {
            std::cout << msg.what() << std::endl;
        }
        return 1;
    }
///

}

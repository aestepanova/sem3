#include "bigNumber.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

namespace Prog3a {

    bigDecNum::bigDecNum()
    {
        Num[0] = 0;
        //все цифры - нули
        for (int i = 1; i < SZ + 1; ++i)
            Num[i] = 0;
        n = 1;
    }
    bigDecNum::bigDecNum(long int x){
        try {
            long int a = abs(x);
            while (a){
                ++n;
                a /= 10;
            }
            if (x < 0) Num[0] = 1;
            else Num[0]=0;
            if (n > SZ)
                throw "Overflow";
            for (int i = 1; i <= n; i++) {
                Num[i] = (a % 10);
                a /= 10;
            }
            for (int i = SZ; i >= SZ - n + 1; i--)
                Num[i] = 0;
        }
        catch (const std::exception & msg) {
            std::cout << msg.what() << std::endl;
        }
    }
    bigDecNum::bigDecNum(const char* str) {
        try {
            Set(str);
        }
        catch (std::exception& a) {
            throw std::exception("Wrong data");
        }
    }
    bigDecNum& bigDecNum::Set(const char* str){
        try {
            std::string STR = str;
            if (str == nullptr)
                throw "Nullptr";
            int l = STR.std::string::length();
            n = l;
            int z=0;
            if (str[0] == '-') {
                Num[0] = 1;
                z++;
                n--;
            }
            else Num[0] = 0;
            int pr1 = STR.std::string::find_first_not_of("0123456789");
            if (pr1 > 0) {
                Num[0] = 0;
                throw "Incorrect data. Your number can begin only from - or 0-9 chars and contain 0-9 chars";
            }
            int i = 0;
            i = l - 1;
            bool tmp = true;
            for (int k = 1; k <= n; k++) {
                Num[k] = str[i]-'0';
                i--;
                if (tmp && Num[k] != 0)
                    tmp = false;
            }
            if (tmp)
                Num[0] = 0;
            for (int k = SZ; k >= n + 1; k--)
                Num[k] = 0;
        }
        catch (const std::exception& msg) {
            std::cout << msg.what() << std::endl;
        }
        return *this;
    }

    const bigDecNum bigDecNum::AddCode() const{
        bigDecNum a;
        if (Num[0] == 0)
            return *this;
        int pr = 1;
        for (int i = 1; i <= SZ; i++) {
            if (pr && Num[i] != 0) {
                a.Num[i] = 10 - Num[i];
                pr=0;
            }
            else if (!pr)
                a.Num[i] = 9 - Num[i];
        }
        if (Num[1] == 0) a.Num[1] = 0;
        a.Num[0] = 0;
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
    }
    bigDecNum bigDecNum::Sum(const bigDecNum& t)const
    {
        try {
            int dop = 0;
            bool index = (Num[0] == t.Num[0]);
            int j = n >= t.n ? n : t.n;
            bigDecNum s1 = (this)->AddCode(), s2(t.AddCode());
            for(int i = 0; i <= SZ; i++) {
                if (s1.Num[i] + s2.Num[i] + dop < 10) {
                    s1.Num[i] = s1.Num[i] + s2.Num[i] + dop;
                    dop = 0;
                }
                else {
                    s1.Num[i] = s1.Num[i] + s2.Num[i] + dop - 10;
                    dop = 1;
                }
            }
            if (dop > 0 && index)
                throw "Overflow";
            if (!index) {
                if ((this)->Large(t)) {
                    s1.Num[0] = Num[0];
                }
                else s1.Num[0] = t.Num[0];
            }
            if (index)s1.Num[0] = Num[0];
            s1 = s1.AddCode();
            for (int i = j; i > 0; i--) {
                if (s1.Num[i] != 0) {
                    s1.n = i;
                    break;
                }
            }
            return s1;
        }
        catch (const std::exception& msg) {
            std::cout << msg.what() << std::endl;
            bigDecNum inc;
            return inc;
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
        try {
            bigDecNum inc;
            inc.n = n + 1;
            inc.Num[0] = Num[0];
            if (Num[SZ] != 0)
                throw "Overflow";
            inc.Num[1] = 0;
            for (int i = n; i >= 1; i--)
                inc.Num[i+1] = Num[i];
            return inc;
        }
        catch (const std::exception& msg) {
            std::cout << msg.what() << std::endl;
            return *this;
        }
    }
    bigDecNum bigDecNum::Dec10() const
    {
        bigDecNum inc;
        inc.n = n - 1;
        inc.Num[0] = Num[0];
        if (n == 1) return inc;
        for (int i = n; i >= 2; i--)
            inc.Num[i - 1] = Num[i];
        return inc;
    }

    bigDecNum bigDecNum::InputStr() const{
        try {
            const char* ptr = "";
            int n;
            int len = 0;
            std::string ss;
            std::cin >> ss;
            if (ss.std::string::length() > SZ + 1)
            {
                std::cout << "Overflow. You enter too big number" << std::endl;
                return *this;
            }
            ptr = ss.c_str();
            std::cin.clear();
            bigDecNum a(ptr);
            return a;

        }
        catch (const std::exception& msg) {
            std::cout << msg.what() << std::endl;
        }
    }
    void bigDecNum::Print() const
    {
        if (Num[0] == 1)
            std::cout << "-";
        bool k = false;
        if (n == 1) {
            if (Num[1] == 0) k = true;
        }
        if (k) std::cout << 0;
        else {
            for (int i = n; i >= 1; i--) {
                int t = Num[i];
                std::cout << t;
            }
        }
    }
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

        n = getNatInt(rc);
        if (n == 0)
            rc = 0;
    } while (rc < 0 || rc >= N);
    return rc;
}

int dialog_inputStr(bigDecNum &bigDecNum) {
    str ss;
    std::cout << "Enter your big decimal number: " << std::endl;
    std::cin >> ss;
    int f = std::cin.good();
    if (f) {
        try {
            bigDecNum.InputStr(ss);
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    else{
        std::cout<< "Repeat again!";
        dialog_inputStr(bigDecNum);
    }

    return 1;
}

int dialog_inputLong(bigDecNum &bigDecNum) {
    long num;
    std::cout << "Enter your big decimal number: " << std::endl;
    std::cin >> num;
    int f = std::cin.good();
    if (f) {
        try {
            bigDecNum.InputLong(num);
        }
        catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    else{
        std::cout<< "Repeat again!";
        dialog_inputStr(bigDecNum);
    }

    return 1;
}

///

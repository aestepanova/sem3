#ifndef LAB4_GUEST_H
#define LAB4_GUEST_H

#include <iostream>
#include <ctime>
#include <utility>

#define CUR_YEAR 2021

using namespace std;

inline int getInt(int &n) { //for natural int
    std::cin >> n;
    if (!std::cin.good())    // обнаружена ошибка ввода или конец файла
        return -1;
    if (n >= std::numeric_limits<int>::max()) return -2;
    if (n < 0) return 0;
    return 1;
}

namespace lab4{
    struct Date{
        int day, month, year;
        Date(): day(1), month(1), year(CUR_YEAR){};
        Date(int t_day, int t_mon, int t_year): day(t_day), month(t_mon), year(t_year){};

        void set_date(){
            cout << "day: \n";
            cin >> day;
            cout << "month: \n";
            cin >> month;
        }

        void print() const{
          std::cout << "date: " << day << "/" << month << "/" << year << std::endl;

        }

    };

    struct Guest{
        Date regDate;
        int days;
        std::string name;

        Guest(): regDate(), days(1), name("-"){};
        Guest(Date d, int ds, std::string nm): regDate(d), days(ds), name(std::move(nm)){};

        void reg(){
            int f = 0;
            do{
                cin.clear();
                cout << "What surname should I use to register the number? \n";
                cin >> name;
                cin.clear();
                cout << "How much days do you want to live in Ancho's Hotel?\n";
                getInt(days);
                cin.clear();
                cout << "When do you want to check in?\n";
                regDate.set_date();
                cin.clear();
                cout << "Check your info: \n-----------------\n";
                this->print();
                cout << "If everything is right - enter 1, else - any key\n";
                getInt(f);
                cin.clear();
                if (f!=1) f = 0;
            }while (f==0);

        };

        void print() const{
            std::cout << "Guest: " << this->name << std::endl << "days: " << this->days << std::endl;
            this->regDate.print();
        }

    };
}



#endif //LAB4_GUEST_H

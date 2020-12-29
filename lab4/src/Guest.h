#ifndef LAB4_GUEST_H
#define LAB4_GUEST_H

#include <iostream>
#include <ctime>
#include <utility>


#define CUR_YEAR 2021
#define LINE "-------------------"

using namespace std;

inline int getInt(int &n) { //for natural int
    std::cin.ignore(32767, '\n');
    cin >> n;
    if (!std::cin.good()){ // обнаружена ошибка ввода или конец файла
        cin.clear();
        return -1;
    }


    if (n >= std::numeric_limits<int>::max()) return -2;
    if (n < 0) return 1;
    return 0;
}

namespace lab4{
    struct Date{
        int day, month, year;
        Date(): day(1), month(1), year(CUR_YEAR){};
        Date(int t_day, int t_mon, int t_year): day(t_day), month(t_mon), year(t_year){};

        void check_date(){
            if ((day<1)||(day>31)||(month<1)||(month>12)){
                day = 1;
                month = 1;
                cout << "Incorrect date!\n";
            }
        }

        void set_date(){
            cout << "day: \n";
            cin >> day;
            cout << "month: \n";
            cin >> month;
            check_date();
        }

        void print() const{
          std::cout << "date: " << day << "/" << month << "/" << year << endl << LINE << endl;
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
                cin.ignore(32767, '\n');
                cout << "What surname should I use to register the number? \n";
                cin >> name;
                cout << "How much days, " << "Mr/Mrs " << name <<", do you want to live in Ancho's Hotel?\n";
                getInt(days);
                cout << "When do you want to check in?\n";
                regDate.set_date();
                cout << "Check your info: \n-----------------\n";
                this->print();
                cout << "If everything is right - enter 1, else - any key\n";
                //cin.ignore(32767, '\n');
                getInt(f);
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

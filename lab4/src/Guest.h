#ifndef LAB4_GUEST_H
#define LAB4_GUEST_H

#include <iostream>
#include <ctime>


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
    /// Структура "Дата" для корректного вывода даты
    struct Date{
        int day, month, year;
        Date(): day(1), month(1), year(1900){};
        Date(int t_day, int t_mon, int t_year): day(t_day), month(t_mon), year(t_year){};


        void print() const{
          std::cout << "\tdate: " << day << "/" << month << "/" << year << endl << LINE << endl;
        }

    };

    /// Структура "Гость"
    struct Guest{
        Date regDate;
        int days;
        std::string name;

        Guest(): regDate(), days(1), name("-"){};
        Guest(Date d, int ds, std::string nm): regDate(d), days(ds), name(std::move(nm)){};

        void reg(){
            time_t now = time(nullptr);
            tm *ltm = localtime(&now);
            int f = 0;
            do{
                cin.ignore(32767, '\n');
                cout << "What surname should I use to register the number? \n";
                cin >> name;
                cout << "How much days, " << "Mr/Mrs " << name <<", do you want to live in Ancho's Hotel?\n";
                getInt(days);
                regDate.day = ltm->tm_mday;
                regDate.month =1 + ltm->tm_mon;
                regDate.year = 1900 + ltm->tm_year;
                cout << "Check your info: \n-----------------\n";
                this->print();
                cout << "If everything is right - enter 1, else - any key\n";
                getInt(f);
                if (f!=1) f = 0;
            }while (f==0);

        };

        void print() const{
            std::cout << "\tGuest: " << this->name << std::endl << "\tdays: " << this->days << std::endl;
            this->regDate.print();
        }

    };
}



#endif //LAB4_GUEST_H

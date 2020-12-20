#ifndef LAB4_GUEST_H
#define LAB4_GUEST_H

#include <iostream>


namespace lab4{
    struct Date{
        int day, month, year;
        Date(): day(1), month(1), year(2020){};
        Date(int t_day, int t_mon, int t_year): day(t_day), month(t_mon), year(t_year){};

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

        void print() const{
            std::cout << this->name << std::endl << "days: " << this->days << std::endl;
            this->regDate.print();
        }

    };
}



#endif //LAB4_GUEST_H

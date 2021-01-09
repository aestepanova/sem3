#ifndef LAB4_SUITE_H
#define LAB4_SUITE_H

#include <iostream>
#include <utility>
#include "Guest.h"


using namespace std;
namespace lab4 {
    /// Базовый класс Номер
    class Suite{
    private:
        string type; // тип номера
        int number; //номер на двери
        int busy; // занятость (1 - да, 0 - свободен)
        int cost; //цена за день
        //int curFree; // количество свободных номеров на данный момент
        int numGuests; // количество гостей в номере

    protected:
        Suite() : type("Unary"), number(0), busy(0), cost(100), numGuests(1) {};
        explicit Suite(string type, int cost = 100) : Suite() {Suite::type = std::move(type); Suite::cost = cost;};
        Suite(string type, int num, int busy, int cost, int num_guests) :
                type(std::move(type)), number(num), busy(busy), cost(cost), numGuests(num_guests) {};

    public:
        [[nodiscard]] string getType() const { return type;}
        [[nodiscard]] int getNumber() const { return number;}
        [[nodiscard]] int isFree() const { return (busy>0) ? 0:1; }
        [[nodiscard]] int getCost() const { return cost;}
        [[nodiscard]] int getNumGuests() const { return numGuests;};

        Suite& setType(string t);
        Suite& setNumber(int t);
        Suite& setBusy(int t);
        Suite& setCost(int t);
        Suite& setNumGuests(int t);

        virtual std::ostream& print(std::ostream& s) const { return s;};
        friend std::ostream& operator << (std::ostream& s, Suite* suite){
            suite->print(s);
            return s;
        }
        virtual ~Suite()= default;;

        virtual void showInfo() = 0;
        virtual void registerG() = 0;
        virtual void unregisterG() = 0;
    };
};


#endif //LAB4_SUITE_H

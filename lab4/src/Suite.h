#ifndef LAB4_SUITE_H
#define LAB4_SUITE_H

#include <iostream>
#include "Guest.h"


using namespace std;
namespace lab4 {
    #define MAX_SIZE 77


    /// Базовый класс номер ///

    class Suite{
    private:
        string type; // тип номера
        int number; //номер на двери
        int busy; // занятость (1 - да, 0 - свободен)
        int cost; //цена за день
        const int totalNum = MAX_SIZE; //общее количество номеров
        int curFree; // количество свободных номеров на данный момент
        int numGuests; // количество гостей в номере

    protected:
        Suite() : type("Unary"), number(0), busy(0), cost(100), curFree(MAX_SIZE), numGuests(0){};
        Suite(string type) : Suite() {Suite::type = type;};
        Suite(string type, int num, int busy, int cost, int cur, int num_guests) :
            type(type), number(num), busy(busy), cost(cost), curFree(cur), numGuests(num_guests) {};

    public:
        [[nodiscard]] string getType() const { return type;}
        [[nodiscard]] int getNumber() const { return number;}
        [[nodiscard]] int isFree() const { return (busy>0) ? 1:0; }
        [[nodiscard]] int getCost() const { return cost;}
        [[nodiscard]] int getTotalNum() const { return totalNum;}
        [[nodiscard]] int getCurFree() const { return curFree;};
        [[nodiscard]] int getNumGuests() const { return numGuests;};

        Suite& setType(string t);
        Suite& setNumber(int t);
        Suite& setBusy(int t);
        Suite& setCost(int t);
        Suite& setCurFree(int t);
        Suite& setNumGuests(int t);

        virtual std::ostream& print(std::ostream& s) const { return s;};
        friend std::ostream& operator << (std::ostream& s, Suite* suite){
            suite->print(s);
            return s;
        }
        virtual ~Suite(){};

        virtual void showInfo() = 0;
        virtual void registerG(Guest& gue, string& type) = 0;
        virtual void unregisterG(Guest& gue, string& type) = 0;
    };
};


#endif //LAB4_SUITE_H

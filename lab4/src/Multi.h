#ifndef LAB4_MULTI_H
#define LAB4_MULTI_H

#include <vector>
#include "Guest.h"
#include "Suite.h"

using namespace std;

namespace lab4 {
#define M_COST 3000
#define BEDS 4

    /// Описатель номера типа "Многоместный", наследует состояние класса Suite

    class Multi : public Suite {
    private:
        int beds; // всего мест
        int current; // занято на данный момент
        vector<Guest*> guests;

    public:
        Multi() : Suite("Multi", M_COST), beds(BEDS), current(0) {};

        Multi(string type, int num, int busy, vector<Guest*>& gue, int cost, int beds, int current ) :
                Suite(std::move(type), num, busy, cost, current), beds(beds), current(current) {
            guests.resize(gue.size());
            for (int i = 0; i < gue.size(); i++ ){
                guests[i] = gue[i];
            }
        };
        void setBeds(int b){ this->beds = b;}
        void setCurrent(int cur){ this->current=cur;}
        int getBeds(){return this->beds;}
        int getCurrent() {return this->current;}
        void showInfo() override;

        void registerG() override;
        void unregisterG() override;
        void unregG(const string& name);
        Guest* findG(const string& name);
        void showG();

        ~Multi() override = default;;
    };
}

#endif //LAB4_MULTI_H

#ifndef LAB4_UNARY_H
#define LAB4_UNARY_H

#include <utility>

#include "Guest.h"
#include "Suite.h"

using namespace std;

namespace lab4{
    #define U_COST 5000

    class Unary : public Suite {
    protected:
        Guest guest;
    public:
        Unary() : Suite("Unary", U_COST), guest(){};
        explicit Unary(string t, int cost = U_COST) : Suite(std::move(t), cost), guest(){};
        Unary(string type, int num, int busy, int cost, Guest gue, int guests = 1) :
                Suite(std::move(type), num, busy, U_COST, guests), guest(std::move(gue)){};
        void showInfo() override;
        void registerG() override;
        void unregisterG() override ;

        ~Unary() override = default;
    };

}

#endif //LAB4_UNARY_H

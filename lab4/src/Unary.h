#ifndef LAB4_UNARY_H
#define LAB4_UNARY_H

#include <utility>

#include "Guest.h"
#include "Suite.h"

using namespace std;

namespace lab4{
    #define U_COST 5000

    class Unary : public Suite {
    private:
        Guest guest;
    public:
        Unary() : Suite("Unary"), guest(){};
        explicit Unary(string t) : Suite(std::move(t)), guest(){};
        Unary(string type, int num, int busy, int cost, Guest gue) :
                Suite(std::move(type), num, busy, U_COST, 1), guest(std::move(gue)){};
        void showInfo() override;
        void registerG() override;
        void unregisterG() override ;

        ~Unary() override = default;
    };

}

#endif //LAB4_UNARY_H

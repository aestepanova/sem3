#ifndef LAB4_UNARY_H
#define LAB4_UNARY_H

#include "Guest.h"
#include "Suite.h"

using namespace std;

namespace lab4{
    class Unary : public Suite {
    private:
        Guest guest;
    public:
        Unary() : Suite("Unary"), guest(){};
        Unary(string type, int num, int busy, int cost, int cur, Guest gue) :
                Suite(std::move(type), num, busy, cost, cur, 1), guest(std::move(gue)){};
        void showInfo() override;
        void registerG(Guest& gue, string& type);
        void unregisterG(Guest& gue, string& type);

        ~Unary() override = default;
    };

}

#endif //LAB4_UNARY_H

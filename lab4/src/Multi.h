#ifndef LAB4_MULTI_H
#define LAB4_MULTI_H

#include <vector>
#include "Guest.h"
#include "Suite.h"

using namespace std;

namespace lab4 {
#define M_COST 3000
    class Multi : public Suite {
    private:
        int beds; // всего мест
        int current; // занято на данный момент
        vector<Guest> guests;

    public:
        Multi() : Suite("Multi"), beds(2), current(0) {
            guests.resize(1);
            guests[0] = Guest();
        };

        Multi(string type, int num, int busy, vector<Guest>& gue, int beds, int current ) :
                Suite(std::move(type), num, busy, M_COST, current), beds(beds), current(current) {
            guests.resize(gue.size());
            for (int i = 0; i < gue.size(); i++ ){
                guests[i] = gue[i];
            }
        };

        void showInfo() override;

        void registerG() override;

        void unregisterG() override;

        ~Multi() override = default;;
    };
}

#endif //LAB4_MULTI_H

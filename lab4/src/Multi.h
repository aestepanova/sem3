#ifndef LAB4_MULTI_H
#define LAB4_MULTI_H

#include <vector>
#include "Guest.h"
#include "Suite.h"

using namespace std;

namespace lab4 {
    class Multi : public Suite {
    private:
        int beds;
        int current;
        vector<Guest> guests;

    public:
        Multi() : Suite("Multi"), beds(2) {
            guests.resize(1);
            guests[0] = Guest();
        };

        Multi(string type, int num, int busy, int cost, int cur, vector<Guest>& gue, int beds, int current ) :
                Suite(std::move(type), num, busy, cost, cur, current), beds(beds), current(current) {
            guests.resize(gue.size());
            for (int i = 0; i < gue.size(); i++ ){
                guests[i] = gue[i];
            }
        };

        void showInfo() override;

        void registerG(Guest &gue, string &type);

        void unregisterG(Guest &gue, string &type);

        ~Multi() override = default;
    };
}

#endif //LAB4_MULTI_H

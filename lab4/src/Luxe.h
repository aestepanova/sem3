#ifndef LAB4_LUXE_H
#define LAB4_LUXE_H

#include "Guest.h"
#include "Suite.h"

using namespace std;

namespace lab4 {
    class Luxe : public Suite {
    private:
        Guest guestMaster;
        int rooms;
        int guests;

    public:
        Luxe() : Suite("Luxe"), guestMaster(), rooms(2), guests(0) {};

        Luxe(string type, int num, int busy, int cost, int cur, Guest gue, int rooms, int guests) :
                Suite(std::move(type), num, busy, cost, cur, guests), guestMaster(std::move(gue)), rooms(rooms) {};

        void showInfo() override;

        void registerG(Guest &gue, string &type);

        void unregisterG(Guest &gue, string &type);

        ~Luxe() override = default;
    };
}

#endif //LAB4_LUXE_H
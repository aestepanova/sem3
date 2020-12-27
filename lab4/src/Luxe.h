#ifndef LAB4_LUXE_H
#define LAB4_LUXE_H

#include <utility>

#include "Guest.h"
#include "Unary.h"

using namespace std;

namespace lab4 {
#define L_COST 15000
    class Luxe : public Unary {
    private:
        int rooms;
    public:
        Luxe() : Unary("Luxe"), rooms(2){};

        Luxe(string type, int num, int busy, Guest gue, int rooms, int guests) :
                Unary(std::move(type), num, busy, L_COST, std::move(gue)), rooms(rooms) {};

        void showInfo() override;

        void registerG() override;

        void unregisterG() override;

        ~Luxe() override= default;;
    };
}

#endif //LAB4_LUXE_H
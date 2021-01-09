#ifndef LAB4_LUXE_H
#define LAB4_LUXE_H

#include "Guest.h"
#include "Unary.h"

using namespace std;

namespace lab4 {
#define L_COST 15000
    /// Описатель номера типа "Люкс", наследует состояние класса Unary
    class Luxe : public Unary {
    private:
        int rooms;
    public:
        Luxe() : Unary("Luxe", L_COST), rooms(2){};

        Luxe(string type, int num, int busy, Guest gue, int cost, int rooms, int guests) :
                Unary(std::move(type), num, busy, cost, std::move(gue), guests), rooms(rooms) {};

        [[nodiscard]] int getRooms() const {return rooms;}

        void setRooms(int &r){ rooms = r;}

        void showInfo() override;

        void registerG() override;

        void unregisterG() override;

        ~Luxe() override= default;;
    };
}

#endif //LAB4_LUXE_H
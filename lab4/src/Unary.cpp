#include "Unary.h"

void lab4::Unary::showInfo() {
    cout << "----------------\nType: " << this->getType() << endl;
    cout << "Number: " << this->getNumber() << endl;
    int t = this->isFree();
    cout << ((t==1) ? "This number is free\n" : "This number is busy\n");
    cout << "Number of guests: " << this->getNumGuests() << endl;
    this->guest.print();
}

void lab4::Unary::registerG() {
    this->guest.reg();
}

void lab4::Unary::unregisterG() {
    this->setBusy(0);
    cout<< "Your accommodation bill: " << (this->guest.days)*(this->getCost()) << endl;
}




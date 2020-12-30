#include "Unary.h"

void lab4::Unary::showInfo() {
    cout << "Type: " << this->getType() << endl;
    cout << "Number: [" << this->getNumber() << "]\n";
    int t = this->isFree();
    cout << ((t==1) ? "This number is free\n" : "This number is busy\n");
    cout << "Number of guests: " << this->getNumGuests() << endl;
    this->guest.print();
}

void lab4::Unary::registerG() {
    this->guest.reg();
    cout << "Your number is [" << this->getNumber() << "]. Welcome to Ancho's Hotel!\n" << endl;
}

void lab4::Unary::unregisterG() {
    cout << this->guest.name <<", your accommodation bill: " << (this->guest.days)*(this->getCost()) << endl;
    cout << "Thank you for choosing our hotel, please come again!\n";
}




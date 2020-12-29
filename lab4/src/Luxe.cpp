#include "Luxe.h"

void lab4::Luxe::showInfo() {
    cout << "Type: " << this->getType() << endl;
    cout << "Number: [" << this->getNumber() << "]\n";
    int t = this->isFree();
    cout << ((t==1) ? "This number is free\n" : "This number is busy\n");
    cout << "Number of guests: " << this->getNumGuests() << endl;
    cout << "Master guest -> \n";
    this->Unary::guest.print();
}

void lab4::Luxe::unregisterG() {
    this->setBusy(0);
    cout << "Your accommodation bill: " << (this->guest.days) * this->getCost() << endl;
}

void lab4::Luxe::registerG() {

    int ng=3;
    do{
        cout << "Please, enter number of guests(1-2): \n";
        if (getInt(ng) != 0){
            cout << "Incorrect!\n";
        }
        if ((ng > 0)&&(ng<=2)){
            this->setNumGuests(ng);
        } else cout << "We have luxes only up to 2 guests\n";
        cin.clear();
    } while ((ng>2)||(ng<=0));

    int r;
    do{
        cout << "How many rooms do you need?\n";
        if (getInt(r) != 0) cout << "Incorrect!\n";
        if (r > 1 && (r <= 3)){
            this->setRooms(r);
        } else cout << "We cam offer you luxes up to 3 rooms\n";
    } while (r > 3 || (r <= 0));


    cout << "Enter information about the guest to whom the room will be registered ---> \n";
    this->guest.reg();

    cout << "Your number is [" << this->getNumber() << "]. Welcome to Ancho's Hotel!\n" << endl;
}
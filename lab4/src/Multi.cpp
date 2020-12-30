#include "Multi.h"

void lab4::Multi::showInfo() {
    cout << "Type: " << this->getType() << endl;
    cout << "Number: [" << this->getNumber() << "]\n";
    int t = this->isFree();
    cout << ((t==1) ? "This number is free\n" : "This number is busy\n");
    cout << "Number of guests: " << this->getNumGuests() << endl;
    this->showG();
}

void lab4::Multi::unregisterG() {
    string gName;
    cout << "What is your name?";
    cin >> gName;
    Guest* g = findG(gName);
    if ( g != nullptr) {
        cout << g->name <<", your accommodation bill: " << (g->days)*(this->getCost()) << endl;
        this->current -= 1;
        this->unregG(gName);
        cout << "Thank you for choosing our hotel, come again!\n";
    }

}

void lab4::Multi::registerG() {

}

lab4::Guest* lab4::Multi::findG(const string& name) {
        if (!(this->guests.empty())){
            std::vector<Guest*>::iterator it;
            for(it = this->guests.begin(); it < this->guests.end(); it++) {
                if (name == ((*it)->name)) {
                    return *it;
                }
            }
        }
    return nullptr;
}

void lab4::Multi::showG() {
    cout << endl << LINE << endl;
    if (!(this->guests.empty())){
        for (int i = 0; i < this->guests.size(); i++) {
            guests[i]->print();
            cout<< endl << LINE << endl;
        }
    }else{
        cout << "There is no guests.\n" << LINE << endl;
    }
}

void lab4::Multi::regG() {

    Guest g;
    g.reg();
    if (this->guests.size() <= beds;
    cout << "Your number is [" << this->getNumber() << "]. Welcome to Ancho's Hotel!\n" << endl;
}

void lab4::Multi::unregG(const string& name) {
    Guest* g = this->findG(name);
    if (g) {
        std::vector<Guest*>::iterator it;
        for (it = this->guests.begin(); it < this->guests.end(); it++) {
            if (g == (*it)) {
                guests.erase(it); // delete guest from vector
                this->setCurrent(this->getNumGuests()-1);
            }
        }
    }
}

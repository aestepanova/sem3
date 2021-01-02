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
    cout << "What is your name?\n";
    cin >> gName;
    Guest* g = findG(gName);
    if ( g != nullptr) {
        cout << gName <<", your accommodation bill: " << (g->days)*(this->getCost()) << endl;
        this->current -= 1;
        this->unregG(gName);
        cout << "Thank you for choosing our hotel, come again!\n";
    } else {
        cout << "We haven't a guest with this name.\n";
    }
}

void lab4::Multi::registerG() {
    if (this->guests.size() <= beds){
        auto* g = new Guest;
        g->reg();
        this->guests.push_back(g);
        cout << "Your number is [" << this->getNumber() << "]. Welcome to Ancho's Hotel!\n" << endl;
    }
    else {
        cout << "This number hasn't free beds.\n";
    }
}

lab4::Guest* lab4::Multi::findG(const string& name) {
        if (!(this->guests.empty())){
            std::vector<Guest*>::iterator it;
            for(it = this->guests.begin(); it < this->guests.end(); it++) {
                if (name == ((*it)->name)) {
                    return (*it);
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
    cout << "/////////////////////////\n";
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
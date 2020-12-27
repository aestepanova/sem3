#include "Suite.h"

using namespace lab4;

Suite &Suite::setType(string t) {

    this->type = std::move(t);

    return *this;
}

Suite &Suite::setNumber(int t) {

    this->number = t;

    return *this;
}

Suite &Suite::setBusy(int t) {

    this->busy = t;

    return *this;
}

Suite &Suite::setCost(int t) {

    this->cost = t;

    return *this;
}

Suite &Suite::setNumGuests(int t) {

    this->numGuests = t;

    return *this;
}


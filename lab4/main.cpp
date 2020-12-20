#include <iostream>
#include "src/Suite.cpp"

using namespace lab4;

int main() {

    Date d(2, 10, 1970);
    d.print();
    Guest g(d,15, "Ivan");

    g.print();
    return 0;
}

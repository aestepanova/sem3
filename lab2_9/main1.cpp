


#include "Lemniscate.h"
#include <iostream>
const char *msgs[] = {" 0. Exit",
                      " 1. Input inner focus",
                      " 2. Input \"angle\" and get polar radius",
                      " 3. Get curve length",
                      " 4. Get curved area",
                      " 5. Input \"t\" and get (x, y)",
                      " 6. Get equation"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int main() {
    Prog2::Lemniscate L;
    int rc = Prog2::dialog(msgs, NMsgs);
    int fl1 = 1;
    double c;
    while (fl1) {
        std::cout << "Your lemniscate is:" << std::endl;
        std::cout << L.formula() << std::endl;
        std::cout << "Focus distance of lemniscate " << L.focusdist() << std::endl;
        std::cout << "Maximum polar radius is " << L.rad() << std::endl;
        std::cout << "Area of two lemniscate's petals " << L.S() << std::endl;
        int fl2 = 1;
        while (fl2) {
            std::cout << "Enter angle to calculate polar radius or press ctrl+Z to quit:" << std::endl;
            double ang;
            std::cin >> ang;
            fl2 = std::cin.good();
            if (!fl2)
                continue;
            try {
                double res = L.polardist(ang);
                std::cout << "r = " << res;
                std::cout << std::endl;
            }
            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        fl2 = 1;
        while (fl2) {
            std::cout << "Enter angle to calculate the radius of curvature or press ctrl+Z to quit:" << std::endl;
            double ang;
            std::cin >> ang;
            fl2 = std::cin.good();
            if (!fl2)
                continue;
            try {
                double res = L.radAngle(ang);
                std::cout << "R = " << res << std::endl;;
            }
            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        fl2 = 1;
        while (fl2) {
            std::cout << "Enter polar radius to calculate the radius of curvature or press ctrl+Z to quit:" << std::endl;
            double ang;
            std::cin >> ang;
            fl2 = std::cin.good();
            if (!fl2)
                continue;
            try {
                double res = L.radRad(ang);
                std::cout << "R = " << res << std::endl;;
            }
            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        std::cin.clear();
        fl2 = 1;
        while (fl2) {
            std::cout << "Enter angle to calculate the sector area or press ctrl+Z to quit:" << std::endl;
            double ang;
            std::cin >> ang;
            fl2 = std::cin.good();
            if (!fl2)
                continue;
            try {
                double res = L.Ssector(ang);
                std::cout << "S = " << res << std::endl;;
            }
            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        c = 0;
        do {
            std::cout << "Enter new quantity of focus to continue or press ctrl+Z to quit:" << std::endl;
            std::cin >> c;
            fl2 = 0;
            if (std::cin.good()) {
                try {
                    L.setFocus(c);
                }
                catch (std::exception& ex) {
                    std::cout << ex.what() << std::endl;
                    fl2 = 1;
                    continue;
                }
            }
            else
                fl1 = 0;
        } while (fl2);
    }
    return 0;
}
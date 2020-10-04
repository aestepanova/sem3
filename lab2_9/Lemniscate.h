//
// Created by user on 04.10.2020.
//

#ifndef LAB2_LEMNISCATE_H
#define LAB2_LEMNISCATE_H

#include <math.h>
#include <sstream>
#include <iostream>

namespace Prog2 {
    class Lemniscate{
    private:
        double f;
    public:
        explicit Lemniscate (double focus = 1.0); //чтобы не было неявных преобразований

        Lemniscate& setFocus(double focus);
        double getFocus() const { return f; };
        double focusdist() const { return 2 * f; };
        double rad() const { return sqrt(2) * f; };
        double polardist(double ang) const;
        std::string formula() const;
        double S() const { return 2 * (f * f); };
        double radAngle(double ang) const;
        double radRad(double rad) const;

        double Ssector(double ang) const;

        ~Lemniscate(){
            std::cout << "Destructor called for Lemniscate with focus " << f << std::endl;
        }
    };

    inline int getNatInt(int& n, const int max=std::numeric_limits<int>::max()) { //for natural int
        std::cin >> n;
        if (!std::cin.good())	// обнаружена ошибка ввода или конец файла
            return -1;
        if (n>=max) return -2;
        if (n<=0) return 0;
        return 1;
    }

    int dialog(const char *[], int);

    int dialog_input(Lemniscate &);
    int dialog_showFormula(Lemniscate &);
    int dialog_getPolarDist(Lemniscate &);

    int dialog_getRadiusAngle(Lemniscate &);
    int dialog_getRadiusRad(Lemniscate &);
    int dialog_getAreaSector(Lemniscate &);
    int dialog_getArea(Lemniscate &);

}

#endif //LAB2_LEMNISCATE_H

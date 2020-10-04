//
// Created by user on 04.10.2020.
//
#include "Lemniscate.h"
#include <sstream>
#include <stdexcept>

double const PI = 3.141592;

namespace Prog2 {
    Lemniscate::Lemniscate(double focus) {
        this->setFocus(focus);
    }

    Lemniscate& Lemniscate::setFocus(double focus) {
        if (focus == 0)
            throw std::invalid_argument("Invalid focus");
        f = abs(focus);
        return *this;
    }

    double Lemniscate::Ssector(double ang) const {
        if (ang >= 360 || ang < 0)
            throw std::invalid_argument("Invalid angle");
        if (ang == 0) return 0;
        if (ang == 180) return f * f;
        if (ang == 360) return 2 * f * f;
        double ang1=ang, s=0;
        if (ang1 >= 180) {
            s = s + f * f;
            ang1 = ang1 - 180;
        }
        if (ang1 >= 45) {
            s = s + f * f/2;
            ang1 = ang1 - 135;
            if (ang1 > 0) {
                ang1 = ang1 * PI / 180;
                s = s + f * f / 2 - (f * f * sin(2 * (PI / 4 - ang1)) / 2);
            }
        }
        else {
            ang1 = ang1 * PI / 180;
            s =s+ f * f * sin(2 * ang1) / 2;
        }
        return s;
    }

    double Lemniscate::polardist(double ang) const {
        if (ang >= 360 || ang < 0)
            throw std::invalid_argument("Invalid angle");
        if ((ang>45 && ang<135)||(ang>225 && ang<315))
            throw std::invalid_argument("Invalid angle");
        double ang1=ang;
        if (ang > 135 && ang < 180) ang1 = 180 - ang1;
        else if (ang > 180 && ang < 225) ang1 = ang - 180;
        else if(ang<45 || ang>315) ang1 = ang;
        ang1 = ang1 * PI / 180;
        return sqrt(2 * f * f * cos(2 * ang1));
    }

    double Lemniscate::radAngle(double ang) const {
        if (ang >= 360 || ang < 0)
            throw std::invalid_argument("Invalid angle");
        if ((ang > 45 && ang < 135) || (ang > 225 && ang < 315))
            throw std::invalid_argument("Invalid angle");
        double ang1=ang;
        if (ang > 135 && ang < 180) ang1 = 180 - ang1;
        else if (ang > 180 && ang < 225) ang1 = ang - 180;
        else if (ang < 45 || ang>315) ang1 = ang;
        ang1 = ang1 * PI / 180;
        return ((2 * f )/ (3 * sqrt(2 * cos(2 * ang1))));
    }
    double Lemniscate::radRad(double rad) const {
        if (rad <0 )
            throw std::invalid_argument("Invalid radius");
        if(rad>abs(sqrt(2 * f * f * cos(0))))
            throw std::invalid_argument("Invalid radius");
        return 2 * f * f /( 3 * rad);
    }
    std::string Lemniscate::formula() const {
        std::stringstream ss;
        ss << " (x ^ 2 + y ^ 2) ^ 2 = 2 * " << f << "^ 2 * (x ^ 2 - y ^ 2)";
        return ss.str();
    }

    int dialog(const char *msgs[], int N) {
        std::string errmsg;
        int rc, n;
        do {
            std::cout << errmsg;
            errmsg = "You are wrong. Repeat, please\n";
            for (int j = 0; j < N; ++j)
                puts(msgs[j]);
            puts("Make your choice: --> ");

            n = getNatInt(rc);
            if (n == 0)
                rc = 0;
        } while (rc < 0 || rc >= N);
        return rc;
    }

    int dialog_input(Lemniscate &Lemniscate) {
        float c;
        std::cout << "Enter new quantity of focus" << std::endl;
        std::cin >> c;
        int f = std::cin.good();
        if (f) {
            try {
                Lemniscate.setFocus(c);
            }
            catch (std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else{
            std::cout<< "Repeat again!";
            dialog_input(Lemniscate);
        }

        return 1;
    }


    int dialog_showFormula(Lemniscate &Lemniscate) {
        std::cout << "Your lemniscate is:" << std::endl;
        std::cout << Lemniscate.formula() << std::endl;
        return 1;
    }

    int dialog_getPolarDist(Lemniscate &Lemniscate) {
        std::cout << "Enter angle to calculate polar radius:" << std::endl;
        double ang;
        std::cin >> ang;
        int f = std::cin.good();
        if (f) {
            try {
                double res = Lemniscate.polardist(ang);
                std::cout << "r = " << res;
                std::cout << std::endl;
            }
            catch (std::exception &ex) {
                std::cout << ex.what() << std::endl;
            }
        }else{
            std::cout<< "Repeat again!";
            dialog_getPolarDist(Lemniscate);
        }
        return 1;
    }



    int dialog_getRadiusAngle(Lemniscate &Lemniscate) {
        std::cout << "Enter angle to calculate the radius of curvature" << std::endl;
        double ang;
        std::cin >> ang;
        int f = std::cin.good();
        if (f) {
            try {
                double res = Lemniscate.radAngle(ang);
                std::cout << "R = " << res << std::endl;;
            }
            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }else{
            std::cout<< "Repeat again!";
            dialog_getRadiusAngle(Lemniscate);
        }
        return 1;
    }

    int dialog_getRadiusRad(Lemniscate &Lemniscate) {
        std::cout << "Enter polar radius to calculate the radius of curvature" << std::endl;
        double ang;
        std::cin >> ang;
        int f = std::cin.good();
        if (f) {
            try {
                double res = Lemniscate.radRad(ang);
                std::cout << "R = " << res << std::endl;;
            }
            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }else{
            std::cout<< "Repeat again!";
            dialog_getRadiusRad(Lemniscate);
        }
        return 1;
    }

    int dialog_getAreaSector(Lemniscate &Lemniscate) {
        std::cout << "Enter angle to calculate the sector area or press ctrl+Z to quit:" << std::endl;
        double ang;
        std::cin >> ang;
        int f = std::cin.good();
        if (f) {
            try {
                double res = Lemniscate.Ssector(ang);
                std::cout << "S = " << res << std::endl;;
            }
            catch (std::exception& ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }else{
            std::cout<< "Repeat again!";
            dialog_getAreaSector(Lemniscate);
        }
        return 1;
    }

    int dialog_getArea(Lemniscate &Lemniscate) {
        std::cout << "Area of two lemniscate's petals " << Lemniscate.S() << std::endl;
        return 1;
    }

}

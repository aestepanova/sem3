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
        f = std::abs(focus);
        return *this;
    }

    std::string Lemniscate::formula() const {
        std::stringstream ss;
        ss << " (x ^ 2 + y ^ 2) ^ 2 = 2 * " << f << "^2 * (x ^ 2 - y ^ 2)";
        return ss.str();
    }

    double Lemniscate::radAngle(double angle) const {
        if (angle>= 360 || angle< 0){
            throw std::invalid_argument("Invalid angle");
        }
        if ((angle> 45 && angle< 135) || (angle> 225 && angle< 315)){
            throw std::invalid_argument("Invalid angle");
        }
        double ang1=angle;
        if (angle> 135 && angle< 180)
            ang1 = 180 - ang1;
        else if (angle> 180 && angle< 225)
            ang1 = angle- 180;
        else if (angle< 45 || angle>315)
            ang1 = angle;
        ang1 = ang1 * PI / 180;

        return ((2 * f )/ (3 * sqrt(2 * cos(2 * ang1))));
    }

    double Lemniscate::sectorArea(double angle) const {
        if (angle>= 360 || angle< 0)
            throw std::invalid_argument("Invalid angle");
        if (angle== 0) return 0;
        if (angle== 180) return f * f;
        if (angle== 360) return 2 * f * f;
        double ang1=angle, s=0;
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

    double Lemniscate::polarDist(double angle) const {
        if (angle >= 360 || angle < 0){
            throw std::invalid_argument("Invalid angle");
        }
        if ((angle > 45 && angle < 135) || (angle > 225 && angle < 315)){
            throw std::invalid_argument("Invalid angle");
        }
        double ang=angle;
        if (angle > 135 && angle < 180){
            angle= 180 - ang;
        } else if (angle > 180 && angle < 225) {
            angle= angle - 180;
        } else if(angle < 45 || angle > 315) {
            angle= angle;
        }
        angle = angle* PI / 180;

        return sqrt(2 * f * f * cos(2 * angle));
    }



    double Lemniscate::radRad(double rad) const {
        if (rad <0 )
            throw std::invalid_argument("Invalid radius");
        if(rad>std::abs(sqrt(2 * f * f * cos(0))))
            throw std::invalid_argument("Invalid radius");
        return 2 * f * f /( 3 * rad);
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
        std::cout << "Enter new focus: " << std::endl;
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
        std::cout << "Formula of your lemniscate: " << std::endl;
        std::cout << Lemniscate.formula() << std::endl;

        return 1;
    }

    int dialog_getPolarDist(Lemniscate &Lemniscate) {
        std::cout << "Enter angle to calculate polar radius:" << std::endl;
        double angle;
        std::cin >> angle;
        int f = std::cin.good();
        if (f) {
            try {
                double res = Lemniscate.polarDist(angle);
                std::cout << "Polar radius is = " << res;
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
                std::cout << "Radius of curvature = " << res << std::endl;;
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
        double angle;
        std::cin >> angle;
        int f = std::cin.good();
        if (f) {
            try {
                double res = Lemniscate.radRad(angle);
                std::cout << "Radius of curvature = " << res << std::endl;;
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
        std::cout << "Enter angle to calculate the sector area: " << std::endl;
        double angle;
        std::cin >> angle;
        int f = std::cin.good();
        if (f) {
            try {
                double res = Lemniscate.sectorArea(angle);
                std::cout << "Area of sector = " << res << std::endl;;
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
        std::cout << "Area of Lemniscate" << Lemniscate.area() << std::endl;
        return 1;
    }

}

#include "lib/bigNumber.h"

using namespace Prog3a;

const char *msgs[] = {" 0. Exit",
                      " 1. Get add-code",
                      " 2. Increase by 10 times",
                      " 3. Decrease by 10 times"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*functions[])(bigDecNum &) = {nullptr,
                                    dialog_getAddCode,
                                    dialog_inc10,
                                    dialog_dec10
};


int main() {
    int f=-1;
    do{
        std::cout<<"Enter a - the first decimal number: ";
        bigDecNum first = first.InputStr();
        std::cout<<"Enter b - the second decimal number: ";
        bigDecNum second = second.InputStr();
        std::cout<<"a = ";
        first.Print();
        std::cout<<"b = ";
        second.Print();

        std::cout<<"a + b = ";
        first.Sum(second).Print();
        std::cout<<std::endl;
        std::cout<<"a - b = ";
        first.Subtraction(second).Print();
        std::cout<<std::endl;


        std::cout<<"There are some operation with the first number --->"<<std::endl;
        int rc=0;
        while ((rc = dialog(msgs, NMsgs))) {
            if (!functions[rc](first)){
                break;
            }
        }

        std::cout<<"There are some operation with the second number --->"<<std::endl;
        rc=0;
        while ((rc = dialog(msgs, NMsgs))) {
            std::cout<<std::endl;
            if (!functions[rc](second))
                break;
        }

        const char *pr ="";
        do{
            std::cout << pr << std::endl;
            std::cout << "Do you want to repeat with other numbers?(1 - Yes, 0 - No): ";
            pr = "You should enter 1 or 0. Repeat please!";
            if (getInt(f) > 0 || ((f != 1) || (f != 0))) // обнаружена ошибка ввода
                f=-1;
        } while (f < 1);

    }while (f);

    std::cout << "Goodbye!" << std::endl;

    return 0;
}

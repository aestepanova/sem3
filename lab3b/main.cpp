#include "src/bigNum.h"

using namespace Prog3b;

const char *msgs[] = {" 0. Exit",
                      " 1. Get add-code",
                      " 2. Increase by 10 times",
                      " 3. Decrease by 10 times",
                      " 4. What is the number?"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*functions[])(bigDecNum &) = {nullptr,
                                   dialog_getAddCode,
                                   dialog_inc10,
                                   dialog_dec10,
                                   dialog_print,
};


int main() {
    bigDecNum first, second;
    int go=1;
    while (go) {
        std::cout << "Enter a - the first decimal number: ";
        try {
            std::cin>>first;
        }
        catch (const std::exception &msg) {
            std::cout << msg.what() << std::endl;
        }

        std::cout << "Enter b - the second decimal number: ";
        try {
            std::cin>>second;
        }
        catch (const std::exception &msg) {
            std::cout << msg.what() << std::endl;
        }

        std::cout << "a = " << first << std::endl;
        std::cout << "b = " << second << std::endl;

        std::cout << "a + b = " << first+second << std::endl;
        std::cout << "a - b = " << first-second << std::endl;


        std::cout << "There are some operation with the first number --->" << std::endl;
        int rc = 0;
        while ((rc = dialog(msgs, NMsgs))) {
            if (!functions[rc](first)) {
                break;
            }
        }

        std::cout << "There are some operation with the second number --->" << std::endl;
        rc = 0;
        while ((rc = dialog(msgs, NMsgs))) {
            std::cout << std::endl;
            if (!functions[rc](second))
                break;
        }
        std::cout << "Enter 0 to exit or 1 to continue: ";
        std::cin >> go;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Goodbye!" << std::endl;

    return 0;
}

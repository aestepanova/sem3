#include "lib/bigNum_char.h"

using namespace Prog3a_char;

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
    std::cout<<"Enter a - the first decimal number: ";
    try{
        first = first.InputStr();
    }
    catch(const std::exception &msg){
        std::cout << msg.what() << std::endl;
    }

    std::cout<<"Enter b - the second decimal number: ";
    try{
        second = second.InputStr();
    }
    catch(const std::exception &msg){
        std::cout << msg.what() << std::endl;
    }

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

    std::cout << "Goodbye!" << std::endl;

    return 0;
}

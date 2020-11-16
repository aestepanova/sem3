#include "src/bigNum.cpp"

using namespace Prog3c;

int main() {
    bigNum first, second;
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

        try{
            std::cout << "a + b = " << first+second << std::endl;
            std::cout << "a - b = " << first-second << std::endl;
            std::cout << "b - a = " << second-first << std::endl;
        }
        catch (const std::exception &msg) {
            std::cout << msg.what() << std::endl;
        }

        std::cout << std::endl;

        try{
            std::cout << "a = " << first << std::endl;
            std::cout << "Add code for number a: " << (~first) << std::endl;
            std::cout << "Increase number a by 10 times: " << (first<<=1) << std::endl;
            std::cout << "Decrease number a by 10 times: " << (first>>=2) << std::endl;
        }
        catch (const std::exception &msg) {
            std::cout << msg.what() << std::endl;
        }

        std::cout << std::endl;

        try{
            std::cout << "b = " << second << std::endl;
            std::cout << "Add code for number b: " << (~second) << std::endl;
            std::cout << "Increase number b by 10 times: " << (second<<=1) << std::endl;
            std::cout << "Decrease number b by 10 times: " << (second>>=2) << std::endl;
        }
        catch (const std::exception &msg) {
            std::cout << msg.what() << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Enter 0 to exit or 1 to continue: ";
        std::cin >> go;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Goodbye!" << std::endl;

    return 0;
}

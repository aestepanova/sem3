#include <cstdio>
#include <iostream>
#include "src\HexNumber.h"
#include "src\Stack.h"
#include <string>

using namespace H16_3;
using namespace Stack1;

int main() {
    class Stack s(3);
    std::string str,x;
    std::cout << "\n\t\t----This is console calculator program with reverse polish notation----"<<std::endl;
    std::cout << "\t\tFor using this program enter numbers and operators with this rules:" << std::endl
    << "\t\t1. Enter spaces after numbers and operators " <<std::endl<< "\t\t2. To get negative number use - before number without space" <<std::endl <<"\t\t3. Enter only number with 32 digits and less "<<std::endl<<"\t\t4. Enter @ to exit"<<std::endl<<"\t\t5. Use only operators from list:" << std::endl;
    std::cout << "\t\t   1. '+' - to sum" << std::endl << "\t\t   2. '^' - to substracting" << std::endl << "\t\t   3. '*' - to increase number by one digit" << std::endl << "\t\t   4. '/' - to decrease number by one digit" <<std::endl<< "\t\t   5. '=' - to get result"<<std::endl;
    std::cout << "\t\t----------------------Let's start calculations!------------------------" << std::endl;
    int f = 1;
    while (f) {
        std::getline(std::cin, x);
        int i = 0;
        int flag = 0;
        for (char& c : x) {
            if ((c >= '0' && c <= '9') || (c >= 'A' && c<= 'F') || c=='-') {
                str.append(x, i, 1);
                flag = 1;
            }
            i++;
            switch (c) {
                case EOF: break;
                case '\n':
                case ' ': {
                    if (flag == 1) {
                        flag = -1;
                        break;
                    }
                    else break;
                }
                case '=': {std::cout << "result:"; s.printStack(); break; }
                case '+': {
                    try {
                        s.push1((s.pop())+(s.pop()));
                    }
                    catch (const std::exception& msg) {
                        std::cout << msg.what() << std::endl;
                    }
                    break; }
                case '^': {
                    try {
                        Hex a = s.pop();
                        Hex b = s.pop();
                        std::cout<<a << "\t" << b;
                        s.push1(a - b);
                    }
                    catch (const std::exception& msg) {
                        std::cout << msg.what() << std::endl;
                    }
                    break; }
                case '*': {
                    try {
                        s.push1(s.pop()<<=(1));
                    }
                    catch (const std::exception& msg) {
                        std::cout << msg.what() << std::endl;
                    }
                    break;
                }
                case '/': s.push1(s.pop()>>=(1)); break;
                default: break;
            }
            if (flag == -1) {
                s.push(str.c_str());
                str.clear();
                flag = 0;
            }
            if (c == '@') {
                f = 0;
                break;
            }
        }
        x.clear();
    }
    std::cout <<"Have a nice day! Goodbye! :)";
    return 0;
}
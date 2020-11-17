#include <cstdio>
#include <malloc.h>
#include <iostream>
#include "src\HexNumber.h"
#include "src\Stack.h"
#include <string>

using namespace Prog3;
using namespace Stack1;

int main() {
    class Stack s(3);
    std::string str,x;
    std::cout << "\n"<< "\t\t----This is console calculator program with reverse polish notation----"<<std::endl;
    std::cout << "\t\tFor using this program enter numbers and operators with this rules:" << std::endl << "\t\t1. Enter spaces after numbers and operators " <<std::endl<< "\t\t2. To get negative number use - before number without space" <<std::endl <<"\t\t3. Enter only number with 47 digits and less "<<std::endl<<"\t\t4. Enter Ctrl+Z to exit"<<std::endl<<"\t\t5. Use only operators from list:" << std::endl;
    std::cout << "\t\t   1. '+' - to sum" << std::endl << "\t\t   2. '^' - to substracting" << std::endl << "\t\t   3. '*' - to increase number by one digit" << std::endl << "\t\t   4. '/' - to decrease number by one digit" <<std::endl<< "\t\t   5. '=' - to get result"<<std::endl;
    std::cout << "\t\t----------------------Let's start calculations!------------------------" << std::endl;
    while (!feof(stdin)) {
        std::getline(std::cin, x);
        int i = 0;
        int flag = 0;
        for (char& c : x) {
            if (c >= '0' && c <= '9' || c=='-') {
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
                case '=': {std::cout << "result:"; s.PrinstStack(); break; }
                case '+': {
                    try {
                        s.push1(s.pop().Add(s.pop()));
                    }
                    catch (const std::exception& msg) {
                        std::cout << msg.what() << std::endl;
                    }
                    break; }
                case '^': {
                    try {
                        s.push1(s.pop().Sub(s.pop()));
                    }
                    catch (const std::exception& msg) {
                        std::cout << msg.what() << std::endl;
                    }
                    break; }
//                case '*': {
//                    try {
//                        s.push1(s.pop().Inc10());
//                    }
//                    catch (const std::exception& msg) {
//                        std::cout << msg.what() << std::endl;
//                    }
//                    break;
//                }
//                case '/': s.push1(s.pop().Dec10()); break;
                default: break;
            }
            if (flag == -1) {
                s.push(str.c_str());
                str.clear();
                flag = 0;
            }
        }
        x.clear();
    }
    return 0;
}
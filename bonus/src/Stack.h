#pragma once
#include <cstdio>
#include <malloc.h>
#include <iostream>
#include "HexNumber.h"

namespace Stack1 {
    using namespace Prog3;
    class Stack {
        HexNumber* number;
        int SZ;
        int ptr;
    public:
        Stack(int size) {
            SZ = size;
            number = (HexNumber*)malloc(SZ * sizeof(HexNumber));
            ptr = 0;
        };
        ~Stack() {
            free(number);
        };
        HexNumber pop(void) {
            if (ptr)
                return number[--ptr];
            else {
                HexNumber a;
                return a;
            }
        };
        void push(const char* str) {
            if (ptr >= SZ - 1) {
                SZ++;
                number = (HexNumber*)realloc(number, SZ * sizeof(HexNumber));
            }
            try {
                number[ptr++].setN(str);
            }
            catch (const std::exception& msg) {

                std::cout << msg.what() << std::endl;
            }
        };
        void push1(HexNumber x) {
            if (ptr >= SZ - 1) {
                SZ++;
                number = (HexNumber*)realloc(number, SZ * sizeof(HexNumber));
            }
            number[ptr++] = x;
        };
        int empty() {
            return (ptr == 0);
        }
        int PrinstStack() {
            std::cout << number;
            return 0;
        }
    };
}
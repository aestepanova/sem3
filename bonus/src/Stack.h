#pragma once
#include <cstdio>
#include <malloc.h>
#include <iostream>
#include <cstring>
#include "HexNumber.h"

namespace Stack1 {
    using namespace H16_3;
    class Stack {
        Hex* number;
        int SZ;
        int ptr;
    public:
        Stack(int size) {
            SZ = size;
            number = (Hex*)malloc(SZ * sizeof(Hex));
            ptr = 0;
        };
        ~Stack() {
            free(number);
        };
        Hex pop(void) {
            if (ptr){
                return number[--ptr];}
            else {
                Hex a;
                return a;
            }
        };
        void push(const char* str) {
            if (ptr >= SZ - 1) {
                SZ++;
                number = (Hex*)realloc(number, SZ * sizeof(Hex));
            }
            try {
                number[ptr++] = Hex(str, strlen(str));
            }
            catch (const std::exception& msg) {

                std::cout << msg.what() << std::endl;
            }
        };
        void push1(Hex x) {
            if (ptr >= SZ - 1) {
                SZ++;
                number = (Hex*)realloc(number, SZ * sizeof(Hex));
            }
            number[ptr++] = x;
        };

        int printStack() {
            std::cout << *number;
            return 0;
        }

    };
}
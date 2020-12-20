#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "Suite.h"
#include <vector>

namespace lab4{
        /// элемент таблицы ///

    struct Item {
        int code;
        Suite* suite;
        Item* next;
    };

       /// таблица ///

    class Table {
    private:
        static const int maxsize = MAX_SIZE;
        vector<Item*> el;

        int hash(int key)
        {
            return (key % maxsize);
        }
    public:
        Table() {
            el.resize(maxsize);
            for (int i = 0; i < maxsize; i++) el[i] = nullptr;
        }

        int add(int code, Suite* suite);
        int del(int code, int num);
        Item* find(int code, int num);
        void show();
    };
}




#endif //LAB4_TABLE_H

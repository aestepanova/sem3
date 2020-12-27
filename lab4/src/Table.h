#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "Suite.h"
#include "Unary.h"
#include "Luxe.h"
#include "Multi.h"
#include <vector>

namespace lab4 {

    class Table {
    private:
        vector<Suite *> el;

    public:
        Table()= default;;

        void add(Suite *suite){
            el.push_back(static_cast<Suite*>(suite));
        }

        Suite *find(int& num){
            if (!(el.empty())){
                std::vector<Suite*>::iterator it;
                for(it = el.begin(); it < el.end(); it++) {
                    if (num == (*(*it)).getNumber()) {
                        return *it;
                    }
                }
                cout << "There is no such number!\n";
            }else{
                cout << "Table is empty\n";
            }
            return nullptr;
        };
        int find_num(int& num){
            if (!(el.empty())){
                std::vector<Suite*>::iterator it;
                for(it = el.begin(); it < el.end(); it++) {
                    if (num == (*(*it)).getNumber()) {
                        return 1;
                    }
                }
            }
            return 0;
        }

        void del(int &num) {
            if (find(num)) {
                std::vector<Suite *>::iterator it;
                for (it = el.begin(); it < el.end(); it++) {
                    if (num == (*(*it)).getNumber()) {
                        (*(*it)).unregisterG();
                        el.erase(it);
                    }
                }
            }
        }

        void show(){
            if (!(el.empty())){
                for (int i = 0; i < this->el.size(); i++) {
                    el[i]->showInfo();
                    cout<< "\n------------------------------\n";
                }
            }else{
                cout << "Table is empty\n";
            }
        };
    };

    inline int getInt(int &n) { //for natural int
        std::cin >> n;
        if (!std::cin.good())    // обнаружена ошибка ввода или конец файла
            return -1;
        if (n >= std::numeric_limits<int>::max()) return -2;
        if (n < 0) return 0;
        return 1;
    }

    int dialog_add(lab4::Table &Tab) {
        Suite *s = nullptr;
        int t=0;
        cout << "What type of suite do you want?"<<endl;
        cout << "1. Unary\n2. Luxe\n3. Multi" << endl;
        getInt(t);
        switch (t) {
            case 1:
                try{
                    s = new Unary();
                    s->setType("Unary");
                    s->registerG();
                    s->setBusy(1);
                    s->setNumGuests(1);
                    cout << "What number do you want?\n";
                    int a;
                    getInt(a);
                    if (!Tab.find_num(a)){
                        s->setNumber(a);
                    }else{
                        cout << "This number is busy. Try again\n";
                    }

                }
                catch (...){};
                break;
            case 2:
                try{
                    s = new Luxe();
                    s->setType("Luxe");
                    s->registerG();
                    s->setBusy(1);
                }
                catch (...){}
                break;
            case 3:
                s = new Multi();
                s->setType("Multi");
                break;
            default:
                break;
        }
        Tab.add(s);
        return 1;
    }

    int dialog_del(lab4::Table &Tab) {
        int num;
        cout << "Enter your number of suite ---> " << endl;
        getInt(num);
        Tab.del(num);

        return 1;
    }

    int dialog_find(lab4::Table &Tab) {
        int num;
        cout << "Enter your number of suite ---> " << endl;
        getInt(num);
        Tab.find(num)->showInfo();
        return 1;
    }

    int dialog_show(lab4::Table &Tab) {
        Tab.show();
        return 1;
    }


    inline int dialog(const char *msgs[], int N) {
        std::string errmsg;
        int rc, n;
        do {
            std::cout << errmsg;
            errmsg = "You are wrong. Repeat, please\n";
            for (int j = 0; j < N; ++j)
                puts(msgs[j]);
            puts("Make your choice: --> ");

            n = getInt(rc);
            if (n == 0)
                rc = 0;
        } while (rc < 0 || rc >= N);
        return rc;
    }
}
#endif //LAB4_TABLE_H

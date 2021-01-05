#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "Suite.h"
#include "Unary.h"
#include "Luxe.h"
#include "Multi.h"
#include <vector>

#define LINE "-------------------"
#define UNARY 1
#define LUXE 1
#define MULTI 2
// номера от 1 до 15 - одноместные, от 16 до 26 - люксы, 27-37 многоместные

namespace lab4 {

    class Table {
    private:
        vector<Suite *> el;

    public:
        Table()= default;
        int h(int k, int i) { return (k % (UNARY + LUXE + MULTI) + i); };
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
                        if ((*(*it)).getType() != "Multi") el.erase(it); // delete unary or luxe
                        if ((*(*it)).isFree() == 1) el.erase(it); // delete free multi
                    }
                }
            }
        }

        void show(){
            cout << endl << LINE << endl;
            if (!(el.empty())){
                for (int i = 0; i < this->el.size(); i++) {
                    el[i]->showInfo();
                    cout<< endl << LINE << endl;
                }
                cout << "There are " << UNARY+LUXE+MULTI - el.size() << " free suites!\n" << LINE << endl;
            }else{
                cout << "There are " << UNARY+LUXE+MULTI << " free suites!\n" << LINE << endl;
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
        Suite *s = nullptr, *tmp;
        int t=0, f, flag=0;
        cout << "What type of suite do you want?"<<endl;
        cout << "1. Unary\n2. Luxe\n3. Multi" << endl;
        getInt(t);
        int i = 0, k = 0, j = 0;
        switch (t) {
            case 1:
                s = new Unary();
                t = UNARY + 1;
                do {
                    j = Tab.h(k, i) + 1;
                    f = Tab.find_num(j);
                    if (f) i++;
                    if (!t){
                        cout << "There are no free unary suites.\n";
                        flag = 1;
                        break;
                    }
                    t -= 1;
                } while ((f)||(t==0));
                if (t){
                    s->setNumber(j);
                    s->setType("Unary");
                    s->registerG();
                    s->setBusy(1);
                    s->setNumGuests(1);
                }
                break;
            case 2:
                s = new Luxe();
                t = LUXE;
                do {
                    j = Tab.h(k, i)+ 1 + UNARY;
                    f = Tab.find_num(j);
                    if (f) i++;
                    t -= 1;
                } while ((f)||(t==0));
                if (!t){
                    cout << "There are no free luxe suites.\n";
                    flag = 1;
                    break;
                }else{
                    s->setNumber(j);
                    s->setType("Luxe");
                    s->registerG();
                    s->setBusy(1);
                }
                break;
            case 3:
                s = new Multi();
                t = MULTI;
                do {
                    j = Tab.h(k, i)+ 1 + UNARY + LUXE;
                    f = Tab.find_num(j);
                    if (f){
                        tmp = Tab.find(j);
                        if ((tmp->getNumGuests()<4)){
                            tmp->registerG();
                            flag = 1;
                            break;
                        }
                        i++;
                    }
                    t -= 1;
                } while ((f)||(t==0));
                if (t == 0){
                    cout << "There are no place in Multi suites. You can choose Unary or Luxe.\n";
                    break;
                }
                if (!flag){
                    s->setNumber(j);
                    s->setType("Multi");
                    s->registerG();
                    s->setBusy(1);
                }
                break;
            default:
                break;
        }
        if (!flag) {
            Tab.add(s);
            return 1;
        }else return 2;
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
        cout << endl << LINE << endl;
        Suite* s;
        s = Tab.find(num);
        if (s){
            s->showInfo();
        }
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

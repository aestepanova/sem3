#ifndef LAB4_TABLE_H
#define LAB4_TABLE_H

#include "Suite.h"
#include "Unary.h"
#include "Luxe.h"
#include "Multi.h"
#include "my_vec.h"

#define LINE "-------------------"
#define UNARY 1
#define LUXE 1
#define MULTI 1
// номера от 1 до 15 - одноместные, от 16 до 26 - люксы, 27-37 многоместные

namespace lab4 {

    /// Содержит в себе информацию обо всех номерах гостиницы (использует свой контейнерный класс "my_vec")
    class Table {
    private:
        my_vec<Suite *> el; ///< Краткое описание

    public:
        Table(): el(){};
        int h(int k, int i) { return (k % (UNARY + LUXE + MULTI) + i); };

        void add(Suite *suite){

            el.push_back(suite);

        }

        /*!
        Поиск гостиничного номера по его номеру
        \param num Конкретный номер гостиничного номера
        \return Указатель на найденный гостиничный номер
*/

        Suite *find(int& num){
            if (!(el.empty())){
                my_vec<Suite*>::iterator it;
                for(it = el.begin(); it < el.end(); it++) {
                    if (num == (*(*it)).getNumber()) {
                        return *it;
                    }
                }
                cout << "There is no such number!\n\n";
            }else{
                cout << "Table is empty\n";
            }
            return nullptr;
        };

        /*!
        Поиск гостиничного номера по его номеру
        \param num Конкретный номер гостиничного номера
        \return 1 - если номер есть в таблице, 0 - если отсутствует
*/
        int find_num(int& num){
            if (!(el.empty())){
                my_vec<Suite*>::iterator it;
                for(it = el.begin(); it < el.end(); it++) {
                    if (num == (*(*it)).getNumber()) {
                        return 1;
                    }
                }
            }
            return 0;
        }

        /*!
        Выдаёт информацию о занятости гостиницы
        \param tab Таблица, содержащая информацию обо всех номерах в гостинице

*/
        void freeSuits(Table& tab){
            int u = UNARY, l = LUXE, m = MULTI;
            if (!(el.empty())){
                my_vec<Suite*>::iterator it;
                for(it = el.begin(); it < el.end(); it++) {
                    if ((*(*it)).getType() == "Unary"){
                        u--;
                    }
                    else if ((*(*it)).getType() == "Luxe"){
                        l--;
                    }
                    else if ((*(*it)).getType() == "Multi"){
                        m--;
                    }
                }
                cout << "\tWe have " << u + l + m <<" vacant suits:\nUnary: " << u << "\nLuxe: " << l << "\nMulti: " << m << endl;
            }else{
                cout << "Hotel is empty. We have " << UNARY + LUXE + MULTI << " vacant suits!\n";
            }
            if ((u+l+m)==0){
                cout<< "You could try taking a seat in a multi-seat nome\n";
            }

        }

        /*!
        Удаление гостиничного номера по его номеру
        \param num Конкретный номер гостиничного номера
*/
        void del(int &num) {
            if (find(num)) {
                my_vec<Suite *>::iterator it;
                for (it = el.begin(); it < el.end(); it++) {
                    if (num == (*(*it)).getNumber()) {
                        (*(*it)).unregisterG();
                        if ((*(*it)).getType() != "Multi") el.erase(it); // delete unary or luxe
                        if ((*(*it)).isFree() == 1) el.erase(it); // delete free multi
                    }
                }
            }
        }

        /*!
        Показ полной таблицы
      */
        void show(){
            cout << endl << LINE << endl;
            if (!(el.empty())){
                for (int i = 0; i < this->el.size(); i++) {
                    el[i]->showInfo();
                    cout<< endl << LINE << endl;
                }
            }
        };
    };

    /*!
        Получение натурального числа
        \param n Число
        \return -1, если обнаружена ошибка ввода или конец файла;
        -2, если введенное число больше максимального Int;
        0, если введено отрицательное число, 1, если всё в порядке
*/
    inline int getInt(int &n) { //for natural int
        std::cin >> n;
        if (!std::cin.good()) {  // обнаружена ошибка ввода или конец файла
            cin.ignore(32767, '\n');
            return -1;
        }
        if (n >= std::numeric_limits<int>::max()) return -2;
        if (n < 0) return 0;
        return 1;
    }

    /*!
        Регистрация гостя
        \param tab Таблица, содержащая информацию обо всех номерах в гостинице
        \return 1, если добавлен новый гостиничный номер в таблицу;
        2, если изменено состояние существующего в таблице гостиничного номера
*/
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
                    t -= 1;
                } while ((f)&&(t!=0));
                if (!t){
                    cout << "There are no free unary suites.\n";
                    flag = 1;
                    break;
                }
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
                t = LUXE + 1;
                do {
                    j = Tab.h(k, i)+ 1 + UNARY;
                    f = Tab.find_num(j);
                    if (f) i++;
                    t -= 1;
                } while ((f)&&(t!=0));
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
                t = MULTI + 1;
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
                } while ((f)&&(t!=0));
                if (t == 0){
                    cout << "There are no place in Multi suites. You can choose Unary or Luxe.\n";
                    flag = 1;
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

    /*!
        Диалог освобождения номера гостем
        \param tab Таблица, содержащая информацию обо всех номерах в гостинице
        \return 1
*/
    int dialog_del(lab4::Table &Tab) {
        int num;
        cout << "Enter your number of suite ---> " << endl;
        if (getInt(num)==1){
            Tab.del(num);
        }else{
            cin.ignore(32767, '\n');
            cout << "Wrong number!\n";
        }
        return 1;
    }

    /*!
        Показывает инфомрацию о номере
        \param tab Таблица, содержащая информацию обо всех номерах в гостинице
        \return 1
*/
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

    /*!
        Диалог показа таблицы
        \param tab Таблица, содержащая информацию обо всех номерах в гостинице
        \return 1
*/
    int dialog_show(lab4::Table &Tab) {
        Tab.show();
        return 1;
    }

    /*!
        Диалог показа заполенности гостиницы
        \param tab Таблица, содержащая информацию обо всех номерах в гостинице
        \return 1
*/
    int dialog_suits(lab4::Table &Tab){
        Tab.freeSuits(Tab);
        return 1;
    }


    /*!
        Организация диалога с пользователем
        \param msgs Массив предлагаемых опций для пользователя
        \param N Количество опций
        \return Номер выбранной функции
*/
    inline int dialog(const char *msgs[], int N) {
        std::string errmsg;
        int rc, n;
        do {
            std::cout << errmsg;
            errmsg = "You are wrong. Repeat, please\n\n";
            cout << ">>>" << LINE << LINE << endl;
            for (int j = 0; j < N; ++j)
                puts(msgs[j]);
            puts("Make your choice: --> ");
            n = getInt(rc);
            if (n == 0)
                rc = 0;
            cout << LINE << LINE << "<<<" << endl;
        } while (rc < 0 || rc >= N);
        return rc;
    }
}
#endif //LAB4_TABLE_H

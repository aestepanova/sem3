#include <iostream>
#include "prog1.h"

namespace prog1 {

    Matrix *input() {
        int lines, columns;
        std::cout << "Enter number of rows -->";
        getNaturalInt(&lines);
        std::cout << "Enter number of columns -->";
        getNaturalInt(&columns);
        auto *matrix = new Matrix;
        matrix->N = lines;
        matrix->M = columns;
        matrix->rows = new MatrixElement *[lines];
        for (int i = 0; i < matrix->N; i++) {
            matrix->rows[i] = nullptr;
        }
        int choice;
        bool check = true;
        while (check) {
            std::cout << "Do you want to input next element (1 - Yes, 0 - No)?" << std::endl;
            std::cin >> choice;
            if (choice) {
                int x, y;
                float value;
                std::cout << "Input number of line in range [" << 1 << ";" << lines << "]" << std::endl;
                getNaturalInt(&x, &lines);
                std::cout << "Input number of column in range [" << 1 << ";" << columns << "]" << std::endl;
                getNaturalInt(&y, &columns);
                std::cout << "Input value of element -->";
                getFloat(&value);
                x--;
                y--;
                addElement(matrix, x, y, value);//увеличиваем количество ненулевых тут
            }
            if (!choice) {
                check = false;
            }
        }
        return matrix;
    }

    void addElement(Matrix *matrix, int x, int y, float value) {
        /* случаи: создаем новую строку-значит,надо создать новый список
         * добавляем новый элемент:находим нужный элемент массива, а там вставка в список.
         */
        auto *elem = new MatrixElement(x,y,value,nullptr);//выделяем память под новый элемент списка

        //первый элемент в строке матрицы или же [y] вставляемого элемента меньше [y] первого элемента
        if (matrix->rows[x] == nullptr || elem->y < matrix->rows[x]->y) {
            elem->next = matrix->rows[x];
            matrix->rows[x] = elem;
            return;
        }
        //ищем нужную позицию, при этом может оказаться , что нужная позиция не занимает
        // промежуточное место в списке, двигать ничего не нужно, просто ставим после
        // ячейка уже занята-делаем запрос, менять ли
        // нужна позиция занимает промежуточное положение в списке-"отодвигаем" хвост списка
        if (matrix->rows[x] != nullptr && matrix->rows[x]->y == elem->y) {//делаем замену
            if (Choice(x, y)) {
                matrix->rows[x]->value = value;
                return;
            } else
                return;
        }

        MatrixElement *prev, *curr;
        prev = matrix->rows[x];
        curr = matrix->rows[x]->next;

        while (curr && elem->y > curr->y) {
            prev = prev->next;
            curr = curr->next;
        }
        if (curr != nullptr && curr->y == elem->y) {
            if (Choice(x, y)) {
                curr->value = elem->value;
                return;
            } else
                return;
        }
        prev->next = elem;
        elem->next = curr;
    }
/// Создать вектор b. i-тый элемент вектора равен сумме тех элементов i-той строки матрицы,
/// которые превышают соответсвующий элемент предыдущей строки (i-1)-той.
/// Для первой строки использовать последнюю в качестве предыдущей.

    float * createVector(Matrix* matrix){
        auto *b = new float[matrix->N](); //N - количество строк
        //заполнение для первой строки
        //подается 2 строки текущая и предыдущая
        *(b)=formVectorItem(matrix->rows[0], matrix->rows[(matrix->N)-1]);
        // заполнение вектора для остальных строк
        for (int k = 1; k <matrix->N; k++) {
            *(b+k)=formVectorItem(matrix->rows[k], matrix->rows[k-1]);
        }
        return b;
    }

    float formVectorItem(struct MatrixElement *cur, struct MatrixElement *pred){
        //сумма тех элементов строки, которые больше элемента c таким же индексом в предыдущей строке
        MatrixElement *row1 = cur;
        MatrixElement *row0 = pred;
        float sum = 0;
        if (!row1){
            return 0; //возвращает 0, если текущая строка пустая
        }
        if (!row0){
            sum = sumOfRow(row1); //если предыдущий ряд заполнен нулями
        } else {
            while(row1) {
                while ((row1)&&(row0)) {
                    if ((row1->y) == (row0->y)) {
                        if ((row1->value) > (row0->value)) {
                            sum += row1->value;
                            row0 = row0->next;
                            row1 = row1->next;
                        }
                    } else if (row1->y < row0->y) {
                        //если индекс текущей меньше номера предыдущей, то продвигаем дальше
                        sum+=row1->value;
                        row1 = row1->next;
                    } else {
                        //если индекс текущей больше номера предыдущей, то двигаем предыдущий список
                        row0=row0->next;
                    }
                }
                //если цикл прекратился из-за того, что закончились ненулевые элементы в предыдущей строке, то
                // добавляем оставшие элементы к имеющейся сумме
                while (row1) {
                    sum += row1->value;
                    row1 = row1->next;
                }
            }
        }

        return sum;
    }
    void outputVector(float * vec, int size){
        float *ptr= vec;
        int N = size;
        printf("\nIt's vector: \n");
        for (int i = 0; i < N; i++) {
            printf("b[%d]=%5.3f  ", i, *(ptr++));
        }
        printf("\n");
    }
    ///

   float sumOfRow(MatrixElement *elem) {
        float sum = 0;
        MatrixElement *ptr = elem;
        while (ptr) {
            sum += ptr->value;
            ptr = ptr->next;
        }
        return sum;
    }

    int Choice(int x, int y) {
        int choice;
        std::cout << "Do you want to change element in position[" << x + 1 << ";" << y + 1
                  << "]? Yes - 1, No - 0" << std::endl;
        std::cin >> choice;
        return choice;
    }

    void output(const char *msg, Matrix *matrix) {
        std::cout << "\n" << "Matrix's elements are printed in format :[x,y,value]" << std::endl;
        std::cout << msg << std::endl;
        for (int i = 0; i < matrix->N; i++) {
            std::cout << "\n";
            if (matrix->rows[i] != nullptr) {
                MatrixElement *ptr;
                ptr = matrix->rows[i];
                while (ptr) {
                    std::cout << " [" << ptr->x + 1 << ";" << ptr->y + 1 << ";" << ptr->value << "] ";
                    ptr = ptr->next;
                }
            }
        }
    }

    int getFloat(float *a){
        int n;
        do {
            n = scanf("%f", a);
            if (n < 0)
                return 0;
            if (n == 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0);
        return 1;
    }

    int getInt(int *a) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (n == 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0);
        return 1;
    }

    int getNaturalInt(int *a) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (n == 0 || *a < 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0 || *a < 0);
        return 1;
    }

    int getNaturalInt(int *a, const int *max) {//ввод с верхней границей
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0)
                return 0;
            if (*a > *max) {
                printf("%s\n", "Error!You exceeded the limit!Repeat input: ");
                scanf("%*[^\n]");
            }
            if (n == 0 || *a < 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0 || *a < 0 || *a > *max);
        return 1;
    }

    Matrix *erase(Matrix *matrix) {
        auto *ptr = new MatrixElement;
        for (int i = 0; i < matrix->N; i++) {
            ptr = matrix->rows[i];
            while (ptr != nullptr) {
                MatrixElement *trash;
                trash = ptr;
                ptr = ptr->next;
                delete trash;
            }
        }
        delete matrix->rows;
        return nullptr;
    }
}



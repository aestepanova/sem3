//
// Created by mi on 19.09.2020.
//
#include <iostream>

namespace prog1 {

    struct MatrixElement {
        int x;//номер в строке
        int y;//номер в столбце
        float value;//значение элемента матрицы
        struct MatrixElement *next;//следующий элемент списка

        MatrixElement() : x(-1), y(-1), value(0), next(nullptr){}

        MatrixElement(int x, int y, float value, MatrixElement *next) : x(x), y(y), value(value), next(next){}
    };

    struct Matrix {
        int N;//количество строк в матрице
        int M;//количество столбцов
        struct MatrixElement **rows;//массив, содержащий указатели на первые элементы строк матрицы
    };

    float sumOfRow(MatrixElement *elem);
    float * createVector(Matrix* matrix);
    float formVectorItem(struct MatrixElement *row1, struct MatrixElement *row0);
    void outputVector(float *, int size);

    void addElement(Matrix *matrix, int x, int y, float value);
    Matrix *input();
    void output(const char *msg, Matrix *matrix);
    int Choice(int, int);
    Matrix *erase(Matrix *matrix);

    int getInt(int *a);
    int getNaturalInt(int *a);
    int getNaturalInt(int *a, const int *max);
    int getFloat(float *a);
}


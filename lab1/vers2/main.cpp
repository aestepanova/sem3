//
// Created by mi on 19.09.2020.
//

#include "prog1.h"

using namespace prog1;

int main() {
    Matrix *matrix;
    matrix = input();
    output("Sourced matrix", matrix);
    float* vector;
    vector = createVector(matrix);
    outputVector(vector, (matrix->N));
    erase(matrix);
    delete [] vector;
    return 0;
}

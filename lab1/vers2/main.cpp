//
// Created by mi on 19.09.2020.
//

#include <iostream>
#include "prog1.h"

using namespace prog1;

int main() {
    auto *matrix = new Matrix;
    matrix = input();
    output("Sourced matrix", matrix);
    float* vector;
    vector = createVector(matrix);

    //sort(matrix);
    output("New matrix", matrix);
    erase(matrix);
    outputVector(vector, &(matrix->N));
   // deleteVector(vector);
    return 0;
}

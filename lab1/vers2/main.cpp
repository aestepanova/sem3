#include "prog1.h"

using namespace prog1;

int main() {
    Matrix *matrix;
    matrix = input();
    if (!matrix){
        std::cout<< "ERROR" << std::endl;
        return -1;
    }
    output("Sourced matrix", matrix);
    float* vector;
    vector = createVector(matrix);
    if (!vector){
        std::cout<< "ERROR" << std::endl;
        return -2;
    }
    outputVector(vector, (matrix->N));
    erase(matrix);
    delete [] vector;
    return 0;
}

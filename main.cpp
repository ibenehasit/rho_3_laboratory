#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "matrix.hpp"

int main() {
    //test for empty matrix 
    Matrix matrix1(6, 7);
    std::cout << "This is a " << matrix1.getRow() << "x" << matrix1.getCol() << " matrix\n";
    matrix1.print();
    
    //test for matrix multiplication
    Matrix matrix2(7, 3);
    Matrix result1 = matrix1 * matrix2;
    std::cout << "\nMultiplication result is a " << result1.getRow() << "x" << result1.getCol() << " matrix\n";
    result1.print();
    

    //test for matrix-scalar multiplication    
    Matrix result2 = matrix1 * 5;
    std::cout << "\nScalar multiplication result is a " << result2.getRow() << "x" << result2.getCol() << " matrix\n";
    result2.print();
    
    //test for matrix addition
    Matrix matrix3(6,7);
    std::cout << "\nAddition result is a " << matrix3.getRow() << "x" << matrix3.getCol() << " matrix\n";
    Matrix result3 = matrix1 + matrix3;
    result3.print();
    

    //printing a given-value matrix
    Matrix matrixFilled1({{1, 2, 3, 4},
                         {5, 6, 7, 8}});

    std::cout << "This is a " << matrixFilled1.getRow() << "x" << matrixFilled1.getCol() << " matrix\n";
    matrixFilled1.print();

    //testing creating a random matrix
    Matrix matrixRandom1(6, 7, true);
    std::cout << "This is a " << matrixRandom1.getRow() << "x" << matrixRandom1.getCol() << " matrix\n";
    matrixRandom1.print();

    Matrix matrixRandom2(7, 6, true);
    Matrix result4 = matrixRandom1 * matrixRandom2;
    std::cout << "\nlet's see if this works lmao\n";
    result4.print();
    
    return 0;
}
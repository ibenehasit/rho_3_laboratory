#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "matrix.hpp"

using std::vector;

// IMPLEMENT METHODS USING Matrix:: SCOPE RESOLUTION

//initialise an empty matrix
Matrix::Matrix(int row, int col){
    Row = row;
    Col = col;

    data.resize(Row); 
    for (int i = 0; i < Row; i++) {
        data[i].resize(Col, 0.0); 
    }
}

//initialise a matrix with given values
Matrix::Matrix(vector<vector<double>> d){
    data = d; // copy the input data
    Row = d.size(); //the number of rows = outer vector size
    if (Row > 0) {
        Col = d[0].size(); //Number of colums = first inner vector size
    } else {
        Col = 0;
    }
}

//initialise a matrix with random values
Matrix::Matrix(int row, int col, bool isRandom) {
    Row = row;
    Col = col;
    data.resize(Row);
    for (int i = 0; i < Row; i++){
        data[i].resize(Col);
    }
    if (isRandom){
        srand(time(0));
        for (int i = 0; i < Row; i++){
            for (int j = 0; j < Col; j++) {
                data[i][j] = (double)rand() / RAND_MAX;
            }   
        }
    } else {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                data [i][j] = 0.0f;
            }
        }
    }
}

//Matrix-matrix multiplication overload
Matrix Matrix::operator*(const Matrix& other) const {
    if (Col != other.Row) {
        std::cerr << "Matrix dimensions incompatible for multiplication\n";
        return Matrix(0, 0);
    }

    Matrix result(Row, other.Col);
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < other.Col; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < Col; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

//Scalar-Matrix multiplication overload
Matrix Matrix::operator*(double scalar) const {
    Matrix result(Row, Col);
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

//Matrix-Matrix addition overload 
Matrix Matrix::operator+(const Matrix& other) const {
    if (Row != other.Row || Col != other.Col) {
        std::cerr << "Error: Matrices must have same dimensions for addition\n";
        return Matrix(0, 0);
    }

    Matrix result(Row, Col);

    for(int i = 0; i < Row; i++){
        for (int j = 0; j < Col; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

//Matrix-Matrix subtraction overload
Matrix Matrix::operator-(const Matrix& other) const {
    if (Row != other.Row || Col != other.Col) {
        std::cerr << "Error: Matrices must have same dimensions for subtraction\n";
        return Matrix(0, 0);
    }

    Matrix result(Row, Col);

    for(int i = 0; i < Row; i++){
        for (int j = 0; j < Col; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

int Matrix::getRow(){
    return Row;
}

int Matrix::getCol(){
    return Col;
}

void Matrix::print() {
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}
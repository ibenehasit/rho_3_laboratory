#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::vector;

class Matrix{
    int Row;
    int Col;
    vector<vector<double>> data;

public:

    //initialise an empty matrix
    Matrix(int row, int col);

    //initisialise a matrix with given values
    Matrix(vector<vector<double>> d);

    //initialise a matrix with random values
    Matrix(int row, int col, bool isRandom);

    //Matrix-matrix multiplication overload
    Matrix operator*(const Matrix& other) const;
    
    //Scalar-Matrix multiplication overload
    Matrix operator*(double scalar) const;

    //Matrix-Matrix addition overload 
    Matrix operator+(const Matrix& other) const;

        Matrix operator-(const Matrix& other) const;
    

    int getRow();
    int getCol();
    void print();
};
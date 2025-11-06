/*
@Filename: Matrix.cpp
@Author: Ivan Ling (ivan.ling@soton.ac.uk)
@Version: 1.0

@Date: 27/10/2025
@copyright Copyright (c) 2025
*/


#include "matrix.h"
#include <cstdlib> // For rand() and RAND_MAX

Matrix::Matrix()
{
	//TODO: Initialize Empty Matrix
}

Matrix::Matrix(vector<vector<double>> d)
{
	//TODO: Initialize matrix with given values
}

Matrix::Matrix(int r, int c, bool isRandom)
{
	//TODO: Create matrix of size defined by r and c. 
	// If isRandom is true, initialize with random number between 0.0 and 1.0
}

int Matrix::getRows() const { return rows; }
int Matrix::getCol() const { return col; }
vector<vector<double>> Matrix::getData() const { return data; }

void Matrix::print_matrix() const
{
	//TODO: Prints the Matrix
}

Matrix Matrix::operator*(const Matrix& mat) const
{
	//TODO: Implement matrix multiplication
	return Matrix(result);
}

Matrix Matrix::operator+(const Matrix& mat) const
{
	//TODO: Implement matrix addition
	return Matrix(result);
}

Matrix Matrix::operator-(const Matrix& mat) const
{
	//TODO: Implement matrix subtraction
	return Matrix(result);
}

Matrix Matrix::operator*(double num) const
{
	//TODO: Implement matrix scalar multiplication
	return Matrix(result);
}

Matrix Matrix::transpose() const
{
	//TODO: Implement matrix transpose
	return Matrix(result_data);
}

Matrix Matrix::element_multiply(const Matrix& mat) const
{
	//TODO: Implement element wise multiplication
	// Hint: For element wise multiply, every element of matrix A(i, j) is multiplied to the corresponding element in matrix B (i, j).
	//Therefore, A and B must be same size
	return Matrix(result_data);
}
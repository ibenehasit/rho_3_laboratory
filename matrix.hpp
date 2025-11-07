#pragma once

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Matrix
{
private:
	int rows; // Changed from 'Row'
	int col;  // Changed from 'Col'

public:
	vector<vector<double>> data; // Public data access is expected by nn_utils functions

	// Constructors
	Matrix(); // Implemented for safety and compatibility
    Matrix(int row, int col);
	explicit Matrix(vector<vector<double>> d);
	Matrix(int r, int c, bool isRandom);

	// Getters (Must be const to avoid type qualifier errors)
	int getRows() const; 
	int getCol() const;
	vector<vector<double>> getData() const;

	void print_matrix() const;

	// Operator Overloads (Must be const)
	Matrix operator*(const Matrix& mat) const;
	Matrix operator+(const Matrix& mat) const;
	Matrix operator-(const Matrix& mat) const;
	Matrix operator*(double num) const;

	// Required Backpropagation Functions
	Matrix transpose() const;
	Matrix element_multiply(const Matrix& mat) const;
};
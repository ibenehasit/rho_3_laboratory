#include "matrix.hpp"
#include <cstdlib> 
#include <ctime>   
#include <iostream> 

using namespace std;

// Default constructor - Fixes the missing default constructor issue
Matrix::Matrix()
{
	rows = 0;
	col = 0;
}

Matrix::Matrix(int a, int b){
    rows = a;
    col = b;

    data.resize(rows); 
    for (int i = 0; i < rows; i++) {
        data[i].resize(col, 0.0); 
    }
}

// Constructor with given values
Matrix::Matrix(vector<vector<double>> d)
{
	data = d; 
	rows = d.size(); 
	if (rows > 0) {
		col = d[0].size();
	} else {
		col = 0;
	}
}

// Constructor with random or zeroed values
Matrix::Matrix(int r, int c, bool isRandom)
{
	rows = r;
	col = c;
	data.resize(rows);
	for (int i = 0; i < rows; i++){
		data[i].resize(col);
	}
    
	if (isRandom){
		// Note: The srand(time(0)) is usually called once in main.cpp, but the matrix logic is correct.
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < col; j++) {
				data[i][j] = (double)rand() / RAND_MAX;
			}   
		}
	} else {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < col; j++) {
				data [i][j] = 0.0;
			}
		}
	}
}

// Getters (Renamed to match NeuralNetwork.h)
int Matrix::getRows() const { return rows; }
int Matrix::getCol() const { return col; }
vector<vector<double>> Matrix::getData() const { return data; }

void Matrix::print_matrix() const
{
	// Renamed from print() to print_matrix()
	for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Matrix-matrix multiplication overload (Logic retained from your original code)
Matrix Matrix::operator*(const Matrix& other) const {
    if (col != other.rows) {
        std::cerr << "Matrix dimensions incompatible for multiplication (A.col != B.row)\n";
        return Matrix(0, 0);
    }

    Matrix result(rows, other.col, false); 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.col; j++) {
            double sum = 0;
            for (int k = 0; k < col; k++) {
                sum += data[i][k] * other.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

// Matrix-Matrix addition overload (Logic retained)
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || col != other.col) {
        std::cerr << "Error: Matrices must have same dimensions for addition\n";
        return Matrix(0, 0);
    }

    Matrix result(rows, col, false);

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < col; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Matrix-Matrix subtraction overload (Logic retained)
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || col != other.col) {
        std::cerr << "Error: Matrices must have same dimensions for subtraction\n";
        return Matrix(0, 0);
    }

    Matrix result(rows, col, false);

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < col; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Matrix-scalar multiplication overload (Logic retained)
Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, col, false);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < col; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

// IMPLEMENTATION: Transpose (Required for Section 3.3.6.b & 3.3.8.a)
Matrix Matrix::transpose() const
{
	Matrix result_data(col, rows, false); // Swap dimensions
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			result_data.data[j][i] = data[i][j];
		}
	}
	return result_data;
}

// IMPLEMENTATION: Element-wise multiplication (Required for Section 3.3.5.c)
Matrix Matrix::element_multiply(const Matrix& other) const
{
	if (rows != other.rows || col != other.col) {
		std::cerr << "Error: Matrices must have same dimensions for element-wise multiplication\n";
		return Matrix(0, 0);
	}
	
	Matrix result_data(rows, col, false);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			result_data.data[i][j] = data[i][j] * other.data[i][j];
		}
	}
	return result_data;
}
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
    Matrix(int row, int col){
        Row = row;
        Col = col;

        data.resize(Row); 
        for (int i = 0; i < Row; i++) {
            data[i].resize(Col, 0.0); 
        }
    }

    //initisialise a matrix with given values
    Matrix(vector<vector<double>> d){
        data = d; // copy the input data
        Row = d.size(); //the number of rows = outer vector size
        if (Row > 0) {
            Col = d[0].size(); //Number of colums = first inner vector size
        } else {
            Col = 0;
        }
    }

    //initialise a matrix with random values
    Matrix(int row, int col, bool isRandom) {
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
    Matrix operator*(const Matrix& other) const {
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
    Matrix operator*(double scalar) const {
        Matrix result(Row, Col);
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    //Matrix-Matrix addition overload 
    Matrix operator+(const Matrix& other) const {
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

    

    int getRow(){
        return Row;
    }

    int getCol(){
        return Col;
    }

    void print() {
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                std::cout << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    //test for empty matrix 
    /*Matrix matrix1(6, 7);
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

    */

    Matrix matrixRandom1(6, 7, true);
    std::cout << "This is a " << matrixRandom1.getRow() << "x" << matrixRandom1.getCol() << " matrix\n";
    matrixRandom1.print();
    
    return 0;
}
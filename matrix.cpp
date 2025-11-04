#include <iostream>
#include <vector>

using std::vector;

class Matrix{
    int Row;
    int Col;
    vector<vector<double>> data;

public:
    Matrix(int row, int col){
        Row = row;
        Col = col;

        data.resize(Row); 
        for (int i = 0; i < Row; i++) {
            data[i].resize(Col, 0.0); 
        }
    }

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
    
    Matrix operator*(double scalar) const {
        Matrix result(Row, Col);
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

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
    Matrix matrix1(6, 7);
    std::cout << "This is a " << matrix1.getRow() << "x" << matrix1.getCol() << " matrix\n";
    matrix1.print();
    
    Matrix matrix2(7, 3);
    Matrix result1 = matrix1 * matrix2;
    std::cout << "\nMultiplication result is a " << result1.getRow() << "x" << result1.getCol() << " matrix\n";
    result1.print();
    
    Matrix result2 = matrix1 * 5;
    std::cout << "\nScalar multiplication result is a " << result2.getRow() << "x" << result2.getCol() << " matrix\n";
    result2.print();
    
    Matrix matrix3(6,7);
    std::cout << "\nAddition result is a " << matrix3.getRow() << "x" << matrix3.getCol() << " matrix\n";
    Matrix result3 = matrix1 + matrix3;
    result3.print();
    
    return 0;
}
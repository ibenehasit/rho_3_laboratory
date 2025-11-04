#include <iostream>
#include <vector>
//hehe hoo hoo 

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

    //function overload baybee
    Matrix operator*(const Matrix& other) const {
        if (Col != other.Row) {
            std::cerr << "Matrix dimensions incompatible for multiplication\n";
            return Matrix(0, 0); // Return empty matrix as error indicator
        }

        Matrix result(Row, other.Col); // this->Row and other.Col
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < other.Col; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < Col; k++) { // this->Col
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
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
    
    // Test multiplication
    Matrix matrix2(7, 3); // Compatible dimensions: 6x7 * 7x3 = 6x3
    Matrix result = matrix1 * matrix2;
    std::cout << "\nMultiplication result is a " << result.getRow() << "x" << result.getCol() << " matrix\n";
    result.print();
    
    return 0;
}
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

        data.resize(Row); // Create 'Row' number of empty vectors
        for (int i = 0; i < Row; i++) {
            data[i].resize(Col, 0.0); 
    }
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
    return 0;
}
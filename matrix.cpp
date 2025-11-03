#include <iostream>
#include <vector>

class Matrix{
    int Row;
    int Col;

public:
    Matrix(int row, int col){
        Row = row;
        Col = col;
    }

    int getRow(){
        return Row;
    }

    int getCol(){
        return Col;
    }

};

int main() {
    Matrix matrix1(6, 7);
    std::cout << matrix1.getRow() << "\n";
    std::cout << matrix1.getCol() << "\n";
    return 0;
}
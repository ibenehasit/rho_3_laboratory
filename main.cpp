/*
@Filename: main.cpp
Example test file for the Neural Network Lab (rho_3)
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "matrix.hpp" // Use "Matrix.h" as per the corrected header name
#include "NeuralNetwork.h"

using namespace std;

// Function to print a Matrix with a header
void printTestResult(const Matrix& result, const string& header) {
    cout << "\n--- " << header << " ---" << endl;
    for (int i = 0; i < result.getRows(); ++i) {
        // Print the probability for each class, formatted to 4 decimal places
        cout << "Class " << i << ": " << fixed << setprecision(4) << result.data[i][0] << endl;
    }
    // Use the argmax utility to get the final classification
    cout << "Classification: Class " << nn_utils::argmax(result) << endl;
    cout << "------------------------" << endl;
}


int main() {
    // 1. Initialize Random Seed
    srand(time(0));

    // 2. Define Training Data (3-bit binary input to 7-class one-hot output)
    
    // Inputs: Binary 1 through 7 (3-bit column vectors)
    vector<Matrix> training_data = {
        // Binary 1 (001) - EXPLICIT FIX APPLIED HERE
        Matrix(vector<vector<double>>{{0.0}, {0.0}, {1.0}}),
        // Binary 2 (010)
        Matrix(vector<vector<double>>{{0.0}, {1.0}, {0.0}}),
        // Binary 3 (011)
        Matrix(vector<vector<double>>{{0.0}, {1.0}, {1.0}}),
        // Binary 4 (100)
        Matrix(vector<vector<double>>{{1.0}, {0.0}, {0.0}}),
        // Binary 5 (101)
        Matrix(vector<vector<double>>{{1.0}, {0.0}, {1.0}}),
        // Binary 6 (110)
        Matrix(vector<vector<double>>{{1.0}, {1.0}, {0.0}}),
        // Binary 7 (111)
        Matrix(vector<vector<double>>{{1.0}, {1.0}, {1.0}})
};

    // Targets: One-hot encoded classes (0 through 6)
    vector<Matrix> target_data = {
        // Target for Binary 1 is Class 0
        Matrix({{1.0}, {0.0}, {0.0}, {0.0}, {0.0}, {0.0}, {0.0}}),
        // Target for Binary 2 is Class 1
        Matrix({{0.0}, {1.0}, {0.0}, {0.0}, {0.0}, {0.0}, {0.0}}),
        // Target for Binary 3 is Class 2
        Matrix({{0.0}, {0.0}, {1.0}, {0.0}, {0.0}, {0.0}, {0.0}}),
        // Target for Binary 4 is Class 3
        Matrix({{0.0}, {0.0}, {0.0}, {1.0}, {0.0}, {0.0}, {0.0}}),
        // Target for Binary 5 is Class 4
        Matrix({{0.0}, {0.0}, {0.0}, {0.0}, {1.0}, {0.0}, {0.0}}),
        // Target for Binary 6 is Class 5
        Matrix({{0.0}, {0.0}, {0.0}, {0.0}, {0.0}, {1.0}, {0.0}}),
        // Target for Binary 7 is Class 6
        Matrix({{0.0}, {0.0}, {0.0}, {0.0}, {0.0}, {0.0}, {1.0}})
    };

    // 3. Define Network Topology: 3 Input, 4 Hidden Neurons, 7 Output
    vector<int> topology = {3, 4, 7};
    
    // 4. Instantiate the ANN
    ANN network(topology);

    // Initial Test (Before Training)
    cout << "--- Initial Test (Weights are Random) ---" << endl;
    network.feedforward(training_data[4]).print_matrix(); // Test Binary 5

    // 5. Train the ANN
    int epochs = 20000;
    double learning_rate = 0.1;
    cout << "\nStarting training for " << epochs << " epochs with learning rate " << learning_rate << "..." << endl;
    network.train(training_data, target_data, epochs, learning_rate);
    cout << "\nTraining complete." << endl;

    // 6. Test the ANN (After Training)

    // Test Case 1: Binary 1 (Expected Class 0)
    Matrix test_input_1 = training_data[0];
    Matrix result_1 = network.feedforward(test_input_1);
    printTestResult(result_1, "Test Result: Input [0, 0, 1] (Binary 1)");

    // Test Case 2: Binary 5 (Expected Class 4)
    Matrix test_input_5 = training_data[4];
    Matrix result_5 = network.feedforward(test_input_5);
    printTestResult(result_5, "Test Result: Input [1, 0, 1] (Binary 5)");

    return 0;
}
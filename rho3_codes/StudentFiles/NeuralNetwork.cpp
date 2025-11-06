/*
@Filename: NeuralNetwork.cpp
@Author: Ivan Ling (ivan.ling@soton.ac.uk)
@Version: 1.2

@Date: 27/10/2025
@copyright Copyright (c) 2025
*/


#include "NeuralNetwork.h"
#include <cmath>      

using namespace std;


//A layer refers to the neurons in a single layer
//Each will have their own wieghts and biases

Layer::Layer(int input_size, int output_size)
{
	weights = Matrix(output_size, input_size, true);
	bias = Matrix(output_size, 1, true);
}

Layer::Layer() {}


ANN::ANN(vector<int> sizes)
{
	//TODO: Populate the layers vector with the correctly sized Layers object as described by the input. 
}

Matrix ANN::feedforward(Matrix input)
{
	activations.clear();
	activations.push_back(input); //First activation layer is always the input
	Matrix current_activation = input;
	
	// TODO: Iterate across all the layers, calculate the activations and use it as the input to the next layer. 

	// Hint: You might want to use the sigmoid function... 
	
	return current_activation;
}

double ANN::update(Matrix target, double training_rate)
{
	//TODO: Read and understand section 3.3
	// Complete this function based on instructions from section 3.3

	
	return absError;
}


// Utility functions for ANN
Matrix nn_utils::sigmoid(const Matrix& m)
{
	vector<vector<double>> result_data(m.getRows(), vector<double>(m.getCol()));
	for (int i = 0; i < m.getRows(); ++i)
	{
		for (int j = 0; j < m.getCol(); ++j)
		{
			result_data[i][j] = 1.0 / (1.0 + exp(-m.data[i][j]));
		}
	}
	return Matrix(result_data);
}

Matrix nn_utils::dsigmoid(const Matrix& m)
{
	vector<vector<double>> result_data(m.getRows(), vector<double>(m.getCol()));
	for (int i = 0; i < m.getRows(); ++i)
	{
		for (int j = 0; j < m.getCol(); ++j)
		{
			result_data[i][j] = m.data[i][j] * (1.0 - m.data[i][j]);
		}
	}
	return Matrix(result_data);
}

int nn_utils::argmax(const Matrix& m)
{
	if (m.getCol() != 1)
	{
		cout<< "argmax only supports 1-column matrices!";
	}
	double max_val = -99999;
	int max_idx = 0;
	for (int i = 0; i < m.getRows(); i++)
	{
		if (m.data[i][0] > max_val)
		{
			max_val = m.data[i][0];
			max_idx = i;
		}
	}
	return max_idx;
}

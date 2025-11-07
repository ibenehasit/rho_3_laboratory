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
	this->layerSizes = sizes; // Store the topology (optional but good practice)
	// The layers vector will be one element shorter than the sizes vector
	// because a Layer object holds the weights connecting one layer to the next.
	for (size_t i = 0; i < sizes.size() - 1; ++i)
	{
		// sizes[i] is the input size for the current Layer
		int input_size = sizes[i]; 
		// sizes[i+1] is the output size for the current Layer
		int output_size = sizes[i+1]; 
		
		// Create a new Layer with random weights and biases (Layer::Layer(int, int) does this)
		layers.push_back(Layer(input_size, output_size));
	}
}

Matrix ANN::feedforward(Matrix input)
{
	activations.clear();
	activations.push_back(input); // First activation layer is always the input (A^0)
	Matrix current_activation = input;
	
	// TODO: Iterate across all the layers, calculate the activations and use it as the input to the next layer. 

	for (const auto& layer : layers)
	{
		// 1. Calculate Net Input Z = W * A + B
		// Matrix multiplication: (W * A)
		Matrix weighted_sum = layer.weights * current_activation;
		// Matrix addition: (W * A) + B
		Matrix net_input = weighted_sum + layer.bias; 

		// 2. Calculate Activation A = sigmoid(Z)
		Matrix new_activation = nn_utils::sigmoid(net_input); 

		// Update the current activation for the next layer's input
		current_activation = new_activation;
		
		// Store the new activation for backpropagation in section 3.3
		activations.push_back(current_activation); 
	}

	return current_activation; // Returns the final output layer activation
}

// ...

double ANN::update(Matrix target, double training_rate)
{
	// 1. Get the final activation (A^L) from the forward pass
	Matrix final_activation = activations.back(); 

	// 2. Calculate the raw output error (Error^L = Target - A^L)
	Matrix error = target - final_activation;

	// 3. Calculate and store the loss (Mean Squared Error) for return
	double absError = 0.0;
	for (int i = 0; i < error.getRows(); ++i)
	{
		// Squared Error (sum of squares of all error components)
		absError += (error.data[i][0] * error.data[i][0]);
	}
	// The full MSE is Sum(error^2) / 2. We divide by 2 later or omit it as it's just for reporting.
	// For simplicity, we just return the sum of squared errors / 2 (as specified in the lab)
	absError *= 0.5;

	// This is the error/delta we will backpropagate. Start with the output layer's error.
	Matrix current_delta = error; 

	// 4. Start the Backpropagation Loop: Iterate BACKWARDS from the last layer (layers.size() - 1)
	// The loop stops at the second layer (i=1), as the first layer (i=0) is the input layer which has no weights to update.
	for (int i = layers.size() - 1; i >= 0; --i)
	{
		Layer& current_layer = layers[i]; // The layer whose weights we are adjusting (W^l, B^l)
		
		// The activation that was the INPUT to the current_layer (A^(l-1))
		Matrix prev_activation = activations[i]; 

		// --- A. Calculate the Scaled Gradient (Delta) ---
		
		// 5.a & b. Calculate the derivative of the sigmoid function for the current layer's activation (A^l)
		// We use the derivative of the activation function, which is σ'(Z) = A * (1 - A)
		Matrix dsigmoid = nn_utils::dsigmoid(activations[i + 1]);

		// 5.c. Calculate the layer's scaled gradient (Delta^l = Error^l * σ'(Z^l))
		// The error from the next layer is element-wise multiplied by the derivative of this layer's activation
		Matrix gradient = current_delta.element_multiply(dsigmoid);

		// 5.d. Scale the gradient by the training rate (Delta^l = training_rate * Delta^l)
		gradient = gradient * training_rate; 

		// --- B. Update Weights and Biases ---
		
		// 6.a, b, c. Calculate the change in weights (Delta W = Gradient * (A^(l-1))^T)
		Matrix delta_weights = gradient * prev_activation.transpose();

		// 7. Apply Delta Weights: W^l = W^l + Delta W
		current_layer.weights = current_layer.weights + delta_weights;

		// 7. Update Bias: B^l = B^l + Gradient
		current_layer.bias = current_layer.bias + gradient;

		// --- C. Pass Error to the Previous Layer ---
		
		if (i > 0) 
		{
			// 8.a & b. Calculate the new error to pass back (Error^(l-1) = (W^l)^T * Delta^l)
			// This is the input error for the next iteration (the layer before this one)
			current_delta = current_layer.weights.transpose() * current_delta;
		}
	}
	
	return absError; 
}

double ANN::train(
	vector<Matrix>& training_data, 
	vector<Matrix>& target_data, 
	int epochs, 
	double learning_rate)
{
	// Ensure the training data and target data are compatible
	if (training_data.size() != target_data.size())
	{
		cerr << "Error: Training data and target data must have the same number of examples." << endl;
		return -1.0; 
	}
	
	// Determine the total number of training examples
	size_t num_examples = training_data.size();
	double total_error = 0.0;

	// 1. Outer Loop: Iterate through all epochs
	for (int i = 0; i < epochs; ++i)
	{
		double epoch_error = 0.0;
		
		// 2. Inner Loop: Iterate through all training examples
		for (size_t j = 0; j < num_examples; ++j)
		{
			Matrix input = training_data[j];
			Matrix target = target_data[j];

			// 3. Forward Pass: Calculate the prediction
			// The feedforward function stores the activations needed for backpropagation
			feedforward(input);

			// 4. Update/Backpropagation: Calculate error, adjust weights/biases
			// The update function returns the total error (loss) for this example
			double example_error = update(target, learning_rate);
			
			// Accumulate error for reporting
			epoch_error += example_error;
		}

		// Optional: Print the average error every few epochs to monitor learning
		// This helps confirm the network is learning (error should decrease)
		if ((i + 1) % 1000 == 0 || i == 0 || i == epochs - 1) 
		{
			double avg_error = epoch_error / num_examples;
			cout << "Epoch: " << (i + 1) << " | Average Loss: " << avg_error << endl;
		}

		// Save the final error to report at the end
		total_error = epoch_error;
	}

	return total_error / num_examples; // Return the average loss of the final epoch
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

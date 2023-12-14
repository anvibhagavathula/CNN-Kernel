#include "linear.h"

float *linear(float *input, float **weights, float *biases, int inputSize, int outputSize){
    // Check for empty input
    if (input == NULL || inputSize == 0 || outputSize == 0){
    return NULL;
    }

    float *output = malloc(outputSize * sizeof(*output));

    for (int o = 0; o < outputSize; o++)
    {
        output[o] = 0.0;
        for (int i = 0; i < inputSize; i++)
        {
            output[o] += input[i] * weights[i][o];
        }
        output[o] += biases[o];
    } 
    return output;
}

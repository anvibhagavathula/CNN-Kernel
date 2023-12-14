#include "conv.h"

// Basic convolution operation
float ***convolution(float ***image, int numChannels, float ****kernel, float *biasData, int numFilters, int inputSize, int kernelSize)
{
    int outputSize = inputSize - kernelSize + 1;

    // Allocate memory for the convolution output
    float ***convOutput = malloc(numFilters * sizeof(*convOutput));

    for (int i = 0; i < numFilters; i++)
    {
        convOutput[i] = malloc(outputSize * sizeof(*convOutput[i]));
        for (int j = 0; j < outputSize; j++)
        {
            convOutput[i][j] = malloc(outputSize * sizeof(*convOutput[i][j]));
        }
    }

    // Perform the convolution operation
    for (int f = 0; f < numFilters; f++){
            // Index into the output row 
            for (int i = 0; i < outputSize; i++){   
                // Index into the output column 
                for (int j = 0; j < outputSize; j++){
                    // Loop through number of channels 
                    float sum = 0.0;
                    for (int c = 0; c < numChannels; c++){
                        // Index into kernel row 
                        for (int kr = 0; kr < kernelSize; kr++){
                            // Index into kernel column
                            for (int kc = 0; kc < kernelSize; kc++){
                                sum +=  kernel[f][c][kr][kc] * image[c][i+kr][j+kc];
                            }
                        }
                    }
                    convOutput[f][i][j] = sum + biasData[f];
                    convOutput[f][i][j] = relu(convOutput[f][i][j]);   
                }
            }
        }
        return convOutput;
    }



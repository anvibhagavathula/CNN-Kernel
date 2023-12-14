#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_linear.h"


void test_linear(void)
{
    // Test Case 1: Input Size 2
    int inputSize1 = 2;
    int outputSize1 = 2;

    float input1_data[] = {1, 2};
    float *input1 = (float *)malloc(inputSize1 * sizeof(float));
    for (int i = 0; i < inputSize1; i++) {
        input1[i] = input1_data[i];
    }

    float weights1_data[2][2] = {{1, 2}, {3, 4}};
    float **weights1 = (float **)malloc(inputSize1 * sizeof(float *));
    for (int i = 0; i < inputSize1; i++) {
        weights1[i] = (float *)malloc(outputSize1 * sizeof(float));
        for (int j = 0; j < inputSize1; j++) {
            weights1[i][j] = weights1_data[i][j];
        }
    }

    float biases1_data[] = {1, 1};
    float *biases1 = (float *)malloc(inputSize1 * sizeof(float));
    for (int i = 0; i < inputSize1; i++) {
        biases1[i] = biases1_data[i];
    }

    float test1_output[] = {8, 11};
    float* linear_output1 = linear(input1, weights1, biases1, inputSize1, outputSize1);


    for (int i = 0; i < inputSize1; i++) {
                TEST_ASSERT_EQUAL_FLOAT(test1_output[i], linear_output1[i]);
            }
    

    // Test Case 2: Input Size 4
    int inputSize2 = 4;
    int outputSize2 = 4;

    float input2_data[] = {1, 2, 3, 4};
    float *input2 = (float *)malloc(inputSize2 * sizeof(float));
    for (int i = 0; i < inputSize2; i++) {
        input2[i] = input2_data[i];
    }

    float weights2_data[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    float **weights2 = (float **)malloc(inputSize2 * sizeof(float *));
    for (int i = 0; i < inputSize2; i++) {
        weights2[i] = (float *)malloc(outputSize2 * sizeof(float));
        for (int j = 0; j < outputSize2; j++) {
            weights2[i][j] = weights2_data[i][j];
        }
    }

    float biases2_data[] = {1, 1, 1, 1};
    float *biases2 = (float *)malloc(inputSize2 * sizeof(float));
    for (int i = 0; i < inputSize2; i++) {
        biases2[i] = biases2_data[i];
    }

    float test2_output[] = {91, 101, 111, 121};
    float* linear_output2 = linear(input2, weights2, biases2, inputSize2, outputSize2);
    
    for (int i = 0; i < inputSize2; i++) {
                TEST_ASSERT_EQUAL_FLOAT(test2_output[i], linear_output2[i]);
            }


    // Test Case 3: Input Size 6
    int inputSize3 = 6;
    int outputSize3 = 6;

    float input3_data[] = {1, 2, 3, 4, 5, 6};
    float *input3 = (float *)malloc(inputSize3 * sizeof(float));
    for (int i = 0; i < inputSize3; i++) {
        input3[i] = input3_data[i];
    }

    float weights3_data[6][6] = {
        {1, 2, 3, 4, 1, 1}, 
        {5, 6, 7, 8, 1, 1}, 
        {9, 10, 11, 12, 1, 1}, 
        {13, 14, 15, 16, 1, 1}, 
        {17, 18, 19, 20, 1, 1}, 
        {21, 22, 23, 24, 1, 1}
        };
    float **weights3 = (float **)malloc(inputSize3 * sizeof(float *));
    for (int i = 0; i < inputSize3; i++) {
        weights3[i] = (float *)malloc(outputSize3 * sizeof(float));
        for (int j = 0; j < outputSize3; j++) {
            weights3[i][j] = weights3_data[i][j];
        }
    }

    float biases3_data[] = {1, 1, 1, 1, 1, 1};
    float *biases3 = (float *)malloc(inputSize3 * sizeof(float));
    for (int i = 0; i < inputSize3; i++) {
        biases3[i] = biases3_data[i];
    }

    float test3_output[] = {302, 323, 344, 365, 22, 22};
    float* linear_output3 = linear(input3, weights3, biases3, inputSize3, outputSize3);
    
    for (int i = 0; i < inputSize3; i++) {
                TEST_ASSERT_EQUAL_FLOAT(test3_output[i], linear_output3[i]);
            }

}



// Add more test cases as needed
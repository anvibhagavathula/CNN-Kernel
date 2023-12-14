#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "../utils/data_utils.h"
#include "test_conv.h"

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

void test_conv(void){
    // Test case 1: InputSize 5 
    float test1_input[1][5][5] = {{
        {1, 4, 5, 6, 7},
        {3, 2, 2, 1, 0},
        {1, 1, 6, 1, 9},
        {7, 1, 4, 2, 8},
        {8, 7, 3, 2, 1}
    }};
    
    float test1_ker[1][1][3][3] = {{{
        {0, 0, 4},
        {2, 3, 1},
        {0, 1, 1}
    }}};
    
    float test1_output[1][3][3] = {{
        {42, 43, 46},
        {25, 32, 35},
        {56, 26, 62}
    }};

    float bias_data1[1] = {1.0};

    int numChannels1 = 1;
    int numFilters1 = 1;
    int inputSize1 = 5; 
    int kernelSize1 = 3;  // Adjusted kernel size
    float ***test1_img = init_image(test1_input, 5, numChannels1);
    float ****test1_kernel = init_kernel(test1_ker, numFilters1, kernelSize1);
    float ***convOutput_1 = convolution(test1_img, numChannels1, test1_kernel, bias_data1, numFilters1, inputSize1, kernelSize1);
    

    // for (int f = 0; f < numFilters1; f++) {
    //     for (int i = 0; i < 3; i++) {
    //         for (int j = 0; j < 3; j++) {
    //             printf("%f ", convOutput_1[f][i][j]);
    //         }
    //         printf("\n");
    //     }
    // }

    // Compare the computed output with the expected output using nested loops
    for (int c = 0; c < numChannels1; c++) {
        for (int i = 0; i < kernelSize1; i++) {
            for (int j = 0; j < kernelSize1; j++) {
                TEST_ASSERT_EQUAL_FLOAT(test1_output[c][i][j], convOutput_1[c][i][j]);
            }
        }
    }

    // Test case 2: InputSize 10 
    float test2_input[1][10][10] = {{
        {1, 4, 5, 6, 7, 1, 4, 5, 6, 7},
        {3, 2, 2, 1, 0, 3, 2, 2, 1, 0},
        {1, 1, 6, 1, 9, 1, 1, 6, 1, 9},
        {7, 1, 4, 2, 8, 7, 1, 4, 2, 8},
        {8, 7, 3, 2, 1, 8, 7, 3, 2, 1},
        {1, 4, 5, 6, 7, 1, 4, 5, 6, 7},
        {3, 2, 2, 1, 0, 3, 2, 2, 1, 0},
        {1, 1, 6, 1, 9, 1, 1, 6, 1, 9},
        {7, 1, 4, 2, 8, 7, 1, 4, 2, 8},
        {8, 7, 3, 2, 1, 8, 7, 3, 2, 1}
    }};
    
    float test2_ker[1][1][3][3] = {{{
        {0, 0, 4},
        {2, 3, 1},
        {0, 1, 1}
    }}};
    
    float test2_output[1][8][8] = {{
        {42, 43, 46, 20, 30, 42, 43, 46},
        {25, 32, 35, 58, 39, 25, 32, 35},
        {56, 26, 62, 49, 58, 56, 26, 62}, 
        {66, 45, 59, 52, 43, 66, 45, 59}, 
        {36, 41, 41, 70, 55, 36, 41, 41}, 
        {42, 43, 46, 20, 30, 42, 43, 46},
        {25, 32, 35, 58, 39, 25, 32, 35}, 
        {56, 26, 62, 49, 58, 56, 26, 62}
    }};

    float bias_data2[1] = {1.0};

    int numChannels = 1;
    int numFilters = 1;
    int inputSize = 10; 
    int kernelSize = 3;  // Adjusted kernel size
    float ***test2_img = init_image_10(test2_input, 10, numChannels);
    float ****test2_kernel = init_kernel(test2_ker, numFilters, kernelSize);
    float ***convOutput_2 = convolution(test2_img, numChannels, test2_kernel, bias_data2, numFilters, inputSize, kernelSize);

    // for (int f = 0; f < numFilters; f++) {
    //     for (int i = 0; i < 8; i++) {
    //         for (int j = 0; j < 8; j++) {
    //             printf("%f ", convOutput_2[f][i][j]);
    //         }
    //         printf("\n");
    //     }
    // }

    // Compare the computed output with the expected output using nested loops
    for (int c = 0; c < numChannels; c++) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                TEST_ASSERT_EQUAL_FLOAT(test2_output[c][i][j], convOutput_2[c][i][j]);
            }
        }
    }

    // Test case 3: InputSize 7 
    float test3_input[1][7][7] = {{
        {1, 4, 5, 6, 7, 1, 4},
        {3, 2, 2, 1, 0, 3, 2},
        {1, 1, 6, 1, 9, 1, 1},
        {7, 1, 4, 2, 8, 7, 1},
        {8, 7, 3, 2, 1, 8, 7},
        {1, 4, 5, 6, 7, 1, 4},
        {3, 2, 2, 1, 0, 3, 2}
    }};
    
    float test3_ker[1][1][3][3] = {{{
        {0, 0, 4},
        {2, 3, 1},
        {0, 1, 1}
    }}};
    
    float test3_output[1][5][5] = {{
        {42, 43, 46, 20, 30},
        {25, 32, 35, 58, 39},
        {56, 26, 62, 49, 58}, 
        {66, 45, 59, 52, 43}, 
        {36, 41, 41, 70, 55}, 
    }};

    float bias_data3[1] = {1.0};

    int numChannels3 = 1;
    int numFilters3 = 1;
    int inputSize3 = 7; 
    int kernelSize3 = 3;  // Adjusted kernel size
    float ***test3_img = init_image_7(test3_input, 7, numChannels3);
    float ****test3_kernel = init_kernel(test3_ker, numFilters3, kernelSize3);
    float ***convOutput_3 = convolution(test3_img, numChannels3, test3_kernel, bias_data3, numFilters3, inputSize3, kernelSize3);

    // for (int f = 0; f < numFilters3; f++) {
    //     for (int i = 0; i < 5; i++) {
    //         for (int j = 0; j < 5; j++) {
    //             printf("%f ", convOutput_3[f][i][j]);
    //         }
    //         printf("\n");
    //     }
    // }

    // Compare the computed output with the expected output using nested loops
    for (int c = 0; c < numChannels3; c++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                TEST_ASSERT_EQUAL_FLOAT(test3_output[c][i][j], convOutput_3[c][i][j]);
            }
        }
    }
}











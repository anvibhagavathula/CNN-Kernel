#include "unity/unity.h"
#include "../kernel/kernel.h"
#include "test_matrix_ops.h"

/**** HELPER FUNCTIONS ****/
/**** YOUR CODE HERE ****/

void test_matmul_block_matrices(void) 
{

    float** initializeMatrix(int n) {
        float **matrix = (float**)malloc(n * sizeof(float*));
        if (matrix == NULL) {
            return NULL;
        }

        // Initialize the matrix elements with random integers 
        for (int i = 0; i < n; i++) {
            matrix[i] = (float*)malloc(n * sizeof(float*));
            if (matrix[i] == NULL) {
                return NULL;
            }

            // Initialize the matrix elements with random integers between 1 and 100 (adjust as needed)
            for (int j = 0; j < n; j++) {
                matrix[i][j] = rand() % 100; // Generates random integers between 1 and 100
            }
        }   
        return matrix; 
    }

    // // Test Case 1: 256 x 256 matrices 
    // int n1 = 256; 
    // float** A1 = initializeMatrix(n1);
    // float** B1 = initializeMatrix(n1);
    // float** test_output1 = matmul(A1, B1, 256, 256, 256, 256);
    // float** block_output1 = matmul_multithread(A1, B1, 256, 256, 256, 256);

    // for (int i = 0; i < 256; i++) {
    //     for (int j = 0; j < 256; j++) {
    //         printf("%.2f ", block_output1[i][j]);
    //     }
    //     printf("\n");
    // }

    // for (int i = 0; i < 256; i++) {
    //     for (int j = 0; j < 256; j++) {
    //         TEST_ASSERT_EQUAL_FLOAT(test_output1[i][j], block_output1[i][j]);
    //     }
    // }

    // Test Case 2: 512 x 512 matrices 
    // int n2 = 512; 
    // float** A2 = initializeMatrix(n2);
    // float** B2 = initializeMatrix(n2);
    // float** test_output2 = matmul(A2, B2, 512, 512, 512, 512);
    // float** block_output2 = matmul_multithread(A2, B2, 512, 512, 512, 512);

    // for (int i = 0; i < 512; i++) {
    //     for (int j = 0; j < 512; j++) {
    //         printf("%.2f ", block_output2[i][j]);
    //     }
    //     printf("\n");
    // }

    // for (int i = 0; i < 512; i++) {
    //     for (int j = 0; j < 512; j++) {
    //         TEST_ASSERT_EQUAL_FLOAT(test_output2[i][j], block_output2[i][j]);
    //     }
    // }

    // // // Test Case 3: 1024 x 1024 matrices 
    int n3 = 1024; 
    float** A3 = initializeMatrix(n3);
    float** B3 = initializeMatrix(n3);
    float** test_output3 = matmul(A3, B3, 1024, 1024, 1024, 1024);
    // float** block_output3 = matmul_multithread(A3, B3, 1024, 1024, 1024, 1024);

    // for (int i = 0; i < 1024; i++) {
    //     for (int j = 0; j < 1024; j++) {
    //         printf("%.2f ", block_output3[i][j]);
    //     }
    //     printf("\n");
    // }

    // for (int i = 0; i < 1024; i++) {
    //     for (int j = 0; j < 1024; j++) {
    //         TEST_ASSERT_EQUAL_FLOAT(test_output3[i][j], block_output3[i][j]);
    //     }
    // }
}


void test_matmul_square_matrices(void)
{
    // Test Case 1: 1 x 1 matrices 
    float A1_data[][1] = {{1}};
    float **A1 = (float**)malloc(1 * sizeof(float));
    for (int i = 0; i < 1; i++) {
        A1[i] = (float *)malloc(1 * sizeof(float));
        for (int j = 0; j < 1; j++) {
            A1[i][j] = A1_data[i][j];
        }
    }

    float B1_data[][1] = {{1}};
    float **B1 = (float**)malloc(1 * sizeof(float));
    for (int i = 0; i < 1; i++) {
        B1[i] = (float *)malloc(1 * sizeof(float));
        for (int j = 0; j < 1; j++) {
            B1[i][j] = B1_data[i][j];
        }
    }

    float test1_output[][1] = {{1}};
    float** matmul_output1 = matmul(A1, B1, 1, 1, 1, 1);

    // for (int i = 0; i < 1; i++) {
    //     for (int j = 0; j < 1; j++) {
    //         printf("%.2f ", matmul_output1[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 1; j++) {
            TEST_ASSERT_EQUAL_FLOAT(test1_output[i][j], matmul_output1[i][j]);
        }
    }


    // Test Case 1: 2 x 2 matrices 
    float A2_data[2][2] = {{1, 2}, {1, 2}};
    float **A2 = (float**)malloc(2 * sizeof(float));
    for (int i = 0; i < 2; i++) {
        A2[i] = (float *)malloc(2 * sizeof(float));
        for (int j = 0; j < 2; j++) {
            A2[i][j] = A2_data[i][j];
        }
    }

    float B2_data[2][2] = {{1, 1}, {1, 1}};
    float **B2 = (float**)malloc(2 * sizeof(float));
    for (int i = 0; i < 2; i++) {
        B2[i] = (float *)malloc(2 * sizeof(float));
        for (int j = 0; j < 2; j++) {
            B2[i][j] = B2_data[i][j];
        }
    }

    float test2_output[2][2] = {{3, 3}, {3, 3}};
    float** matmul_output2 = matmul(A2, B2, 2, 2, 2, 2);

    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         printf("%.2f ", matmul_output2[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            TEST_ASSERT_EQUAL_FLOAT(test2_output[i][j], matmul_output2[i][j]);
        }
    }


    // Test Case 1: 3 x 3 matrices 
    float A3_data[3][3] = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    float **A3 = (float**)malloc(3 * sizeof(float));
    for (int i = 0; i < 3; i++) {
        A3[i] = (float *)malloc(3 * sizeof(float));
        for (int j = 0; j < 3; j++) {
            A3[i][j] = A3_data[i][j];
        }
    }

    float B3_data[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    float **B3 = (float**)malloc(3 * sizeof(float));
    for (int i = 0; i < 3; i++) {
        B3[i] = (float *)malloc(3 * sizeof(float));
        for (int j = 0; j < 3; j++) {
            B3[i][j] = B3_data[i][j];
        }
    }

    float test3_output[3][3] = {{6, 6, 6}, {6, 6, 6}, {6, 6, 6}};
    float** matmul_output3 = matmul_blocking(A3, B3, 3, 3, 3, 3);

    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         printf("%.2f ", matmul_output3[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            TEST_ASSERT_EQUAL_FLOAT(test3_output[i][j], matmul_output3[i][j]);
        }
    }


}

void test_matmul_incompatible_dimensions(void)
{
    // Setup
    float **A = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        A[i] = (float *)malloc(3 * sizeof(float));
    }

    float **B = (float **)malloc(2 * sizeof(float *));
    for (int i = 0; i < 2; i++)
    {
        B[i] = (float *)malloc(2 * sizeof(float));
    }

    // Run function under test
    float **C = matmul(A, B, 2, 3, 2, 2);

    // Check expectations
    UNITY_TEST_ASSERT_NULL(C, __LINE__, "Expected NULL!");

    // Cleanup
    for (int i = 0; i < 2; i++)
    {
        free(A[i]);
        free(B[i]);
    }
    free(A);
    free(B);
}
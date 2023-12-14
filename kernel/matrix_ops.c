#include "matrix_ops.h"
#include <time.h>
#include <pthread.h>


float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    // output row dimension = A_rows
    for (int i = 0; i < A_rows; i++)
    {
        // output col dimension = B_cold 
        for (int j = 0; j < B_cols; j++)
        {
            float elementwise = 0;
            
            // perform elementwise multiplication 
            for (int k = 0; k < A_cols; k++)
            {
                elementwise += A[i][k] * B[k][j];
            }

            // assign to output matrix 
            C[i][j] = elementwise;
        }
    } 

    return C;
}


float **matmul_blocking(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols){
    if (A_cols != B_rows) {
        printf("Matrix dimensions incompatible for multiplication.\n");
        return NULL;
    }

    // Allocate memory for the result matrix C
    float **C = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        C[i] = (float *)malloc(B_cols * sizeof(float));
    }

    // Define the block size 
    int block_size = 16;

    for (int i = 0; i < A_rows; i += block_size) {
        for (int j = 0; j < B_cols; j += block_size) {
            for (int k = 0; k < A_cols; k += block_size) {
                // Compute the block matrix multiplication
                for (int ii = i; ii < i + block_size && ii < A_rows; ii++) {
                    for (int jj = j; jj < j + block_size && jj < B_cols; jj++) {
                        float elementwise = 0;
                        for (int kk = k; kk < k + block_size && kk < A_cols; kk++) {
                            elementwise += A[ii][kk] * B[kk][jj];
                        }
                        C[ii][jj] += elementwise;
                    }
                }
            }
        }
    }

    return C;
}


CSRFormat generate_csr_arrays(float **matrix, int num_rows, int num_cols) {
    // Count the number of non-zero elements to determine the size of CSR arrays
    int non_zero = 0;

    // Counting the nonzero elements in A
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (matrix[i][j] != 0.0) {
                non_zero += 1;
            }
        }
    }

    // Allocate memory for A and B CSR arrays
    float *values = (float *)malloc(non_zero* sizeof(float));
    int *row_idx_array = (int *)malloc((num_rows + 1) * sizeof(int));
    int *col_idx_array = (int *)malloc(non_zero * sizeof(int));

    // Initialize CSR arrays
    int idx = 0;
    row_idx_array[0] = 0;

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (matrix[i][j] != 0.0) {
                values[idx] = matrix[i][j];
                col_idx_array[idx] = j;
                idx++;
            }
        }
        row_idx_array[i + 1] = idx;
    }

    CSRFormat csr_arrays = {values, row_idx_array, col_idx_array};
    return csr_arrays;
}


float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {

    // Turn A and B into CSR formatted arrays
    CSRFormat A_csr = generate_csr_arrays(A, A_rows, A_cols);
    float *A_values = A_csr.values;
    int *A_row_idx_array = A_csr.row_idx_array;
    int *A_col_idx_array = A_csr.col_idx_array;

    CSRFormat B_csr = generate_csr_arrays(B, B_rows, B_cols);
    float *B_values = B_csr.values;
    int *B_row_idx_array = B_csr.row_idx_array;
    int *B_col_idx_array = B_csr.col_idx_array;

    // Allocate memory for the result matrix C
    float **result = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        result[i] = (float *)malloc(B_cols * sizeof(float));
    }

    // Carry out matrix multiplication using the CSR format 
    for (int i = 0; i < A_rows; i++) {
        // Iterates over the non-zero elements of the current row of A_csr
        for (int j = A_row_idx_array[i]; j < A_row_idx_array[i + 1]; j++){
            // identify the column and value of A 
            int A_col_val = A_col_idx_array[j];
            float A_val = A_values[j];
            
            // Identifying output positions of nonzero B values 
            for (int k = B_row_idx_array[A_col_val]; k < B_row_idx_array[A_col_val + 1]; k++) {
                int B_col_val = B_col_idx_array[k];
                float B_val = B_values[k];
                result[i][B_col_val] += A_val * B_val;
            }
        }
    }

    // Free the memory 
    free(A_values);
    free(A_row_idx_array);
    free(A_col_idx_array);

    free(B_values);
    free(B_row_idx_array);
    free(B_col_idx_array);

    return result;
}


void *multiply(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    for (int i = data->A_rows; i < data->A_cols; i++) {
        for (int j = 0; j < data->B_cols; j++) {
            data->result[i][j] = 0.0;
            for (int k = 0; k < data->B_rows; k++) {
                data->result[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }

    pthread_exit(NULL);
}


float **matmul_multithread(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols) {
    
    // Allocate memory for the result matrix
    float **result = (float **)malloc(A_rows * sizeof(float *));
    for (int i = 0; i < A_rows; i++) {
        result[i] = (float *)malloc(B_cols * sizeof(float));
    }

    // Use pthread to create threads and initialise ThreadData struct 
    pthread_t *threads;
    threads = (pthread_t *)malloc(A_rows * sizeof(pthread_t));
    ThreadData *thread_data;
    thread_data = (ThreadData *)malloc(A_rows * sizeof(ThreadData));

    for (int i = 0; i < A_rows; ++i) {
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].result = result;
        thread_data[i].A_rows = i;
        thread_data[i].A_cols = i+1;
        thread_data[i].B_rows = B_rows;
        thread_data[i].B_cols = B_cols;
        pthread_create(&threads[i], NULL, multiply, (void *)&thread_data[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < A_rows; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Free the memory
    free(threads);
    free(thread_data);

    return result;
}


// float** initializeMatrix(int n) {
//     float **matrix = (float**)malloc(n * sizeof(float*));
//     if (matrix == NULL) {
//         return NULL;
//     }

//     // Initialize the matrix elements with random integers 
//     for (int i = 0; i < n; i++) {
//         matrix[i] = (float*)malloc(n * sizeof(float*));
//         if (matrix[i] == NULL) {
//             return NULL;
//         }

//         // Initialize the matrix elements with random integers between 1 and 100 (adjust as needed)
//         for (int j = 0; j < n; j++) {
//             matrix[i][j] = rand() % 100; // Generates random integers between 1 and 100
//         }
//     }   
//     return matrix; 
// }


// int main() {

//     // Test Case for input size testing 
//     int n1 = 2048; 
//     float** A1 = initializeMatrix(n1);
//     float** B1 = initializeMatrix(n1);

//     clock_t start_time, end_time;
//     start_time = clock(); // Record the start time
//     float** block_output1 = matmul_multithread(A1, B1, n1, n1, n1, n1);
//     end_time = clock(); // Record the end time

//     double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
//     printf("Time taken by function: %f seconds\n", time_taken);

//     free(A1);
//     free(B1);
//     free(block_output1);
// }


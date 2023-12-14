#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    float *values; 
    int *row_idx_array; 
    int *col_idx_array; 
} CSRFormat;

typedef struct {
    float **A;
    float **B;
    float **result;
    int A_rows, A_cols, B_rows, B_cols;
} ThreadData;

float **matmul(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols);
float **matmul_blocking(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols);
CSRFormat generate_csr_arrays(float **matrix, int num_rows, int num_cols);
float **matmul_sparse(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols);
float **matmul_multithread(float **A, float **B, int A_rows, int A_cols, int B_rows, int B_cols);
void *multiply(void *arg);


#endif /* MATRIX_OPS_H */
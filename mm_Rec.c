#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Allocate memory for a matrix
int** allocate_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matrix[i] = (int*)malloc(n * sizeof(int));
    return matrix;
}

// Free matrix memory
void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

// Add two matrices
void add_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Subtract two matrices
void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// Standard matrix multiplication (O(n^3))
void normal_multiply(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Strassen’s Algorithm
void strassen(int** A, int** B, int** C, int n) {
    if (n <= 2) {  
        normal_multiply(A, B, C, n); // base case
        return;
    }

    int k = n / 2;

    // Allocate submatrices
    int** A11 = allocate_matrix(k); int** A12 = allocate_matrix(k);
    int** A21 = allocate_matrix(k); int** A22 = allocate_matrix(k);
    int** B11 = allocate_matrix(k); int** B12 = allocate_matrix(k);
    int** B21 = allocate_matrix(k); int** B22 = allocate_matrix(k);
    int** C11 = allocate_matrix(k); int** C12 = allocate_matrix(k);
    int** C21 = allocate_matrix(k); int** C22 = allocate_matrix(k);

    // Temporary matrices
    int** M1 = allocate_matrix(k); int** M2 = allocate_matrix(k);
    int** M3 = allocate_matrix(k); int** M4 = allocate_matrix(k);
    int** M5 = allocate_matrix(k); int** M6 = allocate_matrix(k);
    int** M7 = allocate_matrix(k);
    int** T1 = allocate_matrix(k); int** T2 = allocate_matrix(k);

    // Split matrices into submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Strassen’s 7 multiplications
    add_matrix(A11, A22, T1, k);  add_matrix(B11, B22, T2, k);  strassen(T1, T2, M1, k);
    add_matrix(A21, A22, T1, k);  strassen(T1, B11, M2, k);
    sub_matrix(B12, B22, T2, k);  strassen(A11, T2, M3, k);
    sub_matrix(B21, B11, T2, k);  strassen(A22, T2, M4, k);
    add_matrix(A11, A12, T1, k);  strassen(T1, B22, M5, k);
    sub_matrix(A21, A11, T1, k);  add_matrix(B11, B12, T2, k);  strassen(T1, T2, M6, k);
    sub_matrix(A12, A22, T1, k);  add_matrix(B21, B22, T2, k);  strassen(T1, T2, M7, k);

    // Compute C11, C12, C21, C22
    add_matrix(M1, M4, T1, k);  sub_matrix(T1, M5, T2, k);  add_matrix(T2, M7, C11, k);
    add_matrix(M3, M5, C12, k);
    add_matrix(M2, M4, C21, k);
    sub_matrix(M1, M2, T1, k);  add_matrix(T1, M3, T2, k);  add_matrix(T2, M6, C22, k);

    // Combine submatrices into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free memory
    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(M1, k); free_matrix(M2, k); free_matrix(M3, k); free_matrix(M4, k);
    free_matrix(M5, k); free_matrix(M6, k); free_matrix(M7, k);
    free_matrix(T1, k); free_matrix(T2, k);
}

int main() {
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    srand(time(NULL));

    FILE *fp = fopen("Data.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int** A = allocate_matrix(n);
        int** B = allocate_matrix(n);
        int** C = allocate_matrix(n);

        // Fill A and B with random numbers
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }

        clock_t start, end;
        
        // Standard multiplication
        start = clock();
        normal_multiply(A, B, C, n);
        end = clock();
        double time_normal = (double)(end - start) / CLOCKS_PER_SEC;

        // Strassen multiplication
        start = clock();
        strassen(A, B, C, n);
        end = clock();
        double time_strassen = (double)(end - start) / CLOCKS_PER_SEC;

        printf("   Normal multiply:   %f sec\n", time_normal);
        printf("   Strassen multiply: %f sec\n", time_strassen);
        printf("--------------------------\n");

        // Write results into file (clean format)
        fprintf(fp, "%d %.6f %.6f\n", n, time_normal, time_strassen);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    fclose(fp);
    printf("Results stored in Data.txt\n");

    return 0;
}

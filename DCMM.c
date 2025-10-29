#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Standard matrix multiplication
void multiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Allocate 2D array dynamically
int **allocate_matrix(int n) {
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        mat[i] = (int *)malloc(n * sizeof(int));
    }
    return mat;
}

// Free 2D array
void free_matrix(int **mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Fill matrix with random numbers
void fill_matrix(int **mat, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mat[i][j] = rand() % 10; // values 0–9
}

int main() {
    srand(time(NULL));

    int sizes[] = {8, 16, 32, 64, 128, 256, 512};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    FILE *fp = fopen("Data.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        // Allocate matrices
        int **A = allocate_matrix(n);
        int **B = allocate_matrix(n);
        int **C = allocate_matrix(n);

        // Fill A and B with random numbers
        fill_matrix(A, n);
        fill_matrix(B, n);

        // Start timing
        clock_t start = clock();
        multiply(A, B, C, n);
        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d => %.6f\n", n, elapsed);
        fprintf(fp, "%d %.6f\n", n, elapsed);

        // Free memory
        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(C, n);
    }

    fclose(fp);

    printf("Results stored in Data.txt\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void multiplyMatrices(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int sizes[] = { 8, 16,32, 64,128,256,512,1024}; 
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(time(NULL)); 


    FILE *fp = fopen("results.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "Size Time(seconds)\n"); 

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        
       
        int (*A)[n] = malloc(sizeof(int[n][n]));
        int (*B)[n] = malloc(sizeof(int[n][n]));
        int (*C)[n] = malloc(sizeof(int[n][n]));

     
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }
        }

        clock_t start = clock();
        multiplyMatrices(n, A, B, C);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf(" %dx%d => : %.6f \n", n, n, time_taken);
        fprintf(fp, "%d %.6f\n", n, time_taken);

      
        free(A);
        free(B);
        free(C);
    }

    fclose(fp);
    printf("Results stored in results.txt\n");

    return 0;
}

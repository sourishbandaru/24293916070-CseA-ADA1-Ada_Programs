#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Binary search with artificial delay
int binary_search(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Artificial delay loop (does nothing)
        for (volatile int j = 0; j < 1000; j++);

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

void generateRandomArray(int array[], int size){
    for(int i = 0; i < size; i++)
        array[i] = rand() % 100000;
}

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int input_size[8] = {10, 50, 100, 1000, 3000, 5000, 7000, 10000};

    // Open file to write results
    FILE *fp = fopen("binary_search_results.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "size,avg_time\n"); // CSV header

    for(int i = 0; i < 8; i++){
        int size = input_size[i];
        int array[size];

        generateRandomArray(array, size);
        qsort(array, size, sizeof(int), cmpfunc);

        int target = array[size-1] + 1; // worst-case: not in array

        double total_time = 0;
        int iterations = 100000; // batch size

        clock_t start = clock();
        for(int iter = 0; iter < iterations; iter++) {
            binary_search(array, size, target);
        }
        clock_t end = clock();

        total_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        double avg_time = total_time / iterations;

        printf("Size: %d, Avg time: %lf seconds\n", size, avg_time);
        fprintf(fp, "%d,%lf\n", size, avg_time);
    }

    fclose(fp);
    printf("Results saved to binary_search_results.txt\n");
    return 0;
}
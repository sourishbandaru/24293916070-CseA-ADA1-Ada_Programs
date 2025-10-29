#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int weight;
    int value;
} Item;

int zeroOneKnapsack(int W, Item items[], int n) {
    int **dp = (int**)malloc((n+1) * sizeof(int*));
    for(int i=0; i<=n; i++)
        dp[i] = (int*)malloc((W+1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i-1].weight <= w)
                dp[i][w] = (items[i-1].value + dp[i-1][w-items[i-1].weight] > dp[i-1][w]) 
                           ? items[i-1].value + dp[i-1][w-items[i-1].weight] 
                           : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }

    int result = dp[n][W];

    for(int i=0; i<=n; i++) free(dp[i]);
    free(dp);

    return result;
}

int main() {
    int n_values[11] = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000};
    FILE *fp = fopen("zeroone_results.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));
    fprintf(fp, "n\tW\tDPTime(ms)\n");

    for (int t = 0; t < 11; t++) {
        int n = n_values[t];

        int capacity = n / 10;
        if (capacity < 1) capacity = 1;

        Item *items = malloc(n * sizeof(Item));

        for (int i = 0; i < n; i++) {
            items[i].value = rand() % 100 + 1;
            items[i].weight = rand() % capacity + 1;
        }

        clock_t start = clock();
        zeroOneKnapsack(capacity, items, n);
        clock_t end = clock();

        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

        printf("n=%d W=%d  DP=%.2f ms\n", n, capacity, timeTaken);
        fprintf(fp, "%d\t%d\t%.2f\n", n, capacity, timeTaken);

        free(items);
    }

    fclose(fp);
    printf("\n0/1 knapsack results saved in zeroone_results.txt\n");
    return 0;
}

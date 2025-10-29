#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int weight;
    int value;
    float ratio;
} Item;

int cmp(const void *a, const void *b) {
    Item *i1 = (Item*)a;
    Item *i2 = (Item*)b;
    if (i2->ratio > i1->ratio) return 1;
    else if (i2->ratio < i1->ratio) return -1;
    else return 0;
}

float fractionalKnapsack(int W, Item items[], int n) {
    qsort(items, n, sizeof(Item), cmp);
    int curWeight = 0;
    float finalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (curWeight + items[i].weight <= W) {
            curWeight += items[i].weight;
            finalValue += items[i].value;
        } else {
            int remain = W - curWeight;
            finalValue += items[i].value * ((float)remain / items[i].weight);
            break;
        }
    }
    return finalValue;
}

int main() {
    int n_values[11] = {100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000,1100000};
    FILE *fp = fopen("fractional_results.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(NULL));
    int capacity = 5000;

    fprintf(fp, "n\tGreedyTime(ms)\n");

    for (int t = 0; t < 11; t++) {
        int n = n_values[t];
        Item *items = malloc(n * sizeof(Item));

        for (int i = 0; i < n; i++) {
            items[i].value = rand() % 100 + 1;
            items[i].weight = rand() % 50 + 1;
            items[i].ratio = (float)items[i].value / items[i].weight;
        }

        clock_t start = clock();
        fractionalKnapsack(capacity, items, n);
        clock_t end = clock();

        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

        printf("n=%d  Greedy=%.2f ms\n", n, timeTaken);
        fprintf(fp, "%d\t%.2f\n", n, timeTaken);

        free(items);
    }

    fclose(fp);
    printf("\nFractional knapsack results saved in fractional_results.txt\n");
    return 0;
}

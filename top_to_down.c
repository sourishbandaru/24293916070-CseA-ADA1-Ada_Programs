#include <stdio.h>
#include <time.h>
#define MAX_N 100

long long memo[MAX_N];

long long fib_topdown(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    memo[n] = fib_topdown(n-1) + fib_topdown(n-2);
    return memo[n];
}

int main() {
    int n_values[] = {5, 10, 15, 20, 25, 30, 35, 40};
    int num_values = sizeof(n_values)/sizeof(n_values[0]);

    FILE *fp = fopen("topdown.csv", "w");
    fprintf(fp, "n,time_ms\n");

    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];
        int repeats = 10000;

        clock_t start = clock();
        for (int j = 0; j < repeats; j++) {
            for (int k = 0; k <= n; k++) memo[k] = -1;
            fib_topdown(n);
        }
        clock_t end = clock();
        double time_ms = ((double)(end - start)/CLOCKS_PER_SEC)*1000.0 / repeats;
        fprintf(fp, "%d,%.8f\n", n, time_ms);
    }

    fclose(fp);
    return 0;
}

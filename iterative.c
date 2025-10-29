#include <stdio.h>
#include <time.h>

long long fib_iterative(int n) {
    if (n <= 1) return n;
    long long prev2 = 0, prev1 = 1, curr = 0;
    for (int i = 2; i <= n; i++) {
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

int main() {
    int n_values[] = {5, 10, 15, 20, 25, 30, 35, 40};
    int num_values = sizeof(n_values) / sizeof(n_values[0]);
    FILE *fp = fopen("iterative.csv", "w");
    fprintf(fp, "n,time_ms\n");

    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];
        int repeats = 100000; // fast, so high repeats
        clock_t start = clock();
        for (int j = 0; j < repeats; j++) {
            fib_iterative(n);
        }
        clock_t end = clock();
        double time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0 / repeats;
        fprintf(fp, "%d,%.8f\n", n, time_ms);
    }

    fclose(fp);
    return 0;
}

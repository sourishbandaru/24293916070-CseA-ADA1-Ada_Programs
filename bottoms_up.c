#include <stdio.h>
#include <time.h>

long long fib_bottomup(int n) {
    if (n <= 1) return n;
    long long dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int main() {
    int n_values[] = {5, 10, 15, 20, 25, 30, 35, 40};
    int num_values = sizeof(n_values)/sizeof(n_values[0]);

    FILE *fp = fopen("bottomup.csv", "w");
    fprintf(fp, "n,time_ms\n");

    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];
        int repeats = 100000; // repeat many times
        clock_t start = clock();
        for (int j = 0; j < repeats; j++) {
            fib_bottomup(n);
        }
        clock_t end = clock();
        double time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0 / repeats;
        fprintf(fp, "%d,%.8f\n", n, time_ms);
    }

    fclose(fp);
    return 0;
}

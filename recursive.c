#include <stdio.h>
#include <time.h>

long long fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main() {
    // Use smaller n for recursive to keep times reasonable
    int n_values[] = {5, 10, 15, 20}; 
    int num_values = sizeof(n_values)/sizeof(n_values[0]);

    FILE *fp = fopen("recursive.csv", "w");
    fprintf(fp, "n,time_ms\n");

    for (int i = 0; i < num_values; i++) {
        int n = n_values[i];
        int repeats = 3; // very small repeat because recursive is slow

        clock_t start = clock();
        for (int j = 0; j < repeats; j++) {
            fib_recursive(n);
        }
        clock_t end = clock();

        double time_ms = ((double)(end - start)/CLOCKS_PER_SEC)*1000.0 / repeats;
        fprintf(fp, "%d,%.5f\n", n, time_ms);
    }

    fclose(fp);
    return 0;
}

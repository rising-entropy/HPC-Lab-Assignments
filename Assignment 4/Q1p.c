// Fibonacci Series in Parallel using DP
#include <omp.h>
#include <stdio.h>
#include<stdlib.h>

//We build our DP Array using Recursion

long long fib(long long  n, long long dp[]){
    long long x,y;
    if(n<=1)
        return n;
    if(dp[n]!=0){
        return dp[n];
    }
    # pragma omp task shared(x,dp)
    {
        x = fib(n-1, dp);
    }
    # pragma omp task shared(y,dp)
    {
        y = fib(n-2, dp);
    }

    // wait till both processes are complete
    #pragma omp taskwait
    dp[n] = x + y;
    return x+y;
}

int main() {
    long long n, f;

    printf("\nFibonaci Numbers\n");
    printf("Enter n: ");
    scanf("%d", &n);

    double start, end, duration;
    
    long long* dp = (long long*)malloc((n+1) * sizeof(long long));
    for (long long i = 0; i <= n; i++)
    dp[i] = 0;

    start = omp_get_wtime();

    # pragma omp parallel
    {
        # pragma omp single
        {
            f = fib(n, dp);
        }
    }

    end = omp_get_wtime();
    duration = end - start;

    printf("fib(%lld) = %lld\n\n", n, f);
    printf("Time taken: %lf %15.15lf", duration, duration);

    return 0;
}

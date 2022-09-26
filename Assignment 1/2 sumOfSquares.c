#include <stdio.h>
#include <omp.h>

double sequential(int n){
    printf("Sequential:\n");
    long long sum = 0;
    double start, end;
    start = omp_get_wtime();
    for(int i=1; i<=n; i++){
        sum += i*i;
    }
    end = omp_get_wtime();
    printf("Sum is %lld", sum);
    return end - start;
}

double parallel(int n, int threadCount){
    printf("Parallel:\n");
    omp_set_num_threads(threadCount);
    long long sum = 0;
    double start, end;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+ : sum)
    for(int i=1; i<=n; i++){
        sum += i*i;
    }
    end = omp_get_wtime();
    printf("Sum is %lld", sum);
    return end - start;
}

int main(void)
{
    printf("Maximum Number of Threads - %d\n", omp_get_max_threads());
    
    int threadCount;
    printf("Enter Number of Threads: ");
    scanf("%d", &threadCount);

    double sequentialTime, parallelTime;

    int n;
    printf("\nEnter 'n': ");
    scanf("%d", &n);

    sequentialTime = sequential(n);
    printf("\n");
    parallelTime = parallel(n, threadCount);

    printf("\nSequential Time - %lf\n", sequentialTime);
    printf("Parallel Time - %lf\n", parallelTime);
    printf("Speedup - %lf\n", sequentialTime/parallelTime);
    
    return 0;
}

//Enter 'n': 1048576
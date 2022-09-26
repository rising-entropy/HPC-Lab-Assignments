#include <stdio.h>
#include <omp.h>

double sequential(int n){
    printf("Sequential:\n");
    double start, end;
    start = omp_get_wtime();
    for(int i=0; i<n; i++){
        printf("Hello, world.\n");
    }
    end = omp_get_wtime();
    return end - start;
}

double parallel(int n){
    printf("Parallel:\n");
    double start, end;
    // Set those number of Threads
    omp_set_num_threads(n);
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Hello, world. %d\n", id);
    }
    end = omp_get_wtime();
    return end - start;
}

int main(void)
{
    printf("Maximum Number of Threads - %d\n", omp_get_max_threads());
    
    int n;
    printf("Enter Number of Threads: ");
    scanf("%d", &n);

    double sequentialTime, parallelTime;

    sequentialTime = sequential(n);
    printf("\n");
    parallelTime = parallel(n);

    printf("\nSequential Time - %lf\n", sequentialTime);
    printf("Parallel Time - %lf\n", parallelTime);
    printf("Speedup - %lf\n", sequentialTime/parallelTime);
    
    return 0;
}

//Enter Number of Threads: 16 
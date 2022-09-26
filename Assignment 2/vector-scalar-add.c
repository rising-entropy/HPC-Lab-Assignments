#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
# define N 1048576

int main(void)
{
    printf("Maximum Number of Threads - %d\n", omp_get_max_threads());
    
    int threadCount;
    printf("Enter Number of Threads: ");
    scanf("%d", &threadCount);

    omp_set_num_threads(threadCount);

    int k;
    printf("\nEnter scalar number: ");
    scanf("%d", &k);

    int* v1;
    v1 = (int *)malloc((N) * sizeof(int));

    int* op1;
    op1 = (int *)malloc((N) * sizeof(int));
    int* op2;
    op2 = (int *)malloc((N) * sizeof(int));

    FILE * fp;
    char * line = NULL;
    size_t len = 0, read;
    fp = fopen("v1.txt", "r");
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        v1[i] = (int)line;
        i++;
    }

    double sequentialTime, parallelTime;

    // Sequential
    printf("Sequential:\n");
    long long sum = 0;
    double start, end;
    start = omp_get_wtime();
    for(int i=0; i<N; i++){
        op1[i] = v1[i] + k;
    }
    end = omp_get_wtime();
    sequentialTime = end - start;
    printf("Sequential Task Computed!\n");

    //Parallel
    sum=0;
    start = omp_get_wtime();
    # pragma omp parallel for private(k)
    for(int i=0; i<N; i++){
        op2[i] = v1[i] + k;
    }
    end = omp_get_wtime();
    parallelTime = end - start;
    printf("Parallel Task Computed!\n");


    printf("\nSequential Time - %lf\n", sequentialTime);
    printf("Parallel Time - %lf\n", parallelTime);
    printf("Speedup - %lf\n", sequentialTime/parallelTime);
    
    return 0;
}
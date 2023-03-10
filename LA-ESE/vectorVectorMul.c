// 2019BTECS00058 Devang K

#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
#define N 5242880

int main(void){
    double start_s, end_s;
    double start_p, end_p;

    int n;
    printf("Enter number of threads: ");
    scanf("%d", &n);

    omp_set_num_threads(n);

    int* a;
    int* b;
    int c = 0;

    a = (int*)malloc(N*sizeof(int));
    b = (int*)malloc(N*sizeof(int));

    // set the values
    for(int i=0; i<N; i++){
        a[i] = 1;
        b[i] = 2;
    }

    c = 0;

    // We start with Sequential
    start_s = omp_get_wtime();
    for(int i=0; i<N; i++){
        c += a[i]*b[i];
    }
    end_s = omp_get_wtime();

    printf("\nSeq Ans - %d", c);

    // Reset the value of c
    c = 0;
    
    // Parallel
    start_p = omp_get_wtime();
    #pragma omp parallel for reduction(+: c)
    for(int i=0; i<N; i++){
        c += a[i]*b[i];
    }
    end_p = omp_get_wtime();

    printf("\nPar Ans - %d", c);

    printf("\nFor the program with %d threads, we find:\n", n);
    printf("Sequential Time: %lf\n", end_s-start_s);
    printf("Parallel Time: %lf\n", end_p-start_p);
    printf("Speedup: %lf\n", (end_s-start_s)/(end_p-start_p));
}
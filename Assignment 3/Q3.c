#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000

double sequentialAdd(int A[], int C[], int k){
    double start, end;
    start = omp_get_wtime();
    for(int i=0; i<N; i++){
        C[i] = A[i] + k;
    }
    end = omp_get_wtime();
    return end - start;
}

double parallelStaticAdd(int chunks, int A[], int C[], int k){
    double start, end;
    start = omp_get_wtime();
    # pragma omp parallel for schedule(static, chunks)
    for(int i=0; i<N; i++){
        C[i] = A[i] + k;
    }
    end = omp_get_wtime();
    return end - start;
}

double parallelDynamicAdd(int chunks, int A[], int C[], int k){
    double start, end;
    start = omp_get_wtime();
    # pragma omp parallel for schedule(dynamic, chunks)
    for(int i=0; i<N; i++){
        C[i] = A[i] + k;
    }
    end = omp_get_wtime();
    return end - start;
}

int main(){
    int* A = (int*)malloc(N * sizeof(int));
    int* C = (int*)malloc(N * sizeof(int));

    int k;
    printf("\nVector Scalar Addition:\n");
    printf("Enter Scalar to Add - ");
    scanf("%d", &k);

    for(int i=0; i<N; i++){
        A[i] = rand();
    }

    double sequentialTime = sequentialAdd(A, C, k);

    // static chunks
    double parStatic2 = parallelStaticAdd(2, A, C, k);
    double parStatic4 = parallelStaticAdd(4, A, C, k);
    double parStatic5 = parallelStaticAdd(5, A, C, k);
    double parStatic10 = parallelStaticAdd(10, A, C, k);
    double parStatic20 = parallelStaticAdd(20, A, C, k);

    //dynamic chunks
    double parDynamic2 = parallelDynamicAdd(2, A, C, k);
    double parDynamic4 = parallelDynamicAdd(4, A, C, k);
    double parDynamic5 = parallelDynamicAdd(5, A, C, k);
    double parDynamic10 = parallelDynamicAdd(10, A, C, k);
    double parDynamic20 = parallelDynamicAdd(20, A, C, k);


    printf("\nSequential Time - %lf\n", sequentialTime);

    printf("Static Scheduling\n");
    printf("2 Chunks: Time - %lf, Speedup - %lf\n", parStatic2, sequentialTime/parStatic2);
    printf("4 Chunks: Time - %lf, Speedup - %lf\n", parStatic4, sequentialTime/parStatic4);
    printf("5 Chunks: Time - %lf, Speedup - %lf\n", parStatic5, sequentialTime/parStatic5);
    printf("10 Chunks: Time - %lf, Speedup - %lf\n", parStatic10, sequentialTime/parStatic10);
    printf("20 Chunks: Time - %lf, Speedup - %lf\n", parStatic20, sequentialTime/parStatic20);

    printf("\nDynamic Scheduling\n");
    printf("2 Chunks: Time - %lf, Speedup - %lf\n", parDynamic2, sequentialTime/parDynamic2);
    printf("4 Chunks: Time - %lf, Speedup - %lf\n", parDynamic4, sequentialTime/parDynamic4);
    printf("5 Chunks: Time - %lf, Speedup - %lf\n", parDynamic5, sequentialTime/parDynamic5);
    printf("10 Chunks: Time - %lf, Speedup - %lf\n", parDynamic10, sequentialTime/parDynamic10);
    printf("20 Chunks: Time - %lf, Speedup - %lf\n", parDynamic20, sequentialTime/parDynamic20);
    printf("\n");
    return 0;
}

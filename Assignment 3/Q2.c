/*
Q2 Write OpenMP code for two 2D Matrix addition, vary the size of your matrices
from 250, 500, 750, 1000, and 2000 and measure the runtime with one thread (Use
functions in C in calculate the execution time or use GPROF)
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double sequentialAdd(int** A, int** B, int** C, int n){
    double start, end;
    start = omp_get_wtime();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    end = omp_get_wtime();

    return end - start;
}

double add(int threads, int** A, int** B, int** C, int n) {
  int i, j;
  double start, end;

  omp_set_num_threads(threads);

  start = omp_get_wtime();

#pragma omp parallel for private(j)
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      C[i][j] = A[i][j] + B[i][j];

  end = omp_get_wtime();
  return end - start;
}

int main() {
  int i, j, n;
  printf("\nMatrix-Matrix Addition\n");
  printf("Enter the Matrix Size: ");
  scanf("%d", &n);
  
  int** A = (int**)malloc(n * sizeof(int*));
  int** B = (int**)malloc(n * sizeof(int*));
  int** C = (int**)malloc(n * sizeof(int*));

  for (i = 0; i < n; i++) {
    A[i] = (int*)malloc(n * sizeof(int));
    B[i] = (int*)malloc(n * sizeof(int));
    C[i] = (int*)malloc(n * sizeof(int));
  }

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      A[i][j] = rand();
      B[i][j] = rand();
    }

  double sequentialTime = sequentialAdd(A, B, C, n);

  double parTime2 = add(2, A, B, C, n);
  double parTime4 = add(4, A, B, C, n);
  double parTime8 = add(8, A, B, C, n);
  double parTime16 = add(16, A, B, C, n);

  printf("\n");
  printf("Sequential Time: %lf\n\n", sequentialTime);

  printf("Parallel Time - 2 Threads: %lf\n", parTime2);
  printf("Speedup - 2 Threads: %lf\n\n", sequentialTime/parTime2);

  printf("Parallel Time - 4 Threads: %lf\n", parTime4);
  printf("Speedup - 4 Threads: %lf\n\n", sequentialTime/parTime4);

  printf("Parallel Time - 8 Threads: %lf\n", parTime8);
  printf("Speedup - 8 Threads: %lf\n\n", sequentialTime/parTime8);

  printf("Parallel Time - 16 Threads: %lf\n", parTime16);
  printf("Speedup - 16 Threads: %lf\n\n", sequentialTime/parTime16);
  printf("\n");

  for (i = 0; i < n; i++) {
    free(A[i]);
    free(B[i]);
    free(C[i]);
  }

  free(A);
  free(B);
  free(C);

  return 0;
}

// C Program to find the minimum scalar product of two vectors (dot product)
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

// for parallel, we change all for loops into parallel

void sort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++){
    #pragma omp for
    for (j = 0; j < n - i - 1; j++)
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
  } 
}

void sort_des(int arr[], int n) {
  int i, j;
  for (i = 0; i < n; ++i) {
    #pragma omp for
    for (j = i + 1; j < n; ++j) {
      if (arr[i] < arr[j]) {
        int a = arr[i];
        arr[i] = arr[j];
        arr[j] = a;
      }
    }
  }
}

int main() {
  // fill the code;

    printf("Maximum Number of Threads - %d\n", omp_get_max_threads());
    
    int threadCount;
    printf("Enter Number of Threads: ");
    scanf("%d", &threadCount);
    omp_set_num_threads(threadCount);

  int i, n = 100000;
  int* arr1 = (int*)malloc(n * sizeof(int));
  int* arr2 = (int*)malloc(n * sizeof(int));

  FILE * fp;
    char * line = NULL;
    size_t len = 0, read;
    fp = fopen("Q1a.txt", "r");
    int ii = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        arr1[ii] = (int)line;
        ii++;
    }

    FILE * fp2;
    char * line2 = NULL;
    size_t len2 = 0, read2;
    fp2 = fopen("Q1b.txt", "r");
    ii = 0;
    while ((read2 = getline(&line2, &len2, fp2)) != -1) {
        arr2[ii] = (int)line2;
        ii++;
    }

  int temp = 0;
  for (i = 0; i < n; i++) {
    arr1[i] = temp;
    arr2[i] = temp * 2;
    temp = (temp + 1) % 100;
  }

  double start, end, duration;
  start = omp_get_wtime();
  long long sum = 0;
  #pragma omp parallel
  {
    sort(arr1, n);
    sort_des(arr2, n);
    # pragma omp for reduction(+:sum)
    for (i = 0; i < n; i++) {
        sum += (arr1[i] * arr2[i]);
    }
  }


  end = omp_get_wtime();
  duration = end - start;

  printf("\nParallel:\n");
  printf("Sum: %d\n", sum);
  printf("Time taken: %lf\n", duration);

  return 0;
}

/*
Sequential:
Sum: 323400000
Time taken: 26.435000

Parallel 16:
Sum: 323400000
Time taken: 25.917000

Parallel 8:
Sum: 323400000
Time taken: 24.508000

Parallel 4:
Sum: 323400000
Time taken: 28.057000
*/
#include <omp.h>
#include <stdio.h>

// Say we wish to call independent loops A and B with 5 iterations

void withoutNowait(){
    printf("Without nowait:\n");
    # pragma omp parallel
    {
        # pragma omp for
        for(int i=1; i<=5; i++){
            printf("A - %d\n", i);
        }
        # pragma omp for
        for(int i=1; i<=5; i++){
            printf("B - %d\n", i);
        }
    }
    printf("\n");
}

void withNowait(){
    printf("With nowait:\n");
    # pragma omp parallel
    {
        # pragma omp for nowait
        for(int i=1; i<=5; i++){
            printf("A - %d\n", i);
        }
        # pragma omp for
        for(int i=1; i<=5; i++){
            printf("B - %d\n", i);
        }
    }
    printf("\n");
}


int main(){

    omp_set_num_threads(5);

    // without nowait
    withoutNowait();
    //with nowait
    withNowait();

    return 0;
}
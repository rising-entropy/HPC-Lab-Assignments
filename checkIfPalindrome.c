#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    char a[] = {'a', 'a', 'b', 'a', 'a'};
    int n = 5;
    int theIterations = n/2;
    if(theIterations%2 == 1){
        theIterations++;
    }
    int x = 0;
    # pragma omp parallel
    {
        #pragma omp for reduction(+:x)
        for(int i=0; i<theIterations; i++){
            if(a[i]!=a[n-1-i]){
                x++;
            }
        }
    }

    if(x==0){
        printf("Palindrome\n");
    }else{
        printf("Not Palindrome\n");
    }
    return 0;
}

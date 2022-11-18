#include<stdio.h>
#include <stdlib.h>
#include<math.h>

__global__ void computePrefixSum(double* arr, double *prefixArraySums, int maxElementsInArray, int N){
    
    __shared__ int Arr[320000];
    for(int i=0; i<320000; i++){
        Arr[i] = arr[i];
    }
    
    
    int threadIndex = threadIdx.x;
    int indexToStartFrom = threadIndex * maxElementsInArray;
    int indexTillEnd;
    if((threadIndex+1)*maxElementsInArray -1 >= N){
        // indexTillEnd = N-1; //check later
        indexTillEnd = N;
    }
    else{
        indexTillEnd = (threadIndex+1)*maxElementsInArray -1;
    }
    
    double sum = 0;
    for(int i=indexToStartFrom; i<=indexTillEnd; i++){
        sum += Arr[i];
        arr[i] = sum;
    }
    prefixArraySums[threadIndex] = sum;
}

__global__ void computeFinalSum(double* arr, double *prefixArraySums, int maxElementsInArray, int N){
    int threadIndex = threadIdx.x;
    int indexToStartFrom = threadIndex * maxElementsInArray;
    int indexTillEnd;
    if((threadIndex+1)*maxElementsInArray -1 >= N){
        indexTillEnd = N;
    }
    else{
        indexTillEnd = (threadIndex+1)*maxElementsInArray -1;
    }
    double numberToAdd = prefixArraySums[threadIndex];
    for(int i=indexToStartFrom; i<=indexTillEnd; i++){
        arr[i] += numberToAdd;
    }
}

int main()
{
    char line[100] = {0};
    int N = 320000;

    // divide into 32 sub-arrays
    int totalNumberOfSubArrays = 32;
    double doubleType;
    
    size_t size = N * sizeof(double);
    size_t size2 = totalNumberOfSubArrays * sizeof(double);
    
    double *arr;
    cudaMallocManaged(&arr, size);
    
    double *prefixArraySums;
    cudaMallocManaged(&prefixArraySums, size2);
    int maxElementsInArray = N/totalNumberOfSubArrays;
    if(N%totalNumberOfSubArrays>0){
        maxElementsInArray++;
    }
    
    for(int i=0; i<N; i++){
        arr[i] = 1;
    }
    
    computePrefixSum<<<1, totalNumberOfSubArrays>>>(arr, prefixArraySums, maxElementsInArray, N);
    
    cudaDeviceSynchronize();
    
    // prefix sum
    double prefSumArray = 0;
    for(int j=0; j<totalNumberOfSubArrays; j++){
        double temp = prefSumArray;
        prefSumArray += prefixArraySums[j];
        prefixArraySums[j] = temp;
    }
    
    computeFinalSum<<<1, totalNumberOfSubArrays>>>(arr, prefixArraySums, maxElementsInArray, N);
    cudaDeviceSynchronize();
    cudaFree(arr);  
    cudaFree(prefixArraySums);
}
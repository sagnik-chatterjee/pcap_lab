%%cu
#include <stdio.h>
#include <stdlib.h>

/**
Author: Sagnik Chatterjee
*/

__global__ void add_vectors(int *a,int *b ,int *c){
    int i =blockIdx.x;
    c[i] = a[i] +b[i];
}

void printVector(int *a, int n){
    for(int i=0;i<n;i++){
        printf("%d," ,a[i]);
    }
    printf("\n");
}

int main()
{
 int *d_a, *d_b, *d_c;
 int n = 10;
 int a[n] = {1,2,3,4,5,6,7,8,9,10};
 int b[n] = {10,9,8,7,6,5,4,3,2,1};
 int c[n];
 printVector(a, n);
 printVector(b, n);
 cudaMalloc((void **)&d_a, n * sizeof(int));
 cudaMalloc((void **)&d_b, n * sizeof(int));
 cudaMalloc((void **)&d_c, n * sizeof(int));
 cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
 cudaMemcpy(d_b, b, n * sizeof(int), cudaMemcpyHostToDevice);
 add_vectors<<<n, 1>>>(d_a, d_b, d_c);
 cudaMemcpy(c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);
 printVector(c, n);
 cudaFree(d_a);
 cudaFree(d_b);
 cudaFree(d_c);
}
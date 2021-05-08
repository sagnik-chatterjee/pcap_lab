%%cu
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
/**
Author: Sagnik Chatterjee
*/

__global__ void sum256Block(int *a, int *b, int *c, int n)
{
 int i = (blockDim.x * blockIdx.x) + threadIdx.x;
 if (i < n)
 {
 c[i] = a[i] + b[i];
  }
}
void printVector(int *a, int n)
{
 for (int i = 0; i < n; i++)
 {
 printf("%d, ", a[i]);
 }
 printf("\n");
}
int main()
{
 int *d_a, *d_b, *d_c;
 int n = 10;
 int a[n] = {1,2,3,4,5,6,7,8,9,10};
 int b[n] = {11,12,13,14,15,16,17,18,19,20};
 int c[n];
 printVector(a, n);
 printVector(b, n);
 cudaMalloc((void **)&d_a, n * sizeof(int));
 cudaMalloc((void **)&d_b, n * sizeof(int));
 cudaMalloc((void **)&d_c, n * sizeof(int));
 cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
 cudaMemcpy(d_b, b, n * sizeof(int), cudaMemcpyHostToDevice);
 sum256Block<<<ceil(n / 256.0), 256>>>(d_a, d_b, d_c, n);
 cudaMemcpy(c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);
 for(int i=0;i<n;i++){
     printf("%d, ",c[i]);
 }
 cudaFree(d_a);
 cudaFree(d_b);
 cudaFree(d_c);
}

output:

%%cu
#include <stdio.h>
#include <stdlib.h>
/**
Author : Sagnik Chatterjee
*/

__global__ void addN(int *a, int *b, int *c)
{
 int i = threadIdx.x;
 c[i] = a[i] + b[i];
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
 int n = 5;
 int a[n] = {2,3,4,4,1};
 int b[n] = {5,4,3,1,2};
 int c[n];
 printVector(a, n);
 printVector(b, n);
 cudaMalloc((void **)&d_a, n * sizeof(int));
 cudaMalloc((void **)&d_b, n * sizeof(int));
 cudaMalloc((void **)&d_c, n * sizeof(int));
 cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
 cudaMemcpy(d_b, b, n * sizeof(int), cudaMemcpyHostToDevice);
 addN<<<1, n>>>(d_a, d_b, d_c);
 cudaMemcpy(c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);
 printVector(c, n);
 cudaFree(d_a);
 cudaFree(d_b);
 cudaFree(d_c);
}

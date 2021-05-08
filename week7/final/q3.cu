%%cu
#include <stdio.h>
#include <stdlib.h>
/**
Author: Sagnik Chatterjee
*/
__device__ void swap(int *a, int *b)
{
 int temp = *a;
 *a = *b;
 *b = temp;}
__global__ void oddEven(int *a, int n)
{
 int i = (blockDim.x * blockIdx.x) + threadIdx.x;
 if ((i % 2 == 1) && (i < n - 1))
 {
 if (a[i] > a[i + 1])
 {
 swap(&a[i], &a[i + 1]);
 }
 }
}
__global__ void evenOdd(int *a, int n)
{
 int i = (blockDim.x * blockIdx.x) + threadIdx.x;
 if ((i % 2 == 0) && (i < n - 1))
 {
 if (a[i] > a[i + 1])
 {
 swap(&a[i], &a[i + 1]);
 }
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
 int *d_a;
 int n = 10;
 int a[n] = {13, 10, 4, 7, 1, 4, 8, 0, 5, 6};
 printVector(a, n);
 cudaMalloc((void **)&d_a, n * sizeof(int));
 cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
 for (int i = 0; i <= n / 2; i++)
 {
 oddEven<<<ceil(n / 256.0), 256>>>(d_a, n);
 evenOdd<<<ceil(n / 256.0), 256>>>(d_a, n);
 }
 cudaMemcpy(a, d_a, n * sizeof(int), cudaMemcpyDeviceToHost);
 printVector(a, n);
 cudaFree(d_a);
}
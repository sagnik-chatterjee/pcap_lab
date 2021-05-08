%%cu
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
Author: Sagnik Chatterjee
*/

__global__ void parallel_kernel_pos(int *a, int n)
{
 int i = threadIdx.x;
 int data = a[i];
 int pos = 0;
 for (int j = 0; j < n; j++)
 {
 if (a[j] < data || (a[j] == data && j < i))
 pos++;
 }
 a[pos] = data;
}
void sort_array(int* h_arr, int n){
 int* d_arr = NULL;
 int size = n*sizeof(int);
 cudaError_t err = cudaSuccess;
 err = cudaMalloc((void **)&d_arr,size);
 if(err != cudaSuccess){
 printf("%s\n",cudaGetErrorString(err));
 exit(EXIT_FAILURE);
 }
 err = cudaMemcpy(d_arr,h_arr,size,cudaMemcpyHostToDevice);
 if(err != cudaSuccess){
 printf("%s\n",cudaGetErrorString(err));
 exit(EXIT_FAILURE);
 }
 parallel_kernel_pos<<<1,n>>>(d_arr,n);
 cudaMemcpy(h_arr,d_arr,size,cudaMemcpyDeviceToHost);
 cudaFree(d_arr);
}
int main(){
 int n = 10;
 int arr[n] ={33,36,27,15,43,35,36,42,49,21};
 for(int i=0;i<10;i++){
 printf("%d ",arr[i]);
 }
 //after sorting 
 sort_array(arr,n);
 printf("\n");
 for(int i=0;i<10;i++){
 printf("%d ",arr[i] );
 }
 return 0;
}
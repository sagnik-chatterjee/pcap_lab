%%cu
#include<stdio.h>
#include<stdlib.h>
#define Mask_Width 5
 
__global__ void Convolution_global(int *src, int *res, int *d_mask, int src_length){
    //taking the threadid
    int id =  blockIdx.x * blockDim.x + threadIdx.x;
    if(id < src_length){
        //declaring the start point
        int start = id - (Mask_Width / 2);
              int pval = 0;
    
       //Looping throught the array and multiplying with the mask array
        for(int i = 0; i < Mask_Width; i++){
            if((start + i) >= 0 && (start + i) < src_length){
               // printf("elements being multiplied are: src = %d mask = %d\n", src[start + i], d_mask[i]);
                pval += (src[start + i] * d_mask[i]);
               // printf("pval = %d\n", pval);
            }
        }
 
        //storing the answer in the resultant array
        res[id] = pval;        
      }
}
 
int main(){
    //Initializing the input array and the mask array
    int n = 8;
    int input [] = {8, 9, 3, 4, 5, 6, 11, 67};
    int mask[] = {7, 8, 9, 10, 11};
    int size_input = sizeof(int) * n;
    int size_mask = sizeof(int) * Mask_Width;
    int h_output[n];
 
    //Allocating space in the device
    int *d_input, *d_output, *d_mask_s;
    cudaMalloc((void **)&d_input, size_input);
    cudaMalloc((void **)&d_output, size_input);
    cudaMalloc((void **)&d_mask_s, size_mask);
 
    //Copying to the device memory
    cudaMemcpy(d_input, input, size_input, cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask_s, mask, size_mask, cudaMemcpyHostToDevice);
 
    //Creating event to calculate the time elapsed
    float et;
    cudaEvent_t start, stop;
    cudaEventCreate(&start); cudaEventCreate(&stop);
 
    //Calling the kernel along with time calculation
    int threads = 4;
    int blocks = (threads + n - 1) / threads;
    cudaEventRecord(start);
    Convolution_global<<<blocks, threads>>>(d_input, d_output, d_mask_s, n);
    cudaEventRecord(stop);
    cudaDeviceSynchronize();
    //Calculating the elapsed time of first kernel
    cudaEventElapsedTime(&et, start, stop);
    printf("\nThe time taken by global memory kernel to execute is: %f milliseconds\n", et);
 
    //Copying the shared memory result to host
    cudaMemcpy(h_output, d_output, size_input, cudaMemcpyDeviceToHost);
 
    //printing the result
    printf("\nPrinting the input array:\n");
    for(int i = 0; i < n; i++){
        printf("%d\t", input[i]);
    }
    printf("\n");
    printf("\nPrinting the mask array:\n");
    for(int i = 0; i < Mask_Width; i++){
        printf("%d\t", mask[i]);
    }
    printf("\n");
    printf("\nPrinting the resultant array:\n");
    for(int i = 0; i < n; i++){
        printf("%d\t", h_output[i]);
    }
 
    //Freeing the cuda resources
    cudaFree(d_input);
    cudaFree(d_output);
    cudaFree(d_mask_s);
 
}
 

%%cu

#include<stdio.h>
#include<stdlib.h>
#define Mask_Width 5
#define TILE_SIZE 4
 
__constant__ int d_mask[Mask_Width];
 
__global__ void Convolution_constant(int *src, int *res, int m_width, int src_length){
    //taking the threadid
    int id =  threadIdx.x;
    if(id < src_length){
        //declaring the start point
        int start = id - (m_width / 2);
        int pval = 0;
    
       //Looping throught the array and multiplying with the mask array
        for(int i = 0; i < m_width; i++){
            if((start + i) >= 0 && (start + i) < src_length){
               // printf("Elements being multiplied are: src = %d mask = %d\n", src[start + i], d_mask[i]);
                pval += (src[start + i] * d_mask[i]);
               // printf("PVal = %d\n", pval);
            }
        }
 
        //storing the answer in the resultant array
 res[id] = pval;        
      }
}
 
__global__ void Convolution_shared(int *eles, int *ans, int eles_length){
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    
      //Initializing the shared memory for elements
    __shared__ int shared_Src[TILE_SIZE + Mask_Width - 1];
 
    int s = Mask_Width / 2;
    
    if(id < eles_length){
            //Populating the shared memory
 
    //calculating the left halo indices
    int halo_left = (blockIdx.x - 1) * blockDim.x + threadIdx.x;
    if(threadIdx.x >= (blockDim.x - s)){
        shared_Src[threadIdx.x - (blockDim.x - s)] = (halo_left < 0) ? 0: eles[halo_left];
    }
    shared_Src[s + threadIdx.x] = eles[blockIdx.x * blockDim.x + threadIdx.x];
 
    //Calculating the right halo indices
    int halo_right = (blockIdx.x + 1) * blockDim.x + threadIdx.x;
    if(threadIdx.x < s){
        shared_Src[s + blockDim.x + threadIdx.x] = (halo_right >= eles_length) ? 0 : eles[halo_right]; 
    }
    __syncthreads();
 
    //Calculating the resultant array
    int pval = 0;
    for(int i = 0; i < Mask_Width; i++){
        pval += (shared_Src[threadIdx.x + i] * d_mask[i]);
    }
 
    //Storing the result
    ans[id] = pval;
        
    }
}
 
int main(){
    //Initializing the input array and the mask array
    int n = 8;
    int input [] = {3, 4, 15, 4, 67, 89, 12, 5};
    int mask[] = {7, 8, 9, 10, 11};
    int size_input = sizeof(int) * n;
    int size_mask = sizeof(int) * Mask_Width;
    int h_output[n], h_output_s[n];

    //to mark the time taken by the kernel to execute 
    float et;
    cudaEvent_t start, stop;
    cudaEventCreate(&start); cudaEventCreate(&stop);
 
    //Allocating space in the device
    int *d_input, *d_output, *d_output_s;
    cudaMalloc((void **)&d_input, size_input);
    cudaMalloc((void **)&d_output, size_input);
    cudaMalloc((void **)&d_output_s, size_input);
 
    //Copying the mask directly to constant memory
    cudaMemcpyToSymbol(d_mask, mask, size_mask);
 
    //Copying the input to the device memory
    cudaMemcpy(d_input, input, size_input, cudaMemcpyHostToDevice);
 
    //Calling the kernel function
    int threads = 16;
    int blocks = (threads + n - 1) / threads;
    
    //starting the recorder to calc the execution time 
    cudaEventRecord(start);
    
    Convolution_constant<<<blocks, threads>>>(d_input, d_output, 5, n);
    
    cudaEventRecord(stop);
    cudaDeviceSynchronize();

    //Calculating the elapsed time for constant memory kernel
    cudaEventElapsedTime(&et, start, stop);
    printf("\n Time taken by constant memory kernel to execute is: %f\n", et);
 
    //calling the shared memory kernel
    cudaEvent_t start_s, stop_s;
    cudaEventCreate(&start_s); cudaEventCreate(&stop_s);
    threads = 4;
    blocks = (threads + n - 1) / threads;

    //similarly as before starting the timer to calcualte the execution time 
    // this is for the shared memory kernel
    cudaEventRecord(start_s);
    Convolution_shared<<<blocks, threads>>>(d_input, d_output_s, n);
    cudaEventRecord(stop_s);
    cudaDeviceSynchronize();
    cudaEventElapsedTime(&et, start_s, stop_s);
 
    //printing the elapsed time of shared kernel
    printf("\nThe time elapsed of the shared memory kernel is: %f\n", et);
    
    //Copying the constant memory result to host
    cudaMemcpy(h_output, d_output, size_input, cudaMemcpyDeviceToHost);
 
    //Copying the shared memory result to host
    cudaMemcpy(h_output_s, d_output_s, size_input, cudaMemcpyDeviceToHost);
 
    //printing the result
    printf("\n Input array: > \n");
    for(int i = 0; i < n; i++){
        printf("%d\t", input[i]);
    }
    printf("\n");
    printf("\n Mask array: > \n");
    for(int i = 0; i < Mask_Width; i++){
        printf("%d\t", mask[i]);
    }
    printf("\n");
    printf("\nPart 1>  Constant memory resultant array:\n");
    for(int i = 0; i < n; i++){
        printf("%d\t", h_output[i]);
    }
    printf("\n");
    printf("\nPart 2> Constant shared resultant array:\n");
    for(int i = 0; i < n; i++){
        printf("%d\t", h_output_s[i]);
    }
 
    //Freeing the allocated device memory
    cudaFree(d_output);
    cudaFree(d_output_s);
    cudaFree(d_input);
    cudaFree(d_mask);

    return 0;
}


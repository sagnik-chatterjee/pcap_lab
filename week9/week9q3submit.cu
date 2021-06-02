%%cu

#include <stdio.h>
#include <stdlib.h>
__global__ void mat_mul(int *src_mat, int *mul_mat, int *res, int r){
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if(row < r && col < r){
        //Accumulating a partial result
        int temp = 0;
        for(int i = 0; i < r; i++){
            temp += (src_mat[row * r + i] * mul_mat[i * r + col]);
        }
 
        //Writing back the result
        res[row * r + col] = temp;
    }
}




int main(){
    int mat1[] = {4,4,4,4};
    int mat2[] = {5,5,5,5};
    int res[4];
    int n =2 ;
    int size_val = sizeof(int)*4;

    int *d_mat1 , *d_mat2 ,*d_output;

    cudaMalloc((void**)&d_mat1,size_val);
    cudaMalloc((void**)&d_mat2,size_val);
    cudaMalloc((void**)&d_output,size_val);

    cudaMemcpy(d_mat1,mat1,size_val,cudaMemcpyHostToDevice);
    cudaMemcpy(d_mat2,mat2,size_val,cudaMemcpyHostToDevice);

    //threads and blocks set up
    int thread_count =4;
    int blocks = (thread_count + n-1) /thread_count; 
    dim3 THREADS(thread_count,thread_count);
    dim3 BLOCKS(blocks,blocks);

    //calling kernel 
    mat_mul <<<BLOCKS,THREADS>>>(d_mat1,d_mat2,d_output,2);

    //copy back to host 
    cudaMemcpy(res,d_output,size_val,cudaMemcpyDeviceToHost);

    //input print 
    printf("Matrix 1 > \n");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%d\t",mat1[i]);
        }
        printf("\n");
    }
    //mat2 
    printf("Matrix 2 > \n");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            printf("%d\t",mat2[i]);
        }
        printf("\n");
    }
    //result 
    printf("Result :- > \n");
    for(int i=0;i<2;i++){
        printf("%d\t",res[i]);
    }
    printf("\n");
    for(int i=2;i<4;i++){
        printf("%d\t",res[i]);
    }
    //free up resources 
    cudaFree(d_mat1);
    cudaFree(d_mat2);
    cudaFree(d_output);
    return 0;
}
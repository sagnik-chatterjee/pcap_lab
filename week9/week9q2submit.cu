%%cu 
#include <stdio.h>
#include <stdlib.h>

__global__ void csr_mul(int n_rows,int *mat,int *ci,int *rp,int *mulvec,int *ans){
    int id =threadIdx.x;
    if(id < n_rows){
        int element =0;
        int start = rp[id];
        int end= rp[id+1];
        for(int i=start;i<end;i++){
           int temp = mat[i] * mulvec[ci[i]];
           element += temp; 
        }
        ans[id] = element;
    }
}

int main(){
    int data[] = {4, 5, 6, 7, 8, 1, 2};
    int col_index [] = {0, 3, 1, 2, 0, 3, 3};
    int row_ptr[] = {0, 2, 5, 3, 8};
    int vector [] = {3, 3, 3, 3};
    int res[4];
    int size_data = sizeof(int) * 7;
    int size_col_id = sizeof(int) * 7;
    int size_row_ptr = sizeof(int) * 5;
   
    int *d_data, *d_col_ind, *d_row_ptr, *d_res, *d_vector;
    cudaMalloc((void **)&d_data, size_data);
    cudaMalloc((void **)&d_col_ind, size_col_id);
    cudaMalloc((void **)&d_row_ptr, size_row_ptr);
    cudaMalloc((void **)&d_res, sizeof(int)*4);
    cudaMalloc((void **)&d_vector, sizeof(int)*4);
 
    cudaMemcpy(d_data, data, size_data, cudaMemcpyHostToDevice);
    cudaMemcpy(d_col_ind, col_index, size_col_id, cudaMemcpyHostToDevice);
    cudaMemcpy(d_row_ptr, row_ptr, size_row_ptr, cudaMemcpyHostToDevice);
    cudaMemcpy(d_vector, vector, sizeof(int)*4, cudaMemcpyHostToDevice);
 
    //kernel function call
    csr_mul <<<1, 8>>>(4, d_data, d_col_ind, d_row_ptr, d_vector, d_res);
 
    cudaMemcpy(res, d_res, sizeof(int)*4, cudaMemcpyDeviceToHost);
 
    for(int i = 0; i < 4; i++){
        printf("%d\t", res[i]);
    }
 
    cudaFree(d_data);
    cudaFree(d_col_ind);
    cudaFree(d_row_ptr);
    cudaFree(d_res);
    cudaFree(d_vector);
    return 0;
}

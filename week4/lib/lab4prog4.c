#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int rank, size;
    int arr[4][4], b[4], part[100], i, j, ele, pos;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        fprintf(stdout, "\nEnter a 4X4 matrix\n");
        fflush(stdout);
        for(i = 0; i < 4; i++){
            for(j = 0; j < 4; j++){
                scanf("%d", &arr[i][j]);
            }
        }
    }

    MPI_Scatter(arr, 4, MPI_INT, b, 4, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scan(b, part, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    
    for(i = 0; i < 4; i++){
        fprintf(stdout, "%d\t", part[i]);
        fflush(stdout);
    }
    
    printf("\n");
    
    MPI_Finalize();

}
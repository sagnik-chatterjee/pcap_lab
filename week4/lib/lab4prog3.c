#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    int rank, size;
    int arr[3][3], b[3], i, j, ele, pos;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        fprintf(stdout, "\nPlease Enter Matrix Elements:\n");
        fflush(stdout);
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                scanf("%d", &arr[i][j]);
            }
        }
        fprintf(stdout, "\nPlease Enter Element to be found:\n");
        fflush(stdout);
        scanf("%d", &ele);
    }
    MPI_Bcast(&ele, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, 3, MPI_INT, b, 3, MPI_INT, 0, MPI_COMM_WORLD);
    int count = 0;
    for(i = 0; i < 3; i++){
        if(b[i] == ele){
            count++;
        }
    }

    MPI_Reduce(&count, &pos, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        fprintf(stdout, "\nThe ELement is found %d times\n", pos);
        fflush(stdout);
    }
    MPI_Finalize();
}
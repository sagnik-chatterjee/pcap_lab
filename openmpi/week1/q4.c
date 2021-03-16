#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE sizeof(int)

int main (int argc, char *argv [])
{

    int size, rank;
    //int value;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0)
    {
        int value;
        printf("Enter the number :- \n");
        scanf("%d", &value);
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
        printf("process of rank %d got  value back %d\n", rank, value);
    }
    else
    {
        int value;
        int beforerank = rank - 1;
        int afterrank = (rank + 1) % size;
        MPI_Recv(&value, 1, MPI_INT, beforerank, 0, MPI_COMM_WORLD, &status);
        printf("process of rank :- %d got value %d from process sent rank :- %d \n", rank, value, beforerank);
        value++;
        printf("process of rank :- %d  sent value  %d to process of rank :-%d \n", rank, value, afterrank);
        MPI_Send(&value, 1, MPI_INT, afterrank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

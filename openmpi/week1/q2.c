#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE sizeof(int)

int main (int argc, char *argv [])
{

    int size, rank;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *number = (int *)malloc(SIZE);

    for(int i = 0; i < SIZE; i++)
    {
        //fill up the number array with random numbers
        number[i] =  rand() % ((i + 1) * 100) + 1;
    }

    if (rank == 0)
    {

        for (int i = 1; i < size; ++i)
        {
            printf("Sending rank :- %d. Sent to proces of rank %d:- %d\n", rank, i, *number);
            // Send to the process with ID = i
            MPI_Send(number, SIZE, MPI_INT, i,  i, MPI_COMM_WORLD);
        }

    }
    else
    {

        // Revc from the process with ID = 0
        MPI_Recv(number, SIZE, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);

        printf("The receiver rank:- %d. Received:-  %d\n", rank, *number);

    }

    MPI_Finalize();
    return 0;
}

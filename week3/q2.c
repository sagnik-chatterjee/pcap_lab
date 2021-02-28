/**
AUTHOR : SAGNIK CHATTERJEE
MPI program to read an integer value M and NXM elements into an 1D array in
the root process, where N is the number of processes. Root process sends M elements to
each process. Each process finds average of M elements it received and sends these average
values to root. Root collects all the values and finds the total average.
Use collective communication routines.

*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

//TODO
int main(int argc, char **argv)
{
    int rank, size, M, N;
    int send_buffer[4], recv_buffer[4][4];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Enter the value of M ");
    scanf("%d", &M);
    if(size != 4)
    {
        printf("This application is meant to be run with 4 MPI processes!!!\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if(rank == 0)
    {
        N = size;
        printf("Enter %d values:-\n ", N);
        for(int i = 0; i < N; i++)
        {
            for(int j=0;j<M;j++){
            	scanf("%d",&send_buffer[i][j]);
            }
        }
    }


}

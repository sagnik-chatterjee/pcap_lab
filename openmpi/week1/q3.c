#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv [])
{

    int size, rank;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    int len = size;
    int *arr = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < size; ++i)
    {
        *(arr + i) = i * 256 + 1;
    }

    int buffer_attached_size = MPI_BSEND_OVERHEAD + len * sizeof(int);

    int *buffer_attached  = (int *)malloc(buffer_attached_size);
    int *recv_buffer = (int *)malloc(buffer_attached_size);


    int res;


    if (rank == 0)
    {

        //		MPI_Buffer_attach(buffer_attached,buffer_attached_size);
        for (int i = 1; i < size; i++)
        {
            MPI_Buffer_attach(buffer_attached, buffer_attached_size);

            printf("The rank:- %d. Sent %d to %d.\n", rank, arr[i - 1], i);
            MPI_Bsend(arr + i, len, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Buffer_detach(&buffer_attached, &buffer_attached_size);
            printf("Returned from Bsend ....\n");
            //free(buffer_attached);

        }
        //		MPI_Buffer_detach(&buffer_attached,&buffer_attached_size);
        //		printf("Returned from Bsend ....\n");
        //		free(buffer_attached);

    }
    else
    {

        MPI_Recv(&recv_buffer, buffer_attached_size, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);

        int num;
        for(int i = 0; i < sizeof(recv_buffer); i++)
        {
            if(rank % 2 != 0)
            {
                num =  recv_buffer[i] * recv_buffer[i];
            }
            else
            {
                num = recv_buffer[i] * recv_buffer[i] * recv_buffer[i];
            }
        }
        printf("The rank %d gets the process with rank %d  \n ", rank, num);
    }

    MPI_Finalize();
    return 0;
}

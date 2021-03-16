#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Status status;
    int root_rank = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0 )
    {
        for (int i = 1; i < size; i++)
        {
                int value = rand()%(512+i) + 1;
                printf("process of rank %d ,  sending data %d to process with rank %d \n", rank, value, i);
                int buffer_size = sizeof(int) + MPI_BSEND_OVERHEAD;
                void *buffer = malloc(buffer_size);
                MPI_Buffer_attach(buffer, buffer_size);
                MPI_Bsend(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Buffer_detach(&buffer, &buffer_size);
            
        }
    }
    else
    {
        int value;
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        int ans ;
        if(rank %2 ==0 ){
        	ans = value *value;
        }
        else {
        	ans = value *value *value;
        }
        printf("process of rank %d received value %d from process of rank %d  and calculated %d\n", rank, value, root_rank, ans);
    }
    MPI_Finalize();
    return 0;
}
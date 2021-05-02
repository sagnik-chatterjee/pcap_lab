#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int main(int argc ,char **argv){

    int rank,size ,data_Send=12345,received;

    int buffer_attached_size = MPI_BSEND_OVERHEAD+sizeof(int);

    char *buffer_attached =(char*)malloc(buffer_attached_size);

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0){
        MPI_Buffer_attach(buffer_attached,buffer_attached_size);
        printf("Sender %d has sent value %d\n",rank,data_sent);
        MPI_Bsend(&data_sent,1,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Buffer_detach(&buffer_attached,&buffer_attached_size);
        free(buffer_attached);
    }
    else if(rank==1){
        MPI_Recv(&received,1,MPI_INT,0,1,MPI_COMM_WORLD);
        
    }
    MPI_Finalize();
    return 0;

}


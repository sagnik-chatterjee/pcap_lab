#include <mpi.h>
#include <stdio.h>


int main(int argc ,char **argv){
  int my_rank,nprocs;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

  printf("Hello from processes %d of %d\n",my_rank,nprocs);
  MPI_Finalize();
  return 0;
}

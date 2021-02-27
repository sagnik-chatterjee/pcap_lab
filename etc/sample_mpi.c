#include <stdio.h>
#include <mpi.h>

int main(int argc ,char **argv){
  int rank_find ,size_find;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank_find);
  MPI_Comm_size(MPI_COMM_WORLD,&size_find);

  printf("Hello World ...\n");
  printf("Rank is %d ",rank_find);
  printf("Size is %d ",size_find);
  
  
  MPI_Finalize();
return 0;
}

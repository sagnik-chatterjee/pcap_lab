#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

int main(int argc , char **argv) {
  int rank, size;


  srand(time(NULL));
  int p = rand() % 500;
  int q = rand() % 700;
  MPI_Init(&argc , &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (size != 4) {
    printf("Must use 4 processes for running for the 4 operations");
    exit(0);
  }

  if (rank == 0) {
    printf("The values are :%d ,%d", p, q);
    printf("The result is :- %d\n", p + q);
  }
  if (rank == 1) {
    printf("The values are: %d %d ", p, q);
    printf("The result is:- %d\n", p - q);
  }
  if (rank == 2) {
    printf("The values are : %d %d", p, q);
    printf("The result is :- %d\n", p * q);
  }
  if (rank == 3) {
    printf("The values are : %d %d", p, q);
    printf("The result is :- %f\n", (double)p / q);
  }
  MPI_Finalize();
  return 0;
}
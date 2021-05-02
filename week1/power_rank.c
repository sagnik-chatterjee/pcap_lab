#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(int argc , char **argv) {
  int rank , size;
  //taking random value for x

  srand(time(0));

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int r = rand() % 100; //for keeping it in range 0-100
  int h = pow(r, rank);
  printf("The value of the power is :- %d\n", h);
  printf("The random value is :- %d\n", r);
  printf("The rank of the value is :-%d\n", rank);
  MPI_Finalize();
  return 0;
}
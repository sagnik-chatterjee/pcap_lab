/**
AUTHOR: SAGNIK CHATTERJEE
Write a MPI program using N processes to find 1! + 2! +.....+N!. Use scan. Also, handle
different errors using error handling routines.
*/


#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

void ErrorHandler(int error_code) {
  if (error_code != MPI_SUCCESS) {
    char error_string[BUFSIZ];
    int length_of_error_string, error_class;
    MPI_Error_class(error_code, &error_class);
    MPI_Error_string(error_code, error_string, &length_of_error_string);
    printf("Errors:= %d \t %s\n",  error_class, error_string);
  }
}

int factorial(int num) {
  if (num <= 1) {
    return 1;
  }
  else {
    return num * factorial(num - 1);
  }
}

int main(int argc, char **argv) {

  int rank, size, factorial_final_ans = 0, error_code;
  MPI_Init(&argc, &argv);
  MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
  error_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  ErrorHandler(error_code);
  error_code = MPI_Comm_size(MPI_COMM_WORLD, &size);
  ErrorHandler(error_code);
  int factorial_value = factorial(rank);
  MPI_Scan(&factorial_value, &factorial_final_ans, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  printf(" The sum of all the factorials is:-  %d\n", factorial_final_ans);
  MPI_Finalize();
  return 0;
}
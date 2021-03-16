#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int factorial(int num){
   if(num<=1){
       return 1;
   }
   else {
       return num*factorial(num-1);
   }
}

int main(int argc, char **argv){
    int rank, size, ans;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERROS_RETURN);

    int factorial_value = factorial(rank);
   int k=0;
    k=MPI_Scan(&factorial, &ans, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    if(k!=MPI_SUCCESS){
        printf("Error handling ");
        MPI_Finalize();//exit out of the program
    }
    printf("\nThe sum of all the factorials is: %d\n", ans);
    MPI_Finalize();
}

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int factorial(int num){
    int i, f = 1;
    for(i = 1; i <= num; i++){
        f *= i;
    }

    return f;
}

int main(int argc, char *argv[]){
    int rank, size, ans;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);//to retunr info about errors 

    int factorial_value = factorial(rank);
   
    ierr= MPI_Scan(&factorial, &ans, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    if(ierr==MPI_SUCCESS){
        //now handling the error 
        MPI_Error_class(ierr,&errclass);
        if (errclass== MPI_ERR_RANK) {
         fprintf(stderr,"Invalid rank used in MPI send call\n");
         MPI_Error_string(ierr,err_buffer,&resultlen);
         fprintf(stderr,err_buffer);
         //aborting since error 
         MPI_Finalize();
    }
    }
    
    printf("\nThe sum of all the factorials is: %d\n", ans);
    MPI_Finalize();
}

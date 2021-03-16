/**
AUTHOR : SAGNIK CHATTERJEE
Write a MPI program to calculate π-value by integrating f(x) = 4 /(1+x 2 ) . Area under the
curve is divided into rectangles and the rectangles are distributed to the processors. Also
handle different errors using error handling routines,
*/


#include <stdio.h>
#include <mpi.h>


#define Ntot 10000
#define d1 0.0001
#define d2 0.00000001


void ErrorHandler(int error_code) {
    if (error_code != MPI_SUCCESS) {
        char error_string[BUFSIZ];
        int length_of_error_string, error_class;
        MPI_Error_class(error_code, &error_class);
        MPI_Error_string(error_code, error_string, &length_of_error_string);
        printf("Errors:= %d \t %s\n",  error_class, error_string);
    }
}


int main (int argc, char* argv[])
{
    int rank, size, error_code, i;
    double pi_value = 0.0, result_rect = 0.0, sum = 0.0, begin = 0.0, end = 0.0, x2;


    MPI_Init (&argc, &argv);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    error_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ErrorHandler(error_code);
    error_code = MPI_Comm_size(MPI_COMM_WORLD, &size);
    ErrorHandler(error_code);

    //Each process will caculate a part of the sum
    //as the sum of the rectangles are calculated in each process
    //and them passed to reduce
    //Ntot is the maximum processes we can calcualte for i.e asuming user doesnt cross 10000 threads
    for (i = rank; i < Ntot; i += size)
    {
        //since we need to integrate the area from 0 to 1 ,(as 1+x^2 integrating is tan-^1(x) and at 1 it gives pi/4 so 4*this is 4*pi/4 i.e pi)
        // we divide the total area by the total threads that is possible
        //now on the xaxis we go on incrementing the distance x by size , since
        //on each increment we increase by that onlyi.e dx increase in length
        x2 = d2 * i * i;//small area that we are considering
        result_rect += 4.0 / (1.0 + x2);
    }

    MPI_Reduce(&result_rect, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        //pi_value now has the product
        pi_value = d1 * sum;
        printf("Total process used = %d ----->  Pi value output = %lf\n", size, pi_value);
    }
    MPI_Finalize();
    return 0;
}
/**
AUTHOR: SAGNIK CHATTERJEE
Write a MPI program to read a 3 X 3 matrix. Enter an element to be searched in the root
process. Find the number of occurrences of this element in the matrix using three processes.
Also, handle different errors using error handling routines
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


int main(int argc, char **argv) {
    int rank, size, error_code;
    int arr[3][3], arr2[3], i, j, ele, pos;
    MPI_Init(&argc, &argv);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    error_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ErrorHandler(error_code);
    error_code = MPI_Comm_size(MPI_COMM_WORLD, &size);
    ErrorHandler(error_code);

    if (rank == 0) {
        printf("Enter the elements of the 3*3 matrix :\n");
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                scanf("%d", &arr[i][j]);
            }
        }
        printf("Enter the element to be searched:- \n");
        scanf("%d", &ele);
    }
    MPI_Bcast(&ele, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, 3, MPI_INT, arr2, 3, MPI_INT, 0, MPI_COMM_WORLD);
    int count = 0;
    for (int i = 0; i < 3; i++) {
        if (arr2[i] == ele) {
            count++;

        }
    }
    MPI_Reduce(&count, &pos, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("The element %d is found %d times in the matrix.\n", ele, pos);
    }
    MPI_Finalize();
    return 0;
}
/**
AUTHOR: SAGNIK CHATTERJEE
Write a MPI program to read 4 X 4 matrix and display the following output using four
processes.
I/p matrix: 1 2 3 4
O/p matrix: 1 2 3 4
1 2 3 1
1 1 1 1
2 1 2 1
2 4 6 5
3 5 7 6
5 6 9 7

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
    int arr[4][4], arr2[4], partsum[20], i, j, ele, pos;
    MPI_Init(&argc, &argv);
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    error_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ErrorHandler(error_code);
    error_code = MPI_Comm_size(MPI_COMM_WORLD, &size);
    ErrorHandler(error_code);

    if (rank == 0) {
        printf("Enter  4X4 matrix\n");
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                scanf("%d", &arr[i][j]);
            }
        }
    }

    MPI_Scatter(arr, 4, MPI_INT, arr2, 4, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scan(arr2, partsum, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    for (i = 0; i < 4; i++) {
        printf("%d ", partsum[i]);
    }
    MPI_Finalize();
    return 0;
}
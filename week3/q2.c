/**
AUTHOR : SAGNIK CHATTERJEE
MPI program to read an integer value M and NXM elements into an 1D array in
the root process, where N is the number of processes. Root process sends M elements to
each process. Each process finds average of M elements it received and sends these average
values to root. Root collects all the values and finds the total average.
Use collective communication routines.

*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    int rank, size;
    float avg = 0;
    float b[100];

    int i, n, m;

    int arr[100], c[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 4)
    {
        printf("This application is meant to be run with 4 MPI processes!!!\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }


    if (rank == 0)
    {
        n = size;
        printf("Enter 'm': \n");
        scanf("%d\n", &m);

        printf("Enter %d x %d = %d elements: ", n, m, n * m);
        for (i = 0; i < n * m; ++i)
        {
            scanf("%d\n", &arr[i]);
        }

    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr, m, MPI_INT, c, m, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < m; ++i)
    {
        avg += c[i];
    }

    avg /= m;
    printf("Process :- %d  gives Average = %.2f\n", rank, avg);

    MPI_Gather(&avg, 1, MPI_FLOAT, b, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {

        float tavg = 0;
        for (i = 0; i < n; i++)
            tavg += b[i];
        tavg /= n;
        printf("Total average = %.2f\n", tavg);

    }

    MPI_Finalize();
}

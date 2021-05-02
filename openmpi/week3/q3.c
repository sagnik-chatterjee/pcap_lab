/**
AUTHOR : SAGNIK CHATTERJEE
program to read a string. Using N processes (string length is evenly divisible
by N), find the number of non-vowels in the string. In the root process print number of
non-vowels found by each process and print the total number of non-vowels.
*/
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv)
{

    int rank, size;
    int count = 0;
    int b[100] = {0};

    int i, n, l;

    char str[100], c[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {

        n = size;

        printf("Enter the string: \n");
        scanf("%[^\n]%*c", str);

        l = strlen(str) / n;

    }

    MPI_Bcast(&l, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(str, l, MPI_CHAR, c, l, MPI_CHAR, 0, MPI_COMM_WORLD);

    count = 0;
    for (i = 0; i < l; ++i)
    {
        if (strchr("aeiouAEIOU", c[i]) == NULL)
            count += 1;
    }

    MPI_Gather(&count, 1, MPI_INT, b, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {

        int tcount = 0;
        for (i = 0; i < n; i++) {
            printf("The process %d has the number of no-vowels:- %d \n", i, b[i]);
            tcount += b[i];
        }
        printf("Total non vowels = %d\n", tcount);

    }

    MPI_Finalize();
    return 0;
}
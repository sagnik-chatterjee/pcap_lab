/**
AUTHOR : SAGNIK CHATTERJEE

MPI Program to read two strings S1 and S2 of same length in the root process.
Using N processes including the root (string length is evenly divisible by N), produce the
resultant string as shown below. Display the resultant string in the root process. Use
Collective communication routines.
Example:
String S1: string
String S2: length
Resultant String : slternigntgh

*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv )
{

    int rank, size;

    float avg = 0;
    char temp[100], str1[100], str2[100], c1[100], c2[100], concatted[100];

    int i, j, m;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {

        printf("Enter the string 1 : \n");
        scanf("%[^\n]%*c", str1);
        printf("Enter the string 2 : \n");
        scanf("%[^\n]%*c", str2);
        m = strlen(str1) / size;
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(str1, m, MPI_CHAR, c1, m, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(str2, m, MPI_CHAR, c2, m, MPI_CHAR, 0, MPI_COMM_WORLD);

    int t = 0;

    for (t = 0; t <= (2 * m); t += 2)
    {
        concatted[t] = c1[t / 2];
        concatted[t + 1] = c2[t / 2];
    }
    concatted[2 * m] = '\0';

    MPI_Gather(concatted, 2 * m, MPI_CHAR, temp, 2 * m, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        temp[m * size * 2] = '\0';
        printf("Concated string is :%s\n", temp);
    }

    MPI_Finalize();
    return 0;
}
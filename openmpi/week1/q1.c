#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char *char_toggle(char *a)
{
    int i;
    for(i = 0; i < strlen(a); i++)
    {
        if(a[i] >= 97 && a[i] <= 122)
        {
            a[i] = a[i] - 32;
        }
        else
        {
            a[i] = a[i] + 32;
        }
    }
    return a;
}

int main(int argc, char *argv[])
{
    int rank, size, n = 0;
    char word[10];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank == 0)
    {
        printf("\nEnter a word:\n");
        scanf("%s", word);
        n = strlen(word);
        printf("\nThe length of the string is %d\n", n);
        MPI_Ssend(&word, n, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("\nMessage sent :- %s from rank:- %d\n", word,rank);
        printf("\nWaiting for message.\n");
        MPI_Recv(&word, 5, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nMessage received:- %s\n", word);
    }
    else
    {
        char mess[10], *ans;
        MPI_Recv(&mess, 5, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("\n Received message :- %s from rank %d\n", mess, rank);
        ans = char_toggle(mess);
        MPI_Ssend(&mess, strlen(mess), MPI_CHAR, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
        printf("\n Message sent back to sender.\n");
    }
    MPI_Finalize();
    return 0;
}
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv){

    int rank,size;
    char str[5]="HeLLO";
    MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(str[rank]>='a' &&str[rank]<='z'){
        str[rank]=str[rank]-32;
    }
    else {
        str[rank]=str[rank]+32;
    }
    printf("The rank is %d ,modified string =%s\n",rank,str);
    MPI_Finalize();

    return 0;
}
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int isPrimeGt10(int n){
    int i,squareroot;
    if(n>10){
        squareroot =(int) sqrt(n);
        for(i=3;i<=squareroot;i=i+2){
            if((n%i)==0)
                return 0;
        }
        return 1;
    }
    return 0;

}
int main(int argc ,char **argv){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    

    MPI_Finalize();
    return 0;

}

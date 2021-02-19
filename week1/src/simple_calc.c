#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

int main(int argc ,char **argv){
  //the first and the second arg of the input are the operandds 
  int rank;

 /* if(argc!=3){
    printf("There needs to be 2 operands !!!!");
    exit(1);
  }
  */
  //assuming that 4 process used 
  //and 4 operations possible
  /*char *a = argv[1];
  int p=atoi(a);
  char *b=argv[2];
  int q=atoi(b);
*/
  srand(time(NULL));
  int p=rand()%100;
  int q=rand()%200;
  MPI_Init(&argc ,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  if(rank==0){
    printf("The values are :%d ,%d",p,q);
    printf("The result is :- %d\n",p+q);
  }
  if(rank==1){
    printf("The values are: %d %d ",p,q);
    printf("The result is:- %d\n",p-q);
  }
  if(rank==2){
    printf("The values are : %d %d",p,q);
    printf("The result is :- %d\n",p*q);
  }
  if(rank==3) {
    printf("The values are : %d %d",p,q);
    printf("The result is :- %f\n",(double)p/q);
  }
  MPI_Finalize();
  return 0;
}

/* Author:   Sagnik Chatterjee
 * File:     prime2.c
 * Purpose:  Find all primes less than or equal to an input value.
 *
 * Input:    n:  integer >= 2 (from command line)
 * Output:   Sorted list of primes between 2 and n,
 *
 * Compile:  mpicc -g -Wall -DDEBUG -o primes parallel_primes.c -lm
 * Usage:    mpiexec -n <p> ./primes <n>
 *              n:  max int to test for primality
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

/* Ints in the lists will be between 0 and RMAX */
const int RMAX = 100;
const int STRING_MAX = 10000;

void Print_list(int list[], int n, int my_rank);
void Usage(char prog[]);
int Get_n(int argc, char* argv[]);
int Is_prime(int i);
void Bcast(int** primes_p,  int my_rank, int p, MPI_Comm comm, int local_n, int* prime_count_p);
void Merge(int** primes_p, int* prime_count_p, int received_primes[], int received_count, int** temp_p);
void UpdateListSize(int* prime_count_p, int my_rank, unsigned bitmask, int p);

int main(int argc, char* argv[]) {
   int n, i, j, p, local_n, my_rank;   
   MPI_Comm comm;

   MPI_Init(&argc, &argv);
   comm = MPI_COMM_WORLD;
   MPI_Comm_size(comm, &p);
   MPI_Comm_rank(comm, &my_rank);

   n = strtol(argv[1], NULL, 10);
   local_n = n/(2*p)+2;

   int* primes_p;
   int* prime_count_p;

   primes_p = malloc(local_n*sizeof(int));
   prime_count_p = malloc(p*sizeof(int));

   j = 0;

   if(my_rank == 0){
       primes_p[j] = 2;
       j++;
   }

   for (i = 2*my_rank +3; i <= n; i += 2 * p){
      if (Is_prime(i)){
         primes_p[j]=i;
         j++;
      }
   }

#  ifdef DEBUG
   printf("Proc %d > After search primes are = ", my_rank);
   Print_list(primes_p, j, my_rank);
   fflush(stdout);
#  endif

   MPI_Allgather(&j, 1, MPI_INT, prime_count_p, 1, MPI_INT, comm);

   Bcast(&primes_p, my_rank, p, comm, local_n, prime_count_p); 

#  ifdef DEBUG
   printf("Proc %d > Max primes = %d\n", my_rank, prime_count_p[my_rank]);
   fflush(stdout);
#  endif 

   if(my_rank == 0){
      printf("Primes less than %d are: ", n);
      Print_list(primes_p, prime_count_p[0], 0);
   }
	
   free(primes_p);

   MPI_Finalize();

   return 0;
}  /* main */

/*-------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print a brief message explaining how the program is run.
 *            The quit.
 * In arg:    prog:  name of the executable
 */
void Usage(char prog[]) {
   fprintf(stderr, "usage: %s <n>\n", prog);
   fprintf(stderr, "   n = max integer to test for primality\n");
   exit(0);
}  /* Usage */

/*-------------------------------------------------------------------
 * Function:   Is_prime
 * Purpose:    Determine whether the argument is prime
 * Input arg:  i
 * Return val: true (nonzero) if arg is prime, false (zero) otherwise
 */
int Is_prime(int i) {
   int j;

   for (j = 2; j <= sqrt(i); j++)
      if (i % j == 0)
         return 0;
   return 1;
}  /* Is_prime */

/*-------------------------------------------------------------------
 * Function:  Print_list
 * Purpose:   Convert a list of ints to a single string before
 *            printing.  This should make it less likely that the
 *            output is interrupted by another process.  This is
 *            mainly intended for debugging purposes.
 * In args:   list:  the ints to be printed
 *            n:  the number of ints
 *            my_rank:  the usual MPI variable
 */
void Print_list(int list[], int n, int my_rank) {
   char string[STRING_MAX];
   char* s_p;
   int i;

   sprintf(string, " ");
   s_p = string + strlen(string);
   for (i = 0; i < n; i++) {
      sprintf(s_p, "%d ", list[i]);
      s_p = string + strlen(string);
   }

   printf("%s\n", string);
   fflush(stdout);
}  /* Print_list */

/*-------------------------------------------------------------------
 * Function:  Merge
 * Purpose:   Merge a local list of primes with the primes from the process it's
 *            receiving from using a temporary storage array. 
 * In args:   primes_p:  local list of primes
 *            prime_count_p:  the number of primes in each process
 *            received_primes: list of primes to be received
 *            received_count:  number of primes to be received
 *            temp_p: list of primes for temporary storage for the merge
 *
 */
void Merge(int** primes_p, int* prime_count_p, int received_primes[], int received_count, int** temp_p){
   int ai = 0;
   int bi = 0;
   int ci = 0;

    while (ci < received_count + *prime_count_p) {
      if(ai == *prime_count_p){
         (*temp_p)[ci] = received_primes[bi];
         ci++; bi++;
      }
      else if(bi == received_count){
         (*temp_p)[ci] = (*primes_p)[ai];
         ci++; ai++;
      }
      else if ((*primes_p)[ai] <= received_primes[bi]) {
         (*temp_p)[ci] = (*primes_p)[ai];
         ci++; ai++;
      } else {
         (*temp_p)[ci] = received_primes[bi];
         ci++; bi++;
      }
   }

   *primes_p = *temp_p;
   *prime_count_p = ci;

} /* Merge*/

/* Function:    Bcast
 * Purpose:     Broadcast a merged list of primes from process 0 to all 
  *             the other processes. 
 *
 * Input args:  primes_p = locak list of primes
 *              my_rank = process's rank
 *              p = number of processes
 *              comm = communicator
 *              local_n = size of local prime list
 *              prime_count_p = list of the number of primes on each process
 * 
 */
void Bcast(int** primes_p,  int my_rank, int p, MPI_Comm comm, int local_n, int* prime_count_p) {
int partner;
unsigned bitmask = 1;
int* received_primes;
int* temp_p;

while (bitmask < p) {
   partner = my_rank ^ bitmask;
   if (partner < p) {
      if (my_rank > partner){
         MPI_Send(*primes_p, prime_count_p[my_rank], MPI_INT, partner, 0, comm);
         break;
      }
      else{
         received_primes = malloc(prime_count_p[partner]*sizeof(int));
         temp_p = malloc((prime_count_p[partner]+prime_count_p[my_rank])*sizeof(int));
         MPI_Recv(received_primes, prime_count_p[partner], MPI_INT, partner, 0, comm, 
               MPI_STATUS_IGNORE); 
         Merge(primes_p, &prime_count_p[my_rank], received_primes, prime_count_p[partner], &temp_p);
      #  ifdef DEBUG
         printf("Proc %d > After phase %d primes are", my_rank, bitmask - 1);
         Print_list(*primes_p, prime_count_p[my_rank], my_rank);
         fflush(stdout);
      #  endif
      }

      UpdateListSize(prime_count_p, my_rank, bitmask, p);

      }

   bitmask <<= 1;

   }

}  /* Bcast */

/* Function:    UpdateListSize
 * Purpose:     Updates the list size of a process's parter's list of primes.
 *
 * Input args:  prime_count_p = list of the number of primes on each process
 *              my_rank = process's rank
 *              p = number of processes
 *              bitmask
 */
void UpdateListSize(int* prime_count_p, int my_rank, unsigned bitmask, int p){
   int i, partner;

   for(i=0; i < p; i++){
      partner = i ^ bitmask;
      if(i < partner && partner < p && i != my_rank){
         prime_count_p[i] = prime_count_p[i] + prime_count_p[partner]; 
      }
   } 
} /*UpdateListSize*/

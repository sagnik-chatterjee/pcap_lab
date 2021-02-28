#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv []) {

	int size, rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int len = atoi(argv[1]);
	int *arr = (int *)calloc(len, sizeof(int));
	for (int i = 0; i < len; ++i) {
		*(arr + i) = atoi(argv[i+2]);
	}

	int res;

	if (rank == 0) {
		
		for (int i = 1; i < size; ++i) {
			MPI_Ssend(arr + i, sizeof(int), MPI_INT, i, 100 + i, MPI_COMM_WORLD);
			printf("The rank:- %d. Sent %d to %d.\n", rank, arr[i-1], i);
		}

	} else {
		
		int *num = (int *)malloc(sizeof(int));;
		MPI_Recv(num, sizeof(int), MPI_INT, 0, 100 + rank, MPI_COMM_WORLD, &status);

		res = *num * *num;
		if (rank % 2 != 0)
			res *= *num;

		printf("The rank:- %d. %d:%d\n", rank, *num, res);

	} 

	MPI_Finalize();
}

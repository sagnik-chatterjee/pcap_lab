/**
AUTHOR : SAGNIK CHATTERJEE

MPI program to read N values in the root process. Root process sends one value to
each process. Every process receives it and finds the factorial of that number and returns it
to the root process. Root process gathers the factorial and finds sum of it.

*/


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int factorial(int n)
{
	int arr[n];
	//base case
	arr[0] = 1;
	arr[1] = 1;

	for (int i = 2; i <= n; i++)
	{
		arr[n] = n * factorial(n - 1);
	}
	return arr[n];

}

int sumvalue(int *arr, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum = sum + arr[i];
	}
	return sum;
}

int main(int argc, char **argv)
{
	int rank, size, N, fac_value, c;
	int send_buffer[4], recv_buffer[4];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if (rank == 0)
	{
		N = size;
		printf("Enter %d values:-\n ", N);
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &send_buffer[i]);
			if (send_buffer[i] < 0) {
				printf("PLEASE DON'T PUT NEGATIVE VALUES !!!!");
				MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
			}
		}
	}
	MPI_Scatter(send_buffer, 1, MPI_INT, &c, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("\n Received %d in process %d\n", c, rank);
	int h = factorial(c);
	MPI_Gather(&h, 1, MPI_INT, recv_buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("The final result after summing the factorials are :\n");
		printf(" %d\n ", sumvalue(recv_buffer, N));
	}

	MPI_Finalize();
	return 0;

}

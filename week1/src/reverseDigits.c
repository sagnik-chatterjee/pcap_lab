#include <mpi.h>
#include <stdio.h>

int reverse(int a) {
	int rev = 0;
	while (a != 0) {
		int remainder = a % 10;
		rev = rev * 10 + remainder;
		a = a / 10;
	}
	return rev;

}

int main(int argc , char **argv) {
	int rank, size;

	int arr[9] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	switch (rank) {
	case 1: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[0]));
		break;
	case 2: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[1]));
		break;
	case 3: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[2]));
		break;
	case 4: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[3]));
		break;
	case 5: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[4]));
		break;
	case 6: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[5]));
		break;
	case 7: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[6]));
		break;
	case 8: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[7]));
		break;
	case 9: printf("The rank of this process is :%d\n,and the reversed value id %d\n", rank, reverse(arr[8]));
		break;

	}
	MPI_Finalize();

	return 0;
}
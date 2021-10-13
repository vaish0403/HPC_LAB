#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define n 8 //array size n

int a[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

int a2[5000];
// Temporary array for slave process

int main(int argc, char* argv[])
{

	int rank, //process id
		world_size,	//no. of processes
		elements_per_process,n_elements_recieved;
	char name[80];
	int length;

	MPI_Status status;

	MPI_Init(&argc, &argv);	

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Get_processor_name(name, &length);

	// master process
	if (rank == 0) {
		int index, i;
		elements_per_process = n / world_size;

		// check if more than 1 processes are running
		if (world_size > 1) {
			// distributes the portion of array to child processes to calculate their partial products
			for (i = 1; i < world_size - 1; i++) {
				index = i * elements_per_process;

				MPI_Send(&elements_per_process,
					1, MPI_INT, i, 0,
					MPI_COMM_WORLD);
				MPI_Send(&a[index],
					elements_per_process,
					MPI_INT, i, 0,
					MPI_COMM_WORLD);
			}

			// last process adds remaining elements
			index = i * elements_per_process;
			int elements_left = n - index;

			MPI_Send(&elements_left,
				1, MPI_INT,
				i, 0,
				MPI_COMM_WORLD);

			MPI_Send(&a[index],
				elements_left,
				MPI_INT, i, 0,
				MPI_COMM_WORLD);
		}

		// master process multiplies its own sub array
		int product = 1;
		for (i = 0; i < elements_per_process; i++)
			product *= a[i];

		// collects partial products from other processes
		int tmp;
		for (i = 1; i < world_size; i++) {
			MPI_Recv(&tmp, 1, MPI_INT,	MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			int sender = status.MPI_SOURCE;

			product *= tmp;
		}

		// prints the final product of array
		printf("Product of array is : %d calulated by %d processes from processor %s\n", product, world_size, name);
	}
	// slave processes
	else {
		MPI_Recv(&n_elements_recieved,
			1, MPI_INT, 0, 0,
			MPI_COMM_WORLD,
			&status);

		// stores the received array segment
		// in local array a2
		MPI_Recv(&a2, n_elements_recieved,
			MPI_INT, 0, 0,
			MPI_COMM_WORLD,
			&status);

		// calculates its partial product
		int partial_product = 1;
		for (int i = 0; i < n_elements_recieved; i++)
			partial_product *= a2[i];

		// sends the partial product to the root process
		MPI_Send(&partial_product, 1, MPI_INT,
			0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}

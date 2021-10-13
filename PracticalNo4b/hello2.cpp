//2018BTECS00060
#include<iostream>
#include<mpi.h>

using namespace std;

int main(int argc, char* argv[])
{
	int rank;//unique rank is assigned to each process in a communicator
	int size;
	char name[80];
	int length;

	MPI_Init(&argc, &argv);//initializes the mpi environment
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(name, &length);

	cout << "Hello Vaishnavi! PRN:2018BTECS00060, Rank " << rank << " out of " << size <<
		" processes from processor " << name << endl;

	MPI_Finalize();
	return 0;
}
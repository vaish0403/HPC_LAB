//2018BTECS00060
#include<iostream>
#include<mpi.h>

using namespace std;

int main(int argc, char* argv[]) 
{
	int size;

	MPI_Init(&argc, &argv);//initializes the mpi environment
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	cout << "Hello Vaishnavi PRN:2018BTECS00060, Total Processes: " << size << endl;
	
	MPI_Finalize();
	return 0;
}

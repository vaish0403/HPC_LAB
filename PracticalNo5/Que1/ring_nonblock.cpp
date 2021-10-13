//2018BTECS0060 
#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int numtasks, rank, next, prev, buf[2], tag1 = 1;
    MPI_Request reqs[4];
    MPI_Status stats[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    prev = rank - 1;
    next = rank + 1;
    if (rank == 0)
        prev = numtasks - 1;
    if (rank == (numtasks - 1))
        next = 0;

    MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
    printf("Process %d received with tag %d from process %d\n", prev, tag1, rank);
   
    MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[3]);


    MPI_Waitall(4, reqs, stats);

    MPI_Finalize();
}
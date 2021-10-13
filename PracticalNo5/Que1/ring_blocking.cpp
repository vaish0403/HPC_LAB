//2018BTECS00060
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    char name[80];
    int length;
    MPI_Get_processor_name(name, &length);

    float message;
    if (world_rank != 0) {
        MPI_Recv(&message, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);
        printf("Process %d received message ( %0.2f ) from process %d on processor %s\n", world_rank, message,
            world_rank - 1, name);
    }
    else {
        message = -60.4;
    }
    MPI_Send(&message, 1, MPI_FLOAT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
    if (world_rank == 0) {
        MPI_Recv(&message, 1, MPI_FLOAT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received message ( %0.2f ) from process %d on processor %s\n", world_rank, 
            message, world_size - 1, name);
    }
    MPI_Finalize();
}

#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, n_ranks;
    int my_first, my_last;
    int numbers = 10;
    MPI_Request request;
    char name[80];
    int length;
    MPI_Get_processor_name(name, &length);

    // First call MPI_Init


    // Check that there are at least two ranks
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
    if (n_ranks < 2) {
        printf("This example requires at least two ranks");
        MPI_Finalize();
        return(1);
    }

    // Get my rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        char message[30] = "Vaishnavi, PRN:2018BTECS00060";
        MPI_Isend(message, 31, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &request);
    }

    if (rank == 1) {
        char message[30];
        MPI_Status status;
        MPI_Irecv(message, 31, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Message ( %s ) received by process %d on processor %s\n", message, rank, name);
    }

    if (rank == 2) {
        char message[30] = "Vaishnavi, PRN:2018BTECS00060";
        MPI_Isend(message, 31, MPI_CHAR, 3, 1, MPI_COMM_WORLD, &request);
    }

    if (rank == 3) {
        char message[30];
        MPI_Status status;
        MPI_Irecv(message, 31, MPI_CHAR, 2, 1, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Message ( %s ) received by process %d on processor %s\n", message, rank, name);
    }


    // Call finalize at the end
    return MPI_Finalize();
}

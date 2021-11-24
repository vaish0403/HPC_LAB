#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, n_ranks;
    char name[80];
    int length;

    MPI_Get_processor_name(name, &length);

    //at least two ranks
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
    if (n_ranks < 2) {
        printf("This example requires at least two ranks");
        MPI_Finalize();
        return(1);
    }

    // Get rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {

        float message[4] = { 0.1,0.2,0.3,0.4 };
        MPI_Send(message, 5, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
    }

    if (rank == 1) {
        float m[4];
        MPI_Status status;
        MPI_Recv(m, 5, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nMessage(Array of float) received by process %d on processor %s\n", rank, name);
        printf("\nReceived array of float is: ");
        for (int i = 0;i < 4;i++)
        {
            printf("%f\t", m[i]);

        }
    }

    return MPI_Finalize();
}

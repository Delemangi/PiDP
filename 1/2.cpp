#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int BUFFER_SIZE = 128;
    char message[BUFFER_SIZE] = {};

    if (world_rank == 0)
    {
        strncpy(message, "Hello from 0", sizeof(message));
        message[sizeof(message) - 1] = 0;

        MPI_Send(&message, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&message, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        cout << message << endl;
    }
    else if (world_rank == 1)
    {
        MPI_Recv(&message, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        cout << message << endl;

        strncpy(message, "Answer from one", sizeof(message));
        message[sizeof(message) - 1] = 0;

        MPI_Send(&message, BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        printf("The number of processors must be 2, so run it again with mpiexec -np 2\n");
    }

    MPI_Finalize();
}

#include <mpi.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int BUFFER_SIZE = 128;

    MPI_Request reqs[2];
    MPI_Status statuses[2];

    char rec[BUFFER_SIZE];
    char send[BUFFER_SIZE];

    sprintf(send, "Message from CPU %d to CPU %d", rank, 1 - rank);

    MPI_Irecv(rec, BUFFER_SIZE, MPI_CHAR, 1 - rank, 0, MPI_COMM_WORLD, &reqs[0]);
    MPI_Isend(send, BUFFER_SIZE, MPI_CHAR, 1 - rank, 0, MPI_COMM_WORLD, &reqs[1]);

    MPI_Waitall(2, reqs, statuses);

    printf("[%d]: %s\n", rank, rec);

    MPI_Finalize();
    return 0;
}

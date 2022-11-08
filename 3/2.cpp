#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define BUFFER_SIZE 100
#define REQUEST_SIZE 20

int main()
{
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Request reqs[REQUEST_SIZE];
    MPI_Status statuses[REQUEST_SIZE];

    char recv[BUFFER_SIZE];
    char send[BUFFER_SIZE];

    int j = 0;

    if (rank == 0)
    {
        strcpy(send, "Message from CPU 0 to all CPUs");
        for (int proc_i = 1; proc_i < world_size; ++proc_i)
        {
            MPI_Isend(send, strlen(send) + 1, MPI_BYTE, proc_i, 0, MPI_COMM_WORLD, &reqs[proc_i]);
        }

        MPI_Irecv(recv, BUFFER_SIZE, MPI_BYTE, world_size - 1, 0, MPI_COMM_WORLD, &reqs[0]);

        j = world_size;
    }
    else
    {
        MPI_Irecv(recv, BUFFER_SIZE, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &reqs[0]);
        printf("[%d]: %s\n", rank, recv);
        sprintf(send, "Answer from #%d to CPU 0", rank);
        MPI_Isend(send, strlen(send) + 1, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &reqs[j]);
        j++;
    }

    MPI_Waitall(j, reqs, statuses);

    MPI_Finalize();
    return 0;
}

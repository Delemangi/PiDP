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

    double a = 0.0;
    MPI_Barrier(MPI_COMM_WORLD);
    double b = MPI_Wtime();

    double c = MPI_Wtime() - b;

    printf("[%d]\tWaited\t%.20f (time units)\n", rank, c);

    MPI_Finalize();
    return 0;
}

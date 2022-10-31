#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

double average(double *array, int n)
{
    int sum = 0;
    float average = 0;
    for (int i = 1; i < n; i++)
    {
        sum += array[i];
    }
    return (sum * 1.0) / (n * 1.0);
}

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int i = 0;
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double array[100];
    double arr = 100 / world_size;

    if (world_rank == 0)
    {
        for (i = 0; i < 100; i++)
        {
            array[i] = i;
        }
    }

    double *after_process = (double *) malloc(sizeof(double) * arr);
    MPI_Scatter(array, arr, MPI_DOUBLE, after_process, arr, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double avg = average(after_process, arr);

    printf("[%d]: Local average:\t %.2f\n", world_rank, avg);
    double *local = NULL;

    if (world_rank == 0)
    {
        local = (double *) malloc(sizeof(double) * world_size);
    }

    MPI_Gather(&avg, 1, MPI_DOUBLE, local, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        printf("Global average:\t%.2f\n", average(local, world_size));
    }
}

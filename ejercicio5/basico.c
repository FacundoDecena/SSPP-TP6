#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(argc, argv) int argc;
char **argv;
{
    char message[20];
    int myrank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    if (myrank == 0) /* código para proceso cero */
    {
        strcpy(message, "Hello, world");
        MPI_Send(message, strlen(message), MPI_CHAR, 1, 99,
                 MPI_COMM_WORLD);
    }
    else /* código para el proceso 1*/
    {
        MPI_Recv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
        printf("recibido :%s:\n", message);
    }
    MPI_Finalize();
}
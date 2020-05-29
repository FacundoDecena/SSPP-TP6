#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(argc, argv) int argc;
char **argv;
{
    int myrank;
    char message[14];
    char bmessage[14];
    int bufsize, bbsize;

    MPI_Request request;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    MPI_Pack_size(14, MPI_CHAR, MPI_COMM_WORLD, &bufsize);
    bufsize += MPI_BSEND_OVERHEAD;
    MPI_Buffer_attach(message, bufsize);

    if (myrank == 0)
    {
        strcpy(message, "Hello, world");
        MPI_Bsend(message, 13, MPI_CHAR, 1, 99, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Recv(message, 13, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
        printf("bloqueante recibido :%s:\n", message);
    }



    if (myrank == 0)
    {
        strcpy(message, "Hello, world!");
        MPI_Ibsend(message, 14, MPI_CHAR, 1, 123, MPI_COMM_WORLD, &request);
    }
    else
    {
        MPI_Irecv(message, 14, MPI_CHAR, 0, 123, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("noBloqueante recibido: %s\n\n", message);
    }


    MPI_Buffer_detach(&bmessage, &bbsize);
    MPI_Finalize();
    return 0;
}
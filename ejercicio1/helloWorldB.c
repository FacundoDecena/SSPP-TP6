#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MESSAGE_SIZE 50

int main(int argc, char** argv) {

    {
        char message[MESSAGE_SIZE];
        MPI_Status status;
        int size;
        int rank;

        MPI_Init(&argc, &argv);

        // Get the number of processes
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        // Get the rank of the process
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        sprintf(message, "Hola, saludos desde el proceso %d\n", rank);
        if(rank == 0){
            printf("Hola, soy el proceso 0 (hay %d procesos) y recibo: ", size);

            for(int i = 1; i < size; i++){
                MPI_Recv(message, MESSAGE_SIZE, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("%s", message);
            }

        } else{
            sprintf(message, "(Hola, saludos desde el proceso %d)\n", rank);
            MPI_Send(message, MESSAGE_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }

        // Finalize the MPI environment. No more MPI calls can be made after this
        MPI_Finalize();
    }
}
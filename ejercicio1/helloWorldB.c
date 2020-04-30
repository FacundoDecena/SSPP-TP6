#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
int MESSAGE_SIZE = 500;
    {
        char message[MESSAGE_SIZE];
        MPI_Status status;

        MPI_Init(NULL, NULL);

        // Get the number of processes
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        // Get the rank of the process
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

        // Get the name of the processor
        char processor_name[MPI_MAX_PROCESSOR_NAME];
        int name_len;
        MPI_Get_processor_name(processor_name, &name_len);

        if(world_rank == 0){
            strcpy(message, "Hola, soy el proceso 0 (hay %d procesos) y recibo:");
            MPI_Send(message, strlen(message), MPI_CHAR, world_rank++, 99, MPI_COMM_WORLD);
        } else{
            MPI_Recv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
            printf("Hola, saludos desde el proceso %d :%s:\n", world_rank, message);
            MPI_Send(message, strlen(message), MPI_CHAR, world_rank++, 99, MPI_COMM_WORLD);
        }
        // Print off a hello world message
        printf("Hello world from processor %s, rank %d out of %d processors\n",
        processor_name, world_rank, world_size);

        // Finalize the MPI environment. No more MPI calls can be made after this
        MPI_Finalize();
    }
}
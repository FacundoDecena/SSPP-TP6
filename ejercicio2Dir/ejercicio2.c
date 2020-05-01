#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MESSAGE_SIZE 50

int main(int argc, char** argv) {

    {
        char message[MESSAGE_SIZE];
        MPI_Status status;
        int size;
        int rank;
        int i;
        int n;
        MPI_Init(&argc, &argv);

        // Get the number of processes
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        // Get the rank of the process
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (argc < 2){
            n = 1;
        } else {
            n = atoi(argv[1]);
        }

        for(i = 0; i < n; i++) {
            char token;
            if (rank != 0) {
                MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
                printf("Process %d received token %c from process %d\n", rank, token, rank - 1);
            } else {
                // Set the token's value if you are process 0
                token = 'A';
            }
            MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

            // Now process 0 can receive from the last process.
            if (rank == 0) {
                MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Process %d received token %c from process %d\n", rank, token, size - 1);
            }
        }
        // Finalize the MPI environment. No more MPI calls can be made after this
        MPI_Finalize();
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>

/**
 * Creates a array representing the matrix used in the multiplication
 * @param num_elem
 * @return
 */

int multiply(int *column, int *vector, int size){
    int res = 0;
    int i;
    for( i = 0; i < size; i++){
        res += column[i] * vector[i];
    }
    return res;
}

int main(int argc, char** argv){

    int size, rank, i, num_elem;

    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    num_elem = size * size;
    int *matrix = (int *)malloc(sizeof(int) * num_elem);
    int *vector = (int *)malloc(sizeof(int) * size);
    // For each process create a buffer to hold the respective column
    int *column = (int *)malloc(sizeof(int) * size);

    if (rank == 0){
        for(i = 0; i < num_elem; i++){
            matrix[i] = i + 1;
        }
        for(i = 0; i < size; i++){
            vector[i] = i + 1;
        }
    }

    // Divide in columns
    MPI_Scatter(matrix, size, MPI_INT, column, size, MPI_INT, 0, MPI_COMM_WORLD);
    // Share the vector
    MPI_Bcast(vector, size, MPI_INT, 0, MPI_COMM_WORLD);

    int res = multiply(column, vector, size);

    int *sub_total = NULL;
    if(rank == 0){
        sub_total = (int *)malloc(sizeof(int) * size);;
    }

    MPI_Gather(&res, 1, MPI_INT, sub_total, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("El vector resultado es: \n");
        for( i = 0; i < size; i++){
            printf("%d \n", sub_total[i]);
        }
    }

    // Cleaning memory

    if(rank == 0){
        free(matrix);
        free(vector);
        free(sub_total);
    }
    free(column);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

}
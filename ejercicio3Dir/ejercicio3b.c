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

/**
 * getSubMatrix subtract a portion from a bigger matrix to a smaller one.
 * Can be use to copy it.
 * @param matrix
 * @param destination
 * @param start
 * @param finish
 */
void getSubMatrix(int *matrix, int *destination, int start, int finish){
    int i;
    for (i = start; i < finish; i++){
        destination[i - start] = matrix[i];
    }
}

int main(int argc, char** argv){

    int size, rank, i, matLength, subMatLength, colLength, index, control;

    if (argc != 2){
        printf("Cantidad de argumentos erronea");
        exit(1);
    }

    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    colLength = atoi(argv[1]);
    matLength = colLength * colLength;
    subMatLength = colLength * size;

    int *matrix = (int *)malloc(sizeof(int) * matLength);
    int *vector = (int *)malloc(sizeof(int) * colLength);
    int *subMatrix = (int *)malloc(sizeof(int) * subMatLength);
    // For each process create a buffer to hold the respective column
    int *column = (int *)malloc(sizeof(int) * colLength);
    control = 0;
    //Initialize the matrix and vector to multiply
    if (rank == 0){
        for(i = 0; i < matLength; i++){
            matrix[i] = i + 1;
        }
        for(i = 0; i < colLength; i++){
            vector[i] = i + 1;
        }
        printf("El vector resultado es: \n");
    }
    int *sub_total = NULL;
    MPI_Bcast(vector, colLength, MPI_INT, 0, MPI_COMM_WORLD);
    for (index = 0; index <  matLength - 1; index += subMatLength){
        getSubMatrix(matrix, subMatrix, index, index + subMatLength);
        // Divide in columns
        MPI_Scatter(subMatrix, colLength, MPI_INT, column, colLength, MPI_INT, 0, MPI_COMM_WORLD);
        // Share the vector

        int res = multiply(column, vector, colLength);

        if (rank == 0) {
            sub_total = (int *) malloc(sizeof(int) * size);;
        }

        MPI_Gather(&res, 1, MPI_INT, sub_total, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (rank == 0) {
            for (i = 0; i < size; i++) {
                control++;
                if (control < colLength)
                    printf("%d \n", sub_total[i]);
            }
        }
    }

    // Cleaning memory

    if(rank == 0){
        free(matrix);
        free(subMatrix);
        free(vector);
        free(sub_total);
    }
    free(column);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

}


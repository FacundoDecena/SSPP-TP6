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
    /**
     * size = #Cores
     * rank = specific core
     * matLength = #numbers in the matrix.
     * subMatLength = #cores * #number in a row
     * rowLength = #number in a row (same than columns)
     * i, index and control are for loops.
     */
    int size, rank, i, matLength, subMatLength, rowLength, index, control;

    if (argc != 2){
        printf("Cantidad de argumentos erronea");
        exit(1);
    }

    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Setting "execution constants"
    rowLength = atoi(argv[1]);
    matLength = rowLength * rowLength;
    subMatLength = rowLength * size;

    // Allocating memory
    // Matrix for multiply
    int *matrix = (int *)malloc(sizeof(int) * matLength);
    // Vector for multiply
    int *vector = (int *)malloc(sizeof(int) * rowLength);
    // Slice of matrix that current cores can handle at the same time
    int *subMatrix = (int *)malloc(sizeof(int) * subMatLength);
    // For each process create a buffer to hold the respective column
    int *column = (int *)malloc(sizeof(int) * rowLength);
    // Controls which number are printed at the end
    control = 0;
    //Initialize the matrix and vector to multiply
    if (rank == 0){
        for(i = 0; i < matLength; i++){
            matrix[i] = i + 1;
        }
        for(i = 0; i < rowLength; i++){
            vector[i] = i + 1;
        }
        printf("El vector resultado es: \n[\n");
    }
    // Space for the parcial results
    int *subTotal = NULL;

    //Shares the content of vector with other cores
    MPI_Bcast(vector, rowLength, MPI_INT, 0, MPI_COMM_WORLD);

    // Repeats until all the matrix has been multiplied with the vector
    for (index = 0; index <  matLength ; index += subMatLength){

        // gets the slice of the matrix with which processors can operate
        getSubMatrix(matrix, subMatrix, index, index + subMatLength);
        // Divides the rows between all processors
        MPI_Scatter(subMatrix, rowLength, MPI_INT, column, rowLength, MPI_INT, 0, MPI_COMM_WORLD);

        // Each processor calculates the row * vector
        int res = multiply(column, vector, rowLength);

        // Only the process 0 needs to be not null
        if (rank == 0) {
            subTotal = (int *) malloc(sizeof(int) * size);;
        }

        // The processor 0 gathers all the partials results and saves them in sub_total
        MPI_Gather(&res, 1, MPI_INT, subTotal, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // Prints the result
        if (rank == 0) {
            for (i = 0; i < size; i++) {
                if (control < rowLength)
                    printf("%d \n", subTotal[i]);
                control++;
            }
        }
    }
    if(rank == 0){
        printf("]\n");

        // Cleaning memory
        free(matrix);
        free(subMatrix);
        free(vector);
        free(subTotal);
    }
    free(column);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}

#include <mpi/mpi.h>
#include <stdio.h>
#include <stdlib.h>

void error(char* message)
{
    printf("%s", message);
    exit(1);
}

int main(int argc, char *argv[])
{
    MPI_Comm everyone; /* intercommunicator */

    int world_size = 0, flag, universe_sizep, universe_size;

    char worker_program[10] = "./worker";

    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size != 1)
        error("Top heavy with management\n");

    MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE, &universe_sizep, &flag);

    if (!flag)
    {
        printf("This MPI does not support UNIVERSE_SIZE.\n How many processes total?");
        scanf("%d", &universe_size);
    }

    else
        universe_size = universe_sizep;

    if (universe_size == 1)
        error("No room to start workers");

    printf("I'm a parent!!\n");

    MPI_Comm_spawn(worker_program, MPI_ARGV_NULL, universe_size - 1, MPI_INFO_NULL, 0, MPI_COMM_SELF, &everyone, MPI_ERRCODES_IGNORE);


    MPI_Finalize();

    return 0;
}

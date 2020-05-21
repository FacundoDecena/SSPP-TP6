#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void error(char* message)
{
    printf("%s", message);
    exit(1);
}

int main(int argc, char *argv[])
{

    MPI_Comm parent;
    int size;

    MPI_Init(&argc, &argv);

    MPI_Comm_get_parent(&parent);

    if (parent == MPI_COMM_NULL)
        error("No parent!");

    MPI_Comm_remote_size(parent, &size);

    printf("I'm tikito!!\n");

    if (size != 1)
        error("Something's wrong with the parent");

    MPI_Finalize();

    return 0;
}
#include <mpi.h>
#include <stdlib.h>
#include <string.h>

void FMPI_Barrier(MPI_Comm comm)
{
    int i, size, rank;
    int flag = 1;
    MPI_Status status;

    MPI_Comm_size(comm, &size);

    MPI_Comm_rank(comm, &rank);

    if (rank > 0)
    {
        MPI_Send(&flag, 1, MPI_INT, 0, 0, comm);
        MPI_Recv(&flag, 1, MPI_INT, 0, 0, comm, &status);
    }
    else
    {
        for (i = 1; i < size; i++)
        {
            MPI_Recv(&flag, 1, MPI_INT, i, 0, comm, &status);
        }
        for (i = 1; i < size; i++)
        {
            MPI_Send(&flag, 1, MPI_INT, i, 0, comm);
        }
    }
    return;
}

void FMPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
{

    int rank, size, i;

    MPI_Comm_size(comm, &size);

    MPI_Comm_rank(comm, &rank);

    if (rank == root)
    {
        for (i = 0; i < size; i++)
        {
            if (i != rank)
            {
                MPI_Send(buffer, count, datatype, i, 0, comm);
            }
        }
    }
    else
    {
        MPI_Recv(buffer, count, datatype, root, 0, comm, MPI_STATUS_IGNORE);
    }

    return;
}

void FMPI_Scatter(const void *send_data, int send_count, MPI_Datatype send_datatype,
                  void *recv_data, int recv_count, MPI_Datatype recv_datatype,
                  int root, MPI_Comm comm)
{

    int rank, size, i, send_size;

    MPI_Comm_size(comm, &size);

    MPI_Comm_rank(comm, &rank);

    FMPI_Barrier(comm);

    MPI_Type_size(send_datatype, &send_size);

    if (rank == root)
    {

        int sent = 0;
        for (i = 0; i < size; i++)
        {
            const void *data = (send_data + (sent * send_size));
            if (i == root)
                memcpy(recv_data, data, (size_t)(send_count * send_size));
            else
                MPI_Send(data, send_count, send_datatype, i, 0, comm);
            sent += send_count;
        }
    }
    else
        MPI_Recv(recv_data, recv_count, recv_datatype, 0, 0, comm, MPI_STATUS_IGNORE);

    return;
}

void FMPI_Gather(void *send_data, int send_count, MPI_Datatype send_datatype,
                 void *recv_data, int recv_count, MPI_Datatype recv_datatype,
                 int root, MPI_Comm comm)
{
    int rank, size, i;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    FMPI_Barrier(comm);

    if (rank == root)
    {
        MPI_Status status;
        int recv_size;
        MPI_Type_size(send_datatype, &recv_size);

        size_t data_size = (size_t)(recv_count * recv_size);
        void *data = malloc(data_size);

        for (i = 0; i < size; i++)
        {
            int offset;
            if (i != root) {
                MPI_Recv(data, recv_count, recv_datatype, MPI_ANY_SOURCE, MPI_ANY_TAG, comm, &status);
                offset = status.MPI_TAG;
            }
            else {
                memcpy(data, send_data, data_size);
                offset = root;
            }
            memcpy(recv_data + ((int)data_size * offset), data, data_size);
            
        }
    }
    else {
        MPI_Send(send_data, send_count, send_datatype, root, rank, comm);
    }
    
    return;
}

int FMPI_Reduce(void *sendbuffer, void *recvbuffer, int count,
                MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
{

    return 0;
}
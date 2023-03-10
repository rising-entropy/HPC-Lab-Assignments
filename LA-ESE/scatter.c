// 2019BTECS00058

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // maximum number of threads
    int globaldata[size];
    int localdata;

    // default thread that sets values
    if (rank == 0) {

        for (int i=0; i<size; i++)
            globaldata[i] = i;

        printf("1. Processor %d has data: ", rank);
        for (int i=0; i<size; i++)
            printf("%d ", globaldata[i]);
        printf("\n");
        printf("This data is now going to be scattered.\n");
    }
    //MPI_Scatter( const void* sendbuf , MPI_Count sendcount , MPI_Datatype sendtype , void* recvbuf , MPI_Count recvcount , MPI_Datatype recvtype , int root , MPI_Comm comm);
    MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("2. After scattering, processor %d has data %d\n", rank, localdata);

    MPI_Finalize();
    return 0;
}
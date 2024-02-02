/*
 * This is the C++ MPI communication backend. It is always pre-compiled in C++,
 * so qcomp is always resolved to the C++ complex type. We disable name-mangling 
 * (via extern "C") so that a user's C code can use these functions. When
 * pre-processor macro DISTRIBUTED_MODE is not defined, MPI is not necessary
 * (permitting compilation by non-MPI compilers).
 */

#ifdef DISTRIBUTED_MODE
#include <mpi.h>
#endif 

#include "comm.both"

#include <vector>
#include <iostream>


extern "C" void myCommFunc(qcomp* arr, int len) {
#ifdef DISTRIBUTED_MODE

    MPI_Init(NULL, NULL);

    int tag = 0;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
        MPI_Send(arr, len, MPI_QCOMP, 1, tag, MPI_COMM_WORLD);
    if (rank == 1) {
        std::vector<qcomp> recv(len);
        MPI_Recv(recv.data(), len, MPI_QCOMP, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        std::cout << "rank 1 received from rank 0:\n\t";
        for (int i=0; i<len; i++)
            std::cout << recv[i] << " ";
        std::cout << "\n";
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
#else
    std::cout << "(no messages passed; non-distributed)\n";
#endif
}

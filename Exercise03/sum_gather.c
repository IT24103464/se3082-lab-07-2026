#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *array = NULL;
    long long *recv_array = NULL;

    if (rank == 0) {
        array = (int *)malloc(N * sizeof(int));
        recv_array = (long long*)malloc(size * sizeof(long long));

        for (int i = 0; i < N; i++)
            array[i] = i + 1;

        printf("Root filled array with values 1 to %d\n", N);
    }

    double start = MPI_Wtime();

    int chunk_size = N / size;
    int local_chunk[chunk_size];
    long long local_sum = 0;

    MPI_Scatter(array, chunk_size, MPI_INT, local_chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++) {
        local_sum += local_chunk[i];
    }
        

    printf("  Rank %d: => local_sum = %lld\n", rank, local_sum);

    MPI_Gather(&local_sum, 1, MPI_LONG_LONG, recv_array, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        long long total_sum = 0;        
        for (int r = 0; r < size; r++) {
            total_sum += recv_array[r];
        }
        double elapsed = MPI_Wtime() - start;
        long long expected = (long long)N * (N + 1) / 2;
        printf("\n[Scatter] Total sum   = %lld\n", total_sum);
        printf("[Scatter] Expected    = %lld\n", expected);
        printf("[Scatter] Correct?    = %s\n", total_sum == expected ? "YES" : "NO");
        printf("[Scatter] Time        = %.4f sec\n", elapsed);
    }

    free(array);
    MPI_Finalize();
    return 0;
}
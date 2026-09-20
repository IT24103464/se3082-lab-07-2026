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

    if (rank == 0) {
        array = (int *)malloc(N * sizeof(int));

        for (int i = 0; i < N; i++)
            array[i] = i + 1;

        printf("Root filled array with values 1 to %d\n\n", N);
    }

    double start = MPI_Wtime();

    int chunk_size = N / size;
    int local_chunk[chunk_size];

    long long local_sum = 0;
    long long prefix_sum = 0;

    MPI_Scatter(array, chunk_size, MPI_INT, local_chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++) {
        local_sum += local_chunk[i];
    }

    MPI_Scan(&local_sum, &prefix_sum, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);

    long long sum_before_me = prefix_sum - local_sum;
    printf("    Rank %d: => local_sum = %lld\n", rank, local_sum);
    printf("    Rank %d: => prefix_sum = %lld\n", rank, prefix_sum);
    printf("    Rank %d: => sum_beofre_me = %lld\n", rank, prefix_sum - local_sum);

    /* Bonus verification */
    long long K = (long long)(rank + 1) * chunk_size;
    long long expected_prefix = K * (K + 1) / 2;

    printf("    Rank %d: expected      = %lld\n\n", rank, expected_prefix);

    if (rank == size - 1) {
        double elapsed = MPI_Wtime() - start;
        long long expected = (long long)N * (N + 1) / 2;
        printf("\n[AllReduce] Total sum   = %lld\n", prefix_sum);
        printf("[AllReduce] Expected    = %lld\n", expected);
        printf("[AllReduce] Correct?    = %s\n", prefix_sum == expected ? "YES" : "NO");
        printf("[AllReduce] Time        = %.4f sec\n", elapsed);
    }

    free(array);
    MPI_Finalize();
    return 0;
}
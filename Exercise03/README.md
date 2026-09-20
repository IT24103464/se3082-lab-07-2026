# Exercise 03 — MPI Gather

## Objective

This exercise improves the result collection method used in Exercise 02.

`MPI_Scatter` is still used to divide the original array into equal chunks. However, instead of using individual `MPI_Send` and `MPI_Recv` operations to return each partial sum to the root process, `MPI_Gather` collects all local sums using a single collective operation.

## Improvement from Exercise 02

**Exercise 02**

```text
MPI_Scatter
     ↓
Each rank calculates local_sum
     ↓
MPI_Send / MPI_Recv
     ↓
Root calculates total_sum
```

**Exercise 03**

```text
MPI_Scatter
     ↓
Each rank calculates local_sum
     ↓
MPI_Gather
     ↓
recv_array[] on Rank 0
     ↓
Root calculates total_sum
```

`MPI_Gather` collects one `local_sum` from every process, including Rank 0, and stores the values in rank order inside the receive array on the root process.

The root then manually adds the gathered values to obtain the final sum.

## Compile and Run

```bash
mpicc -o sum_gather program.c
mpirun -np 4 ./sum_gather
```

## Output

```text
Root filled array with values 1 to 1000000
  Rank 0: => local_sum = 31250125000
  Rank 3: => local_sum = 218750125000
  Rank 2: => local_sum = 156250125000
  Rank 1: => local_sum = 93750125000

[Gather] Total sum   = 500000500000
[Gather] Expected    = 500000500000
[Gather] Correct?    = YES
[Gather] Time        = 0.0235 sec
```

## Result

`MPI_Gather` successfully collected the partial sums from all 4 MPI processes into the root process.

The gathered values were manually summed by Rank 0, producing:

**500,000,500,000**

The calculated value matches the expected result, confirming that the implementation is correct.

The displayed rank order may vary between executions because MPI processes run concurrently.

## Proof

![Exercise 03 Output](image.png)
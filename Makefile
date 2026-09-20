MPICC = mpicc
NP = 4

EX1 = Exercise01/program
EX2 = Exercise02/sum_scatter
EX3 = Exercise03/sum_gather
EX4 = Exercise04/sum_reduce
EX5 = Exercise05/sum_allreduce
EX6 = Exercise06/sum_scan

all: $(EX1) $(EX2) $(EX3) $(EX4) $(EX5) $(EX6)

$(EX1): Exercise01/program.c
	$(MPICC) -o $(EX1) Exercise01/program.c

$(EX2): Exercise02/sum_scatter.c
	$(MPICC) -o $(EX2) Exercise02/sum_scatter.c

$(EX3): Exercise03/sum_gather.c
	$(MPICC) -o $(EX3) Exercise03/sum_gather.c

$(EX4): Exercise04/sum_reduce.c
	$(MPICC) -o $(EX4) Exercise04/sum_reduce.c

$(EX5): Exercise05/sum_allreduce.c
	$(MPICC) -o $(EX5) Exercise05/sum_allreduce.c

$(EX6): Exercise06/sum_scan.c
	$(MPICC) -o $(EX6) Exercise06/sum_scan.c

run: all
	@echo "===== Exercise 01 ====="
	mpirun -np $(NP) ./$(EX1)

	@echo "===== Exercise 02 ====="
	mpirun -np $(NP) ./$(EX2)

	@echo "===== Exercise 03 ====="
	mpirun -np $(NP) ./$(EX3)

	@echo "===== Exercise 04 ====="
	mpirun -np $(NP) ./$(EX4)

	@echo "===== Exercise 05 ====="
	mpirun -np $(NP) ./$(EX5)

	@echo "===== Exercise 06 ====="
	mpirun -np $(NP) ./$(EX6)

clean:
	rm -f $(EX1) $(EX2) $(EX3) $(EX4) $(EX5) $(EX6)
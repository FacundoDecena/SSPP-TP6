# Build Executable
SHELL=/bin/bash
# Overrides command line arguments
np = 1

all:
	mpicc -o ./build/ejercicio4 ejercicio4.c

	mpicc -o ./build/worker worker.c

clean:
	$(RM) ./build/*

run:
	mpirun -np $(np) ./build/ejercicio4

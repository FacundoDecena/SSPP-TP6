# Build Executable
SHELL=/bin/bash
# Overrides command line arguments
np = 6
mult = 18

  all:
	mpicc -g -std=c99 -Wall -o ./build/ejercicio3a ejercicio3a.c

	mpicc -g -std=c99 -Wall -o ./build/ejercicio3b ejercicio3b.c

  clean:
	$(RM) ./build/ejercicio*

  3a:
	mpirun -np $(np) ./build/ejercicio3a
  3b:
	mpirun -np $(np) ./build/ejercicio3b $(mult)
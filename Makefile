# Build Executable
SHELL=/bin/bash
# Overrides command line arguments
np = 16
npl = 6

clean:
	$(RM) ./build/*

ejercicio.1:
	mpicc -o ./build/ejercicio1A ./ejercicio1/helloWorld.c
	mpicc -o ./build/ejercicio1B ./ejercicio1/helloWorldB.c
	mpicc -o ./build/ejercicio1C ./ejercicio1/helloWorldC.c
	mpicc -o ./build/ejercicio1D ./ejercicio1/helloWorldD.c

ejercicio.1.localRun:
	mpirun -np $(npl) ./build/ejercicio1A
	mpirun -np $(npl) ./build/ejercicio1B
	mpirun -np $(npl) ./build/ejercicio1C
	mpirun -np $(npl) ./build/ejercicio1D

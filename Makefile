# Build Executable
SHELL=/bin/bash
# Overrides command line arguments
np = 16
npl = 6

ejercicio.1:
	mpicc -o ./build/ejercicio1A helloWorld.c
	mpicc -o ./build/ejercicio1B helloWorldB.c
	mpicc -o ./build/ejercicio1C helloWorldC.c
	mpicc -o ./build/ejercicio1D helloWorldD.c

ejercicio.1.localRun:
	mpirun -np $(npl) ./build/ejercicio1A
	mpirun -np $(npl) ./build/ejercicio1B
	mpirun -np $(npl) ./build/ejercicio1C
	mpirun -np $(npl) ./build/ejercicio1D

clean:
	$(RM) ./build/*
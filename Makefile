# Build Executable
SHELL=/bin/bash
# constants
np = 16
npl = 6
mult = 13

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

ejercicio.1.run:
	mpirun -np $(np) -f ./hostfile ./build/ejercicio1A
	mpirun -np $(np) -f ./hostfile ./build/ejercicio1B
	mpirun -np $(np) -f ./hostfile ./build/ejercicio1C
	mpirun -np $(np) -f ./hostfile ./build/ejercicio1D

ejercicio.2:
	mpicc -o ./build/ejercicio2 ./ejercicio2/ejercicio2.c

ejercicio.2.localRun:
	mpirun -np $(npl) ./build/ejercicio2

ejercicio.2.run:
	mpirun -np $(np) -f ./hostfile ./build/ejercicio2

ejercicio.3:
	mpicc -g -std=c99 -Wall -o ./build/ejercicio3a ejercicio3/ejercicio3a.c

	mpicc -g -std=c99 -Wall -o ./build/ejercicio3b ejercicio3/ejercicio3b.c

ejercicio.3.localRun:
	mpirun -np $(npl) ./build/ejercicio3a
	mpirun -np $(npl) ./build/ejercicio3b $(mult)

ejercicio.3.run:
	mpirun -np $(np) -f ./hostfileE3 ./build/ejercicio3a
	mpirun -np $(np) -f ./hostfileE3 ./build/ejercicio3b $(mult)
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

ejercicio.4:
	mpicc -o ./build/ejercicio4 ejercicio4/ejercicio4.c

	mpicc -o ./build/worker ejercicio4/worker.c

ejercicio.4.run:
	mpirun -np 1 -f ./hostfile ./build/ejercicio4

ejercicio.5:
	mpicc -o ./build/ejercicio5 ./ejercicio5/ejercicio5.c
	mpicc -o ./build/ejercicio5b ./ejercicio5/ejercicio5b.c


ejercicio.5.localRun:
	# Uso de Bcast y Barrier
	mpirun -np $(npl) ./build/ejercicio5
	# Uso de Scatter y Gather
	mpirun -np $(npl) ./build/ejercicio5b

ejercicio.5.run:
	# Uso de Bcast y Barrier
	mpirun -np $(np) -f ./hostfile ./build/ejercicio5
	# Uso de Scatter y Gather
	mpirun -np $(np) -f ./hostfile ./build/ejercicio5b
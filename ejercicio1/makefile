CC=mpicc
CFLAGS=-I

all: helloWorld helloWorldB

helloWorld: src/helloWorld.c
	$(CC) -o build/helloWorld src/helloWorld.c

helloWorldB: src/helloWorldB.c
	$(CC) -o build/helloWorldB src/helloWorldB.c


.PHONY: clean

clean:
	@ -rm -f build/*
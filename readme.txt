mpirun -np 16 -f ./hostfile ./main
mpicc -o main main.c
ssh sdyp02@cluster-lidic-r.unsl.edu.ar
ssh sdyp02@10.230.9.37
# distracted_processing
Poznan University of Technology

setup-mpi
mpicc sort2.c -o sort2
mpirun -hostfile maszyny -np 11 sort2 liczby_do_sortowania 

#include <mpi.h>
int main(int argc, char **argv)
{
	int rank, size, dane[2], eff[2];
	
	MPI_Init( &argc, &argv );

	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

	dane[0] = rank;
	dane[1] = 1;
	MPI_Allreduce( &dane, &eff, 2, MPI_INT, MPI_SUM , MPI_COMM_WORLD );
	printf("dane %d %d\n", eff[0], eff[1] );

	dane[0] = rank;
	dane[1] = size;
	MPI_Reduce( &dane, &eff, 2, MPI_INT, MPI_SUM ,0, MPI_COMM_WORLD );
	printf("dane at %d: %d %d\n", rank, eff[0], eff[1] );
	MPI_Finalize();
}

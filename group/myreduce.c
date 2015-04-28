#include <mpi.h>
int rank;

void func(void *a, void *b, int *len, MPI_Datatype *typ)
{
	int i;

	/*for (i=0;i<*len;i++)
	{
		b[i] = 2*a[i] + b[i];// + 2* a[i];
	}*/
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	printf(" My rank %d a %d b %d\n",rank,((int*)a)[0], ((int*)b)[0]);
        fflush(0);
    /// Dla 4 procesów:
    /// wykonuje tylko trzy razy!
    /// w pierwszym: 2*2+3
    /// w drugim: 2*1+7
    /// w trzecim: 2*0+9
	((int *)b)[0]=2* ((int*)a)[0] + ((int*)b)[0];
}

int main(int argc, char **argv)
{
	int size, dane[2]={0}, eff[2]={0};
	MPI_Op op;
	
	MPI_Init( &argc, &argv );

	MPI_Op_create( func, 0, &op);
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

	//sleep(1);
	dane[0] =  rank;
	//dane[1] = 2;
	//if ( rank<2)
	MPI_Reduce( &dane, &eff, 1, MPI_INT, op , 0, MPI_COMM_WORLD );
	MPI_Barrier( MPI_COMM_WORLD );
	MPI_Op_free(&op);

	printf("dane at %d: %d %d\n", rank, eff[0],  dane[0] );
        if (rank==0)
	printf("\n----\nDANE AT %d: %d %d\n---\n", rank, eff[0],  dane[0] );
	MPI_Finalize();
}

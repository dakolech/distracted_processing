#include <mpi.h>

#define SIZE 16
int main(int argc, char **argv)
{
	int size, rank;
	int recv[SIZE]={0}, send[SIZE]={0};	
	MPI_Init( &argc, &argv );
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if ( !rank)
	{
		int i;
		for (i=0;i<SIZE;i++)
			send[i]=i+1;
	}	
	MPI_Scatter( send, SIZE/size, MPI_INT, recv, SIZE/size, MPI_INT, 0, MPI_COMM_WORLD);

	printf("%d \n", recv[0]);
	{int i;
		for (i=0;i<SIZE/size;i++)
			send[i]=rank;
	}

	MPI_Gather( send, SIZE/size, MPI_INT, recv, SIZE/size, MPI_INT, 0, MPI_COMM_WORLD);

	if (!rank)
	{
		int i;
		for (i=1;i<SIZE;i++)
		{
			printf("[%d]=%d, ",i,recv[i]);
		}
	}
	
	MPI_Finalize();
}

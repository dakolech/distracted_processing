#include <mpi.h>
#include <stdio.h>
#define ROOT 0
#define MSG_TAG 100

int main(int argc, char **argv)
{
	int tid,size;
	MPI_Status status;

	MPI_Init(&argc, &argv); //Musi być w każdym programie na początku

	//printf("Checking!\n");
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &tid );
	//printf("My id is %d from %d\n",tid, size);

	int msg[2];

	if ( tid == ROOT)
	{
		msg[0] = tid;
		msg[1] = size;
		MPI_Send( msg, 2, MPI_INT, 1, MSG_TAG, MPI_COMM_WORLD );
		printf(" Wyslalem %d do 1\n", msg[0]);

		MPI_Recv(msg, 2, MPI_INT, 9, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("(%d) Otrzymalem %d od 9\n", tid, msg[0]);

	}
	else
	{
		int from = tid-1;
		MPI_Recv(msg, 2, MPI_INT, from, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("(%d) Otrzymalem %d od %d\n", tid,  msg[0], from);
		
		int destination = 0;
		if (tid+1 != 10)
		  destination = tid+1;
		
		msg[0] = tid;
		msg[1] = size;
		MPI_Send( msg, 2, MPI_INT, destination, MSG_TAG, MPI_COMM_WORLD );
		printf(" Wyslalem %d do %d\n", msg[0], destination );
	}

	MPI_Finalize(); // Musi być w każdym programie na końcu
}

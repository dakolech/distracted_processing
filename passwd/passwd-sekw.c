#include <mpi.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define PASSWD 1

/* 4 literowe
aa5UYq6trT5u.
bahAZ9Hk7SCf6
ddoo3WocSpthU
jkmD2RlhoMyuA
zzm4NUIIb7VIk
kkv864igyJC9o

5 literowe
aaSPfLTmjh3fU

6 literowe
aaLTdQr7DyHuU 
*/

char *stro="aaSPfLTmjh3fU";


int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int size,rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    char cmp[6]={0};

    char salt[3]={0};
    salt[0]=stro[0];
    salt[1]=stro[1];

    char * x;
    /* Ten fragment kodu nalezy _jakos_ zrównoleglić */
    /* pewnie będzie potrzebna jakaś pętla... */
    int i,j,k,l,m;
    for (i='a'; i<='z'; i++) {
      for (j='a'; j<='z'; j++) {
	for (k='a'; k<='z'; k++) {
	  for (l='a'; l<='z'; l++) {
	    for (m='a'; m<='z'; m++) {
	      cmp[0] = i;
	      cmp[1] = j;
	      cmp[2] = k;
	      cmp[3] = l;
	      cmp[4] = m;
	      
	      x=crypt(cmp, salt);
	      if ((strcmp(x,stro))==0)
	      {
		printf("Udalo sie: %s %s %s\n", cmp, x, stro);
	      }
	    }
	  }
	}
      }
    }
    

    if ((strcmp(x,stro))==0)
    {
	    //MPI_Send( &cmp, 5, MPI_INT, 1, PASSWD, MPI_COMM_WORLD);
            /* w docelowej wersji przeslac odgadnięte hasło masterowi */
	    printf("Udalo sie: %s %s %s\n", cmp, x, stro);
            MPI_Finalize();
	    exit(0);
    }
    /* Koniec fragmentu kodu */

    MPI_Finalize();
}

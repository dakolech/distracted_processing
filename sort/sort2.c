#include <mpi.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define SORT 1
#define END 2
#define TABSIZE 10

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int size,rank;
    int tablica[TABSIZE]={0};
    int sorted[TABSIZE]={-1};
    int max=-1;
    int tmp=-1;
    int i;
    int end=0;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc<2) {
	    MPI_Finalize();
	    printf("Za malo argumentow\n");
	    exit(0);
    }
    /*
        Szkielet dzieli procesy na trzy kategorie: wierzchołek, liście oraz pozostałe.
        W Twoim rozwiązaniu być może wystarczą tylko dwie kategorie
    */

    if (rank == 0) {
        /* Wczytywanie liczb do posortowania z pliku podanego jako pierwszy argument */
        printf("Otwieram plik\n");
	FILE *f;int i;
	f = fopen(argv[1],"r");
	for (i=0;i<TABSIZE;i++) fscanf(f, "%d", &(tablica[i]));
	for (i=0;i<TABSIZE;i++) printf("%d ", (tablica[i]));

        max=tablica[0];
        printf("\n------------\n");
        /**/

        /* Tutaj wstaw wysyłanie liczb do bezpośrednich następników wierzchołka */
	printf("%d: Wczytuje %d, wysylam\n", rank, max);
        for (i=0;i<TABSIZE;i++) {
	    MPI_Send( &tablica[i], 1, MPI_INT, 1, SORT, MPI_COMM_WORLD);
	    printf("MASTER: Wysylam %d\n", tablica[i]);
            // MPI_SEND( &(tablica[i]).....
            //MPI_SEND( skąd, ile, typ, do kogo, z jakim tagiem, MPI_COMM_WORLD)
        }
        /**/
        /* Zawiadamiamy, że więcej liczb do wysyłania nie będzie*/
        int dummy=-1;
	MPI_Send( &dummy, 1, MPI_INT, 1, END, MPI_COMM_WORLD); //koniec liczb

        /* Tutaj wstaw odbieranie posortowanych liczb */
        for (i=0;i<size-1;i++) {
	      MPI_Recv(&sorted[i], 1, MPI_INT, i+1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	      printf("MASTER: Odbieram %d\n", sorted[i]);
	//    MPI_Recv( gdzie, ile , jakiego typu, od kogo, z jakim tagiem, MPI_COMM_WORLD, &status);
        }

        /* Wyświetlanie posortowanej tablicy */
	//for (i=0;i<TABSIZE-(size-1);i++) {
        for (i=0;i<TABSIZE;i++) {
            printf("MASTER: Posortowane %d\n", sorted[i]);
        }
        printf("\n");

    } else if (rank==size-1) { //LISC 
      int liczba=-1;
        while (!end) {
	    MPI_Recv(&tmp, 1, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	    if (status.MPI_TAG==END) {
		end=1;
		MPI_Send( &liczba, 1, MPI_INT, 0, SORT, MPI_COMM_WORLD);
	     // cos jeszcze?
	    } else {
	    //cos jeszcze?
	      liczba=tmp;
	    } 
        }
    } else { //Ani wierzchołek, ani liść
	int liczba = -1;
        while (!end) {	    
	    MPI_Recv(&tmp, 1, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	    if (status.MPI_TAG==END) {
		end=1;
		 MPI_Send( &liczba, 1, MPI_INT, 0, SORT, MPI_COMM_WORLD);
		 MPI_Send( &tmp, 1, MPI_INT, rank+1, END, MPI_COMM_WORLD);
	    } else {
	      if (liczba==-1)
		liczba=tmp;
	      else {
		if (liczba>tmp) {		  
		  MPI_Send( &liczba, 1, MPI_INT, rank+1, SORT, MPI_COMM_WORLD);
		  liczba = tmp;
		} else{
		  MPI_Send( &tmp, 1, MPI_INT, rank+1, SORT, MPI_COMM_WORLD);
		}
	      }
	    }
        }
    }
   
    MPI_Finalize();
}

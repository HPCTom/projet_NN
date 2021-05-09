#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "mesure.h"
void CALCUL(){
  int a = 0;
  a++;
}

int main(int argc, char * argv[])
{
  int nb_run = 0;
  int N = 250;
  MPI_Init( &argc, &argv );

	while(nb_run < N){
    double temps_mpi[N];
    clock_t temps_clock[N];
    double temps_mpi_mesure_mesure[N];
    clock_t temps_clock_mesure_mesure[N];

    double t1 =  MPI_Wtime();
    clock_t a = rdtsc();

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &comm_size );


    //debut_mesure_opti(t1,a,rank);
    debut_mesure_scalabilite(t1,a,rank);
    //debut_mesure_stabilite(t1,a,rank);


    CALCUL(); // code à mesurer


    double t2 =  MPI_Wtime();
    clock_t b = rdtsc();


    //fin_mesure_opti(t1,a,t2,b,rank,temps_mpi,temps_clock,nb_run,N,argv[1]);
    fin_mesure_scalabilite(t1,a,t2,b,rank,temps_mpi,temps_clock,nb_run,N,comm_size);
    //fin_mesure_stabilite(t1,a,t2,b,rank,temps_mpi,temps_clock,nb_run,N,atoi(argv[1]));


	nb_run ++;
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}

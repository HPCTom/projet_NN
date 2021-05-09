#include "base_mesure.h"

void create_data_stabilite(){
  FILE *P_FICHIER = NULL;
  char NOM_FICHIER[30] = "aa_stabilité.dat";

  if(fopen(NOM_FICHIER, "r") == NULL){
    char title[1000] = "#abscisse \t stabilité \n";

    P_FICHIER = fopen(NOM_FICHIER, "w");

    fprintf(P_FICHIER,"%s",title);
    fclose(P_FICHIER);
  }
}

void debut_mesure_stabilite(double t1, clock_t a,int rank){

  if(rank == 0){
    FILE *P_FICHIER = NULL;
    char VAL[30];
    char NOM_FICHIER[30] = "aa_brut_stabilité.dat";
    P_FICHIER = fopen(NOM_FICHIER, "a");

    sprintf(VAL, "%f", t1);
    fprintf(P_FICHIER,"%s\t",VAL);

    fclose(P_FICHIER);
  }
}

void fin_mesure_stabilite(double t1, clock_t a,double t2, clock_t b,int rank,
                            double *temps_mpi, clock_t *temps_clock, int nb_run,int N, int abscisse){

  if(rank ==0){
    create_data_stabilite();
    FILE *P_FICHIER = NULL;
    char VAL[30];
    char NOM_FICHIER[30] = "aa_brut_stabilité.dat";
    P_FICHIER = fopen(NOM_FICHIER, "a");

    sprintf(VAL, "%f", t2);

    fprintf(P_FICHIER,"%s\t",VAL);
    sprintf(VAL, "%f", t2-t1);

    fprintf(P_FICHIER,"%s\n",VAL);

    fclose(P_FICHIER);

    temps_mpi[nb_run] = t2-t1;
    temps_clock[nb_run] = b-a;

    if(nb_run == N-1){
      FILE *P_FICHIER2 = NULL; /* pointeur sur FILE */
      char VAL2[30];
      char NOM_FICHIER2[30] = "aa_stabilité.dat";
      P_FICHIER2 = fopen(NOM_FICHIER2, "a");
      fprintf(P_FICHIER2," %d \t\t\t",abscisse);
      sprintf(VAL2, "%f", pourcent_ecart_moy(N,temps_mpi)); //stabilité
      fprintf(P_FICHIER2," %s\n",VAL2);
    }
  }
}

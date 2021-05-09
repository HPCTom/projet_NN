#include "base_mesure.h"

void create_data_opti(){
  FILE *P_FICHIER = NULL;
  char NOM_FICHIER[30] = "aa_opti.dat";

  if(fopen(NOM_FICHIER, "r") == NULL){
    char title[1000] = "#abscisse \t\t val \t\t err_inf \t err_sup \n";

    P_FICHIER = fopen(NOM_FICHIER, "w");

    fprintf(P_FICHIER,"%s",title);
    fclose(P_FICHIER);
  }
}

void debut_mesure_opti(double t1, clock_t a,int rank){

  if(rank == 0){
    FILE *P_FICHIER = NULL;
    char VAL[30];
    char NOM_FICHIER[30] = "aa_brut_opti.dat";
    P_FICHIER = fopen(NOM_FICHIER, "a");

    sprintf(VAL, "%f", t1);
    fprintf(P_FICHIER,"%s\t",VAL);

    fclose(P_FICHIER);
  }
}

void fin_mesure_opti(double t1, clock_t a,double t2, clock_t b,int rank,
                     double *temps_mpi, clock_t *temps_clock, int nb_run,int N,char *abscisse){
  if(rank ==0){
    create_data_opti();
    FILE *P_FICHIER = NULL;
    char VAL[30];
    char NOM_FICHIER[30] = "aa_brut_opti.dat";
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
      char NOM_FICHIER2[30] = "aa_opti.dat";
      P_FICHIER2 = fopen(NOM_FICHIER2, "a");
      fprintf(P_FICHIER2," \"%s\" \t",abscisse); //
      sprintf(VAL2, "%f", moyenne(N,temps_mpi)); //moyenne
      fprintf(P_FICHIER2," %s \t ",VAL2);
      sprintf(VAL2, "%f", t2-t1-ecart_type(N,temps_mpi)); // moyenne - ecart-type
      fprintf(P_FICHIER2,"%s \t ",VAL2);
      sprintf(VAL2, "%f", t2-t1+ecart_type(N,temps_mpi)); // moyenne + ecart-type
      fprintf(P_FICHIER2,"%s \t \n",VAL2);
    }
  }
}

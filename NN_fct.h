#include "NN_init.h"

long double sigmoid(long double x)
{ return 1 / (1 + exp(-x)); }

long double d_sigmoid(long double x)
{ return sigmoid(x) * (1 - sigmoid(x)); }

void transpose(long double *W_XT,long double *W_X, int Taille_output, int Taille_layer){
		for(int i = 0; i < Taille_output; i++){
			for(int j = 0; j < Taille_layer; j++){
        int offset1 = i * Taille_layer + j;
        int offset2 = j * Taille_output + i;
				W_XT[offset2] = W_X[offset1];
			}
		}
    /*
    printf("W_O \n");
    int row, columns;
    for (row=0; row<TAILLE_OUTPUT; row++)
    {
      for(columns=0; columns<TAILLE_LAYER; columns++)
      {
        int offset = row * TAILLE_LAYER + columns;
        printf("%Lf     ", W_X[offset]);
      }
      printf("\n");
    }
    printf("W_OT\n");
    int row2, columns2;
    for(row2=0; row2<TAILLE_LAYER; row2++)
    {
      for (columns2=0; columns2<TAILLE_OUTPUT; columns2++)
      {
        int offset2 = row2 * TAILLE_OUTPUT + columns2;
        printf("%Lf     ", W_XT[offset2]);
      }
      printf("\n");
    }
    */
	}

void multiplAV(long double *A, long double *V, long double *ans, int Taille_layer, int Taille_ouput){
  int row, columns;
  for(row=0; row<TAILLE_LAYER; row++)
  {
    for (columns=0; columns<TAILLE_OUTPUT; columns++)
    {
      int offset = row * TAILLE_OUTPUT + columns;
      ans[row] += A[offset]*V[columns];
			//printf("anss = %Lf\n",ans[row]);
    }
  }
}

void fct_cout(long double *SOLUTION,long double *OUTPUT,long double *COUT,int n, long double *Solution,
              long double *Output,int Taille_output){
	COUT[0] = 0;
  for (int j=0; j<Taille_output; j = j+1){
    COUT[0] += pow((SOLUTION[j]-OUTPUT[j]),2);;
  }
  COUT[0] = COUT[0]/2;
}

void fct_eta(long double *eta){
	eta[0] = 1;
}

void resultat(long double *OUTPUT,long double *SOLUTION){
	if (SOLUTION[0] == 1.0){
		printf("L'image est cancéreuse\n");
		if (OUTPUT[1]-OUTPUT[0] < 0){
			printf("Le réseau détermine que l'image est cancéreuse\n");
			printf("PARFAIT !\n");
		}
		else{
			printf("Le réseau détermine que l'image n'est pas cancéreuse\n");
			printf("Sadge ...\n");
		}
	}
	else{
		printf("L'image n'est pas cancéreuse\n");
		if (OUTPUT[1]-OUTPUT[0] < 0){
			printf("Le réseau détermine que l'image est cancéreuse\n");
			printf("Sadge ...\n");
		}
		else{
			printf("Le réseau détermine que l'image n'est pas cancéreuse\n");
			printf("PARFAIT !\n");
		}
	}
 }

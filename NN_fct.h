#include "NN_init.h"

long double sigmoid(long double x)
{ return 1 / (1 + exp(-x)); }

long double d_sigmoid(long double x)
{ return sigmoid(x) * (1 - sigmoid(x)); }

void transpose(long double *W_XT,long double *W_X, int Taille_output, int Taille_layer){
		//fct qui transpose une matrice stockée dans un tableau 1D
		for(int i = 0; i < Taille_output; i++){
			for(int j = 0; j < Taille_layer; j++){
        int offset1 = i * Taille_layer + j;
        int offset2 = j * Taille_output + i;
				W_XT[offset2] = W_X[offset1];
			}
		}
	}

void multiplAV(long double *A, long double *V, long double *ans, int Taille_layer,
							 int Taille_ouput){
//fct qui effectue une mutiliplication matrice vecteur pour une matrice stockée dans un tableau 1D
  int row, columns;
  for(row=0; row<TAILLE_LAYER; row++)
  {
    for (columns=0; columns<TAILLE_OUTPUT; columns++)
    {
      int offset = row * TAILLE_OUTPUT + columns;
      ans[row] += A[offset]*V[columns];
    }
  }
}

void fct_cout(long double *SOLUTION,long double *OUTPUT,long double *COUT,
							long double *Solution,long double *Output,int Taille_output){
	//Calcul le cout pour la condtion d'arret
	COUT[0] = 0;
  for (int j=0; j<Taille_output; j = j+1){
    COUT[0] += pow((SOLUTION[j]-OUTPUT[j]),2);;
  }
  COUT[0] = COUT[0]/2;
}

void fct_eta(long double *eta){
	eta[0] = 1;
}

void mem_0(long double *LAYER,long double *OUTPUT,long double *ans,int Taille_layer,
					 int Taille_output){
	//réinitialise LAYER et OUTPUT à 0 pour la front_prop et ans pour error_layer
	memset(LAYER,0.0,Taille_layer*sizeof(long double));
	memset(OUTPUT,0.0,Taille_output*sizeof(long double));
	memset(ans,0.0,Taille_layer*sizeof(long double));
}

void resultat(long double *OUTPUT,long double *SOLUTION,long double *COUT){
	printf("OUTPUT[0] = %Lf \n",OUTPUT[0]);
	printf("OUTPUT[1] = %Lf \n",OUTPUT[1]);
	printf("COUT = %Lf \n\n\n",COUT[0]);
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

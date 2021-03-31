#include "NN_init.h"

long double sigmoid(long double x){
	return 1 / (1 + exp(-x));
	// if (x<0){
	// 	return 0;
	// }
	// else{
	// 	return x;
	// }
}

long double d_sigmoid(long double x){
	return sigmoid(x) * (1 - sigmoid(x));
	// if (x<0){
	// 	return 0;
	// }
	// else{
	// 	return 1;
	// }
}

void transpose(long double *W_XT,long double *W_X){
		//fct qui transpose une matrice stockée dans un tableau 1D
		for(int i = 0; i < TAILLE_OUTPUT; i++){
			for(int j = 0; j < TAILLE_LAYER; j++){
        int offset1 = i * TAILLE_LAYER + j;
        int offset2 = j * TAILLE_OUTPUT + i;
				W_XT[offset2] = W_X[offset1];
			}
		}
	}

void multiplAV(long double *A, long double *V, long double *ans){
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

void fct_cout(long double *SOLUTION,long double *OUTPUT,long double *COUT){
	//Calcul le cout pour la condtion d'arret
	COUT[0] = 0;
  for (int j=0; j<TAILLE_OUTPUT; j = j+1){
    COUT[0] += pow((SOLUTION[j]-OUTPUT[j]),2);
  }
  COUT[0] = COUT[0]/2;
}

void fct_eta(long double *eta){
	//Taux d'apprentissage
	eta[0] = 1.5;
}

void mem_0(long double *LAYER,long double *OUTPUT){
	//réinitialise LAYER et OUTPUT à 0 pour la front_prop
	memset(LAYER,0.0,TAILLE_LAYER*sizeof(long double));
	memset(OUTPUT,0.0,TAILLE_OUTPUT*sizeof(long double));
}

void free_all(long double *INPUT,long double *LAYER,long double *OUTPUT,long double *SOLUTION,long double *COUT,
							long double *ERROR_OUTPUT,long double *ERROR_LAYER,long double *W_L,long double *W_O,
							long double *W_OT,long double *b_L,long double *b_O,long double *Z_L,long double *Z_l,long double *ans,
							long double *eta){
	free(INPUT);
	free(LAYER);
	free(OUTPUT);
	free(SOLUTION);
	free(COUT);
	free(ERROR_OUTPUT);
	free(ERROR_LAYER);
	free(W_L);
	free(W_O);
	free(W_OT);
	free(b_L);
	free(b_O);
	free(Z_L);
	free(Z_l);
	free(ans);
	free(eta);
}

void resultat(long double *OUTPUT,long double *SOLUTION,long double *COUT,int run, int pas){
	//Affichage des runs
	if(run % pas == 0){
			printf("                                                  				run : %d\n",run);
	printf("OUTPUT[0] = %Lf \n",OUTPUT[0]);
	printf("OUTPUT[1] = %Lf \n",OUTPUT[1]);
	printf("COUT = %Lf \n",COUT[0]);
	if (SOLUTION[0] == 1.0){
			printf("L'image est cancéreuse                                ++++\n");
		if (OUTPUT[1]-OUTPUT[0] < 0){
			printf("Le réseau détermine que l'image est cancéreuse        ++++\n");
			printf("PARFAIT !\n \n");
		}
		else{
			printf("Le réseau détermine que l'image n'est pas cancéreuse  ----\n");
			printf("NUL !\n \n");
		}
	}
	else{
			printf("L'image n'est pas cancéreuse                          ----\n");
		if (OUTPUT[1]-OUTPUT[0] < 0){
			printf("Le réseau détermine que l'image est cancéreuse        ++++\n");
			printf("NUL !\n \n");
		}
		else{
			printf("Le réseau détermine que l'image n'est pas cancéreuse  ----\n");
			printf("PARFAIT !\n \n");
		}
	}
 }
}

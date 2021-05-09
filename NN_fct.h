#include "NN_init.h"

long double sigmoid(long double x){
	return 1 / (1 + exp(-x));
}

long double d_sigmoid(long double x){
	return sigmoid(x) * (1 - sigmoid(x));
}

long double relu(long double x){
	if (x<0){
	 	return 0;
	}
	else{
	 	return x;
	}
}

long double d_relu(long double x){
	if (x<0){
		return 0;
	}
	else{
		return 1;
	}
}

void transpose(long double *W_XT,long double *W_X, int TAILLEONE,
							 int TAILLETWO){
		//fct qui transpose une matrice stockée dans un tableau 1D
		for(int i = 0; i < TAILLEONE; i++){
			for(int j = 0; j < TAILLETWO; j++){
        int offset1 = i * TAILLETWO + j;
        int offset2 = j * TAILLEONE + i;
				W_XT[offset2] = W_X[offset1];
			}
		}
	}

void multiplAV(long double *A, long double *V, long double *ans,
	 						 int TAILLEONE, int TAILLETWO){
//fct qui effectue une mutiliplication matrice vecteur pour une matrice stockée dans un tableau 1D
  int row, columns;
  for(row=0; row<TAILLEONE; row++)
  {
    for (columns=0; columns<TAILLETWO; columns++)
    {
      int offset = row * TAILLETWO + columns;
      ans[row] += A[offset]*V[columns];
    }
  }
}

void fct_cout(long double *SOLUTION,long double *OUTPUT,long double *COUT, int run){
	//Calcul le cout pour la condtion d'arret
	COUT[0] = 0;
  for (int j=0; j<TAILLE_OUTPUT; j = j+1){
    COUT[0] += pow(fabs(SOLUTION[j]-OUTPUT[j]),2);
  }
  COUT[0] = COUT[0]/2;
}

void fct_eta(long double *eta,int run){
	//Taux d'apprentissage
	if(run%100000 == 0){
		eta[0] = eta[0] - (eta[0]*5/100);
	}

}

void mem_0(long double *LAYER, long double *LAYERII, long double *LAYERIII,
	 				 long double *OUTPUT){
	//réinitialise LAYER et OUTPUT à 0 pour la front_prop
	memset(LAYER,0.0,TAILLE_LAYER*sizeof(long double));
	memset(LAYERII, 0.0, TAILLE_LAYERII*sizeof(long double));
	memset(LAYERIII, 0.0, TAILLE_LAYERIII*sizeof(long double));
	memset(OUTPUT,0.0,TAILLE_OUTPUT*sizeof(long double));
}

void free_all(long double *INPUT,long double *LAYER, long double *LAYERII,
	 						long double *LAYERIII, long double *OUTPUT,long double *SOLUTION,
							long double *COUT,long double *ERROR_OUTPUT,long double *ERROR_LAYERIII,
							long double *ERROR_LAYERII, long double *ERROR_LAYER, long double *W_L,
							long double *W_LII, long double *W_LIII, long double *W_O,
							long double *W_OT, long double *W_LIIIT, long double *W_LIIT,
							long double *b_L, long double *b_LII, long double *b_LIII,
							long double *b_O,long double *Z_L,long double *Z_lIII, long double *Z_lII,
							long double *Z_l, long double *ans3, long double *ans2, long double *ans,
							long double *eta, long double *IMAGE, long double *CONVOLUTION,
							long double *W_C, long double *POOLING, long double *CONVOLUTION2,
							long double *W_C2, long double *POOLING2){
	//free(INPUT);
	free(LAYER);
	free(LAYERII);
	free(LAYERIII);
	free(OUTPUT);
	free(SOLUTION);
	free(COUT);
	free(ERROR_OUTPUT);
	free(ERROR_LAYERIII);
	free(ERROR_LAYERII);
	free(ERROR_LAYER);
	free(W_L);
	free(W_LII);
	free(W_LIII);
	free(W_O);
	free(W_OT);
	free(W_LIIIT);
	free(W_LIIT);
	free(b_L);
	free(b_LII);
	free(b_LIII);
	free(b_O);
	free(Z_L);
	free(Z_lIII);
	free(Z_lII);
	free(Z_l);
	free(ans3);
	free(ans2);
	free(ans);
	free(eta);
	free(IMAGE);
	free(CONVOLUTION);
	free(W_C);
	free(POOLING);
	free(CONVOLUTION2);
	free(W_C2);
	free(POOLING2);
}

void resultat(long double *OUTPUT, long double *SOLUTION, long double *COUT,
							int run, int pas, int nb_0, int nb_1, int *fauxpos, int *fauxneg,
							int *bonneg, int *bonpos, float *bon, float *faux, float *null){
if(run % pas == 0){
		printf("                                                  		           run : %d\n",run);
		printf("                                                  			  NB 0 : %d\n",nb_0);
		printf("                                                  			  NB 1 : %d\n",nb_1);
printf("OUTPUT = %Lf \n",OUTPUT[0]);
//printf("OUTPUT[1] = %Lf \n",OUTPUT[1]);
printf("COUT = %Lf \n",COUT[0]);

///////////////////////
if (SOLUTION[0] == 1.0){
			printf("L'image est cancéreuse                                          ++++\n");
	if (OUTPUT[0] < 0.5){
			printf("Le réseau détermine que l'image n'est pas cancéreuse            ----\n");
			printf("FAUX !\n\n");
			*fauxneg = *fauxneg+1;
			*faux = *fauxpos + *fauxneg;
			printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
			printf("NB BON NEGATIF: %d\n",*bonneg);
			printf("NB BON POSITIF : %d\n",*bonpos);
			printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
			printf("NB FAUX NEGATIF : %d\n", *fauxneg);
			printf("NB FAUX POSITIF : %d\n", *fauxpos);
			printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
	}
		else if (OUTPUT[0] > 0.5){
			printf("Le réseau détermine que l'image est cancéreuse                  ++++\n");
				printf("BON !\n\n");
				*bonpos = *bonpos + 1 ;
				*bon = *bonneg+ *bonpos;
				printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
				printf("NB BON NEGATIF: %d\n",*bonneg);
				printf("NB BON POSITIF : %d\n",*bonpos);
				printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
				printf("NB FAUX NEGATIF : %d\n", *fauxneg);
				printf("NB FAUX POSITIF : %d\n", *fauxpos);
				printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
		}
		else{
			printf("Le réseau ne peut pas conclure convenablement                   0000\n");
			*null = *null+1;
		}
	}


///////////////////////
else{
			printf("L'image n'est pas cancéreuse                                    ----\n");
if (OUTPUT[0] < 0.5){
			printf("Le réseau détermine que l'image n'est pas cancéreuse            ----\n");
		printf("BON !\n\n");
		*bonneg = *bonneg + 1 ;
		*bon = *bonpos + *bonneg;
		printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
		printf("NB BON NEGATIF: %d\n",*bonneg);
		printf("NB BON POSITIF : %d\n",*bonpos);
		printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
		printf("NB FAUX NEGATIF : %d\n", *fauxneg);
		printf("NB FAUX POSITIF : %d\n", *fauxpos);
		printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
}
	else if (OUTPUT[0] > 0.5){
			printf("Le réseau détermine que l'image est cancéreuse                  ++++\n");
			printf("FAUX !\n \n");
			*fauxpos = *fauxpos+1;
			*faux = *fauxneg + *fauxpos;
			printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
			printf("NB BON NEGATIF: %d\n",*bonneg);
			printf("NB BON POSITIF : %d\n",*bonpos);
			printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
			printf("NB FAUX NEGATIF : %d\n", *fauxneg);
			printf("NB FAUX POSITIF : %d\n", *fauxpos);
			printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
		}
		else{
			printf("Le réseau ne peut pas conclure convenablement                   0000\n");
			printf("NULL !\n\n");
			*null = *null + 1;
			printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
			printf("NB BON NEGATIF: %d\n",*bonneg);
			printf("NB BON POSITIF : %d\n",*bonpos);
			printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
			printf("NB FAUX NEGATIF : %d\n", *fauxneg);
			printf("NB FAUX POSITIF : %d\n", *fauxpos);
			printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
		}
	}
}
else{
	if (SOLUTION[0] == 1.0){
		if (OUTPUT[0] < 0.5){
			*fauxneg = *fauxneg+1;
			*faux = *fauxpos + *fauxneg;
		}
		else if (OUTPUT[0] > 0.5){
			*bonpos = *bonpos + 1;
			*bon = *bonpos + *bonneg;
		}
		else{
			*null = *null+1;
		}
	}
	else{
		if (OUTPUT[0] < 0.5){
			*bonneg = *bonneg + 1 ;
			*bon = *bonpos + *bonneg;
		}
		else if (OUTPUT[0] > 0.5){
			*fauxpos = *fauxpos+1;
			*faux = *fauxneg + *fauxpos;
		}
		else{
			*null = *null + 1;
		}
	}
}
}


void resultat2(long double *OUTPUT, long double *SOLUTION, long double *COUT,
							int run, int pas, int nb_0, int nb_1, int *fauxpos, int *fauxneg,
							int *bonneg, int *bonpos, float *bon, float *faux, float *null){
	//Affichage des runs
	if(run % pas == 0){
			printf("                                                  		           run : %d\n",run+1);
			printf("                                                  			  NB 0 : %d\n",nb_0);
			printf("                                                  			  NB 1 : %d\n",nb_1);
	printf("OUTPUT[0] = %Lf \n",OUTPUT[0]);
	printf("OUTPUT[1] = %Lf \n",OUTPUT[1]);
	printf("COUT = %Lf \n",COUT[0]);

	///////////////////////
	if (SOLUTION[0] == 1.0){
					printf("L'image est cancéreuse                                        ++++\n");
		if (OUTPUT[1]-OUTPUT[0] <= 0){
			if(fabs(OUTPUT[1]-OUTPUT[0]) > 0.8){
					printf("Le réseau détermine que l'image n'est pas cancéreuse          ----\n");
				printf("FAUX !\n\n");
				*fauxneg = *fauxneg+1;
				*faux = *fauxpos + *fauxneg;
				printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
				printf("NB BON NEGATIF: %d\n",*bonneg);
				printf("NB BON POSITIF : %d\n",*bonpos);
				printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
				printf("NB FAUX NEGATIF : %d\n", *fauxneg);
				printf("NB FAUX POSITIF : %d\n", *fauxpos);
				printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
			}
			else{
					printf("Le réseau ne peut pas conclure convenablement                 0000\n");
				printf("NULL !\n\n");
				*null = *null + 1;
				printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
				printf("NB BON NEGATIF: %d\n",*bonneg);
				printf("NB BON POSITIF : %d\n",*bonpos);
				printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
				printf("NB FAUX NEGATIF : %d\n", *fauxneg);
				printf("NB FAUX POSITIF : %d\n", *fauxpos);
				printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
		}
		}
			else if (OUTPUT[1]-OUTPUT[0] >= 0){
				if(fabs(OUTPUT[1]-OUTPUT[0]) > 0.8){
					printf("Le réseau détermine que l'image est cancéreuse                ++++\n");
					printf("BON !\n\n");
					*bonpos = *bonpos + 1 ;
					*bon = *bonneg+ *bonpos;
					printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
					printf("NB BON NEGATIF: %d\n",*bonneg);
					printf("NB BON POSITIF : %d\n",*bonpos);
					printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
					printf("NB FAUX NEGATIF : %d\n", *fauxneg);
					printf("NB FAUX POSITIF : %d\n", *fauxpos);
					printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
				}
				else{
					printf("Le réseau ne peut pas conclure convenablement                 0000\n");
					printf("NULL !\n\n");
					*null = *null + 1;
					printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
					printf("NB BON NEGATIF: %d\n",*bonneg);
					printf("NB BON POSITIF : %d\n",*bonpos);
					printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
					printf("NB FAUX NEGATIF : %d\n", *fauxneg);
					printf("NB FAUX POSITIF : %d\n", *fauxpos);
					printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
			}
			}
		}


	///////////////////////
	else{
					printf("L'image n'est pas cancéreuse                                  ----\n");
	if (OUTPUT[1]-OUTPUT[0] <= 0){
		if(fabs(OUTPUT[1]-OUTPUT[0]) > 0.8){
					printf("Le réseau détermine que l'image n'est pas cancéreuse          ----\n");
		printf("BON !\n\n");
		*bonneg = *bonneg + 1 ;
		*bon = *bonpos + *bonneg;
		printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
		printf("NB BON NEGATIF: %d\n",*bonneg);
		printf("NB BON POSITIF : %d\n",*bonpos);
		printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
		printf("NB FAUX NEGATIF : %d\n", *fauxneg);
		printf("NB FAUX POSITIF : %d\n", *fauxpos);
		printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
		}
		else{
					printf("Le réseau ne peut pas conclure convenablement                 0000\n");
			printf("NULL !\n\n");
			*null = *null + 1;
			printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
			printf("NB BON NEGATIF: %d\n",*bonneg);
			printf("NB BON POSITIF : %d\n",*bonpos);
			printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
			printf("NB FAUX NEGATIF : %d\n", *fauxneg);
			printf("NB FAUX POSITIF : %d\n", *fauxpos);
			printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
		}
	}
		else if (OUTPUT[1]-OUTPUT[0] >= 0){
			if(fabs(OUTPUT[1]-OUTPUT[0]) > 0.8){
					printf("Le réseau détermine que l'image est cancéreuse                ++++\n");
				printf("FAUX !\n \n");
				*fauxpos = *fauxpos+1;
				*faux = *fauxneg + *fauxpos;
				printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
				printf("NB BON NEGATIF: %d\n",*bonneg);
				printf("NB BON POSITIF : %d\n",*bonpos);
				printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
				printf("NB FAUX NEGATIF : %d\n", *fauxneg);
				printf("NB FAUX POSITIF : %d\n", *fauxpos);
				printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
			}
			else{
					printf("Le réseau ne peut pas conclure convenablement                 0000\n");
				printf("NULL !\n\n");
				*null = *null + 1;
				printf("NB BON : %.0f (%.2f %%)\n",*bon,(*bon)*100/run);
				printf("NB BON NEGATIF: %d\n",*bonneg);
				printf("NB BON POSITIF : %d\n",*bonpos);
				printf("NB FAUX : %.0f (%.2f %%)\n",*faux,(*faux)*100/run);
				printf("NB FAUX NEGATIF : %d\n", *fauxneg);
				printf("NB FAUX POSITIF : %d\n", *fauxpos);
				printf("NB NULL : %.0f (%.2f %%)\n",*null,(*null)*100/run);
			}
		}
	}
}
else{
	if (SOLUTION[0] == 1.0){
		if (OUTPUT[1]-OUTPUT[0] <= 0){
			if(fabs(OUTPUT[1]-OUTPUT[0]) > 0.8){
				*fauxneg = *fauxneg+1;
				*faux = *fauxpos + *fauxneg;
			}
			else{
				*null = *null + 1;
		}
		}
			else if (OUTPUT[1]-OUTPUT[0] >= 0){
				if(fabs(OUTPUT[1]-OUTPUT[0]) > 0.8){
					*bonpos = *bonpos + 1 ;
					*bon = *bonneg+ *bonpos;
				}
				else{
					*null = *null + 1;
			}
			}
		}
	else{
	if (OUTPUT[1]-OUTPUT[0] <= 0){
		if(fabs(OUTPUT[1]-OUTPUT[0]) > 0.8){
		*bonneg = *bonneg + 1 ;
		*bon = *bonpos + *bonneg;
		}
		else{
			*null = *null + 1;
		}
	}
		else if (OUTPUT[1]-OUTPUT[0] >= 0){
			if(fabs(OUTPUT[1]-OUTPUT[0]) > 0.8){
				*fauxpos = *fauxpos+1;
				*faux = *fauxneg + *fauxpos;
			}
			else{
				*null = *null + 1;
			}
		}
	}
}
}

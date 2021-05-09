#include "NN_fct.h"

/********************************************************
Cette fonction réalise l'opération de convulation sur
la matrice contenant les valeurs des pixel de l'image 
 avec la matrice de poid qui lui est associée
************************************************************/
void convolution(long double *W_C, long double *CONVOLUTION, long double *IMAGE){
	for(int i=0; i<(TAILLE_IMAGE-2); i++){
		for (int j=0; j<(TAILLE_IMAGE-2); j++){
			int offset2 = i*(TAILLE_IMAGE-2)+j;
			for(int x=0; x<3; x++){
				for(int y=0; y<3; y++){
					int offset = x*3+y;
					CONVOLUTION[offset2]= relu(W_C[offset] * IMAGE[TAILLE_IMAGE*(x+i)+y+j]);
				}
			}
		}
	}
}

void pooling(long double *CONVOLUTION, long double *POOLING){
	int compare, compare2;
	for(int k=0; k<TAILLE_POOL; k++){
		for (int i=0; i<TAILLE_IMAGE-2; i+=2){
			for (int j=0; j<TAILLE_IMAGE-2; j+=2){
				int offset = (TAILLE_IMAGE-2)*i+j;
				if(CONVOLUTION[offset]<CONVOLUTION[offset+1]){
					compare = CONVOLUTION[offset+1];
				}
				else{
					compare = CONVOLUTION[offset];
				}
				offset += TAILLE_IMAGE-2;
				if(CONVOLUTION[offset]<CONVOLUTION[offset+1]){
					compare2 = CONVOLUTION[offset+1];
				}
				else{
					compare2 = CONVOLUTION[offset];
				}
				if(compare < compare2){
					POOLING[k] = compare2;
				}
				else{
					POOLING[k] = compare;
				}
			}
		}
	}
}

void convolution2(long double *W_C2, long double *CONVOLUTION2, long double *POOLING){
	for(int i=0; i<(DIM_POOL-2); i++){
		for (int j=0; j<(DIM_POOL-2); j++){
			int offset2 = i*(DIM_POOL-2)+j;
			for(int x=0; x<3; x++){
				for(int y=0; y<3; y++){
					int offset = x*3+y;
					CONVOLUTION2[offset2] = relu(W_C2[offset] * POOLING[DIM_POOL*(x+i)+y+j]);
				}
			}
		}
	}
}

void pooling2(long double *CONVOLUTION2, long double *POOLING2){
	int compare, compare2;
	for(int k=0; k<TAILLE_POOLII; k++){
		for (int i=0; i<DIM_POOL-2; i+=2){
			for (int j=0; j<DIM_POOL-2; j+=2){
				int offset = (DIM_POOL-2)*i+j;
				if(CONVOLUTION2[offset]<CONVOLUTION2[offset+1]){
					compare = CONVOLUTION2[offset+1];
				}
				else{
					compare = CONVOLUTION2[offset];
				}
				offset += DIM_POOL-2;
				if(CONVOLUTION2[offset]<CONVOLUTION2[offset+1]){
					compare2 = CONVOLUTION2[offset+1];
				}
				else{
					compare2 = CONVOLUTION2[offset];
				}
				if(compare < compare2){
					POOLING2[k] = compare2;
				}
				else{
					POOLING2[k] = compare;
				}
			}
		}
	}
}

/************************************************************************
	front_prop realise la front propagation et calcul les valeurs
	de l'output à partir des données contenu dans l'input
**************************************************************************/

void front_prop(long double *Z_L,long double *Z_lIII,long double *Z_lII,
								long double *Z_l, long double *INPUT,long double *LAYER,
								long double *LAYERII, long double *LAYERIII, long double *OUTPUT,
								long double *b_L, long double *b_LII, long double *b_LIII,
								long double *b_output,long double* W_L, long double *W_LII,
								long double *W_LIII, long double* W_O){
		//premiere propagation Input à Layer
	//	#pragma omp parallel shared(Z_L, Z_lIII, Z_lII, Z_l,INPUT,LAYER,LAYERII,LAYERIII,OUTPUT,b_L,b_LII, b_LIII,b_output,W_L,W_LII, W_LIII, W_O)
		//{
			#pragma omp for nowait
		for (int i=0; i<TAILLE_LAYER; i++){
			for (int j=0; j<TAILLE_INPUT; j = j+1){
        int offset = i * TAILLE_INPUT + j;
				//#pragma omp atomic
        LAYER[i] = LAYER[i] + W_L[offset]*INPUT[j];
			}
      Z_l[i] = LAYER[i];
			LAYER[i] = sigmoid(LAYER[i]-b_L[i]);
		 }
		 #pragma omp for nowait
		 for (int i=0; i<TAILLE_LAYERII; i++){
 			for (int j=0; j<TAILLE_LAYER; j = j+1){
         int offset = i * TAILLE_LAYER + j;
         LAYERII[i] = LAYERII[i] + W_LII[offset]*LAYER[j];
 			}
       Z_lII[i] = LAYERII[i];
 			LAYERII[i] = sigmoid(LAYERII[i]-b_LII[i]);
 		 }
		 #pragma omp for nowait
		 for (int i=0; i<TAILLE_LAYERIII; i++){
 			for (int j=0; j<TAILLE_LAYERII; j = j+1){
         int offset = i * TAILLE_LAYERII + j;
				// #pragma omp atomic
         LAYERIII[i] = LAYERIII[i] + W_LIII[offset]*LAYERII[j];
 			}
       Z_lIII[i] = LAYERIII[i];
 			LAYERIII[i] = sigmoid(LAYERIII[i]-b_LIII[i]);
 		 }
	// }
		 //deuxième propagation Layer à Output
		for (int i=0; i<TAILLE_OUTPUT; i++){
			for (int j=0; j<TAILLE_LAYERIII; j = j+1){
        int offset = i * TAILLE_LAYERIII + j;
				OUTPUT[i] = OUTPUT[i] + W_O[offset]*LAYERIII[j];
			}
      Z_L[i] = OUTPUT[i];
			OUTPUT[i] = sigmoid(OUTPUT[i]-b_output[i]);
		}

}

/***********************************************
error_output calcul l'erreur sur l'output
à partir de la solution
************************************************/

void error_output(long double *Z_L,long double *ERROR_OUTPUT,
                  long double *SOLUTION,long double *OUTPUT){
  for (int j=0; j<TAILLE_OUTPUT; j = j+1){
    ERROR_OUTPUT[j] = (OUTPUT[j]-SOLUTION[j])*d_sigmoid(Z_L[j]);
  }
}

/********************************************
calcul de l'erreur aux niveaux du
3ieme layer a partir de l'erreur sur
l'output et par une multiplication
de la transpose de sa matrice des poids
**********************************************/
void error_layerIII(long double *ans3, long double *W_OT, long double *ERROR_LAYERIII,
                  	long double *ERROR_OUTPUT, long double *Z_lIII){
  multiplAV(W_OT, ERROR_OUTPUT, ans3, TAILLE_LAYERIII, TAILLE_OUTPUT);
  for (int j=0; j<TAILLE_LAYERIII; j = j+1){
    ERROR_LAYERIII[j] = ans3[j]*d_sigmoid(Z_lIII[j]);
  }
}

/********************************************
calcul de l'erreur aux niveaux du
2n layer a partir de l'erreur sur
le 3ieme layers et par une multiplication
de la transpose de sa matrice des poids
**********************************************/

void error_layerII(long double *ans2, long double *W_LIIIT, long double *ERROR_LAYERII,
									 long double *ERROR_LAYERIII, long double *Z_lII){
	multiplAV(W_LIIIT, ERROR_LAYERIII, ans2, TAILLE_LAYERII, TAILLE_LAYERIII);
	#pragma omp for nowait
	for (int j=0; j<TAILLE_LAYERII; j++){
		ERROR_LAYERII[j] = ans2[j]*d_sigmoid(Z_lII[j]);
	}
}

/********************************************
calcul de l'erreur aux niveaux du
1er layers a partir de l'erreur sur
le 2nd layer et par une multiplication
de la transpose de sa matrice  des poids
**********************************************/
void error_layer(long double *ans, long double *W_LIIT, long double *ERROR_LAYER,
 								 long double *ERROR_LAYERII, long double *Z_l){
	multiplAV(W_LIIT, ERROR_LAYERII, ans, TAILLE_LAYER, TAILLE_LAYERII);
	#pragma omp for nowait
	for (int j=0; j< TAILLE_LAYER; j++){
		ERROR_LAYER[j] = ans[j]*d_sigmoid(Z_l[j]);
	}
}

/***********************************************************************
 backprop() la fonction qui réalise la back-propagation
 et qui corrige les valeurs de poids et de biais a chaque apprentissage
 **********************************************************************/
void backprop(long double *W_L, long double *W_LII, long double *W_LIII,
	 						long double *W_O, long double *b_L, long double *b_LII,
							long double *b_LIII, long double *b_O, long double *eta,
							long double *ERROR_OUTPUT, long double *ERROR_LAYERIII,
							long double *ERROR_LAYERII, long double *ERROR_LAYER,long double *INPUT,
							long double *LAYER, long double *LAYERII, long double *LAYERIII,
							long double *OUTPUT){

  // modification BIAIS et POIDS pour OUTPUT
  for (int j=0; j<TAILLE_OUTPUT; j = j+1){
    b_O[j] = b_O[j] - eta[0]*ERROR_OUTPUT[j];
  }

  int row, columns;
  for (row=0; row<TAILLE_OUTPUT; row++)
  {
    for(columns=0; columns<TAILLE_LAYERIII; columns++)
    {
      int offset = row * TAILLE_LAYERIII + columns;
			//#pragma omp atomic
      W_O[offset] = W_O[offset] - eta[0]*ERROR_OUTPUT[row]*LAYERIII[columns];

    }
  }

	//modification BIAIS et POIDS pour LAYERIII

	for (int j=0; j<TAILLE_LAYERIII; j = j+1){
    b_LIII[j] = b_LIII[j] - eta[0]*ERROR_LAYERIII[j];
  }

  //row = 0; columns = 0;
//	#pragma omp parallel for shared(W_LIII,eta,ERROR_LAYERIII,ERROR_LAYERII)
#pragma omp for nowait
  for ( int row=0; row<TAILLE_LAYERIII; row++)
  {
    for( int columns=0; columns<TAILLE_LAYERII; columns++)
    {
      int offset = row * TAILLE_LAYERII + columns;
			//#pragma omp atomic
      W_LIII[offset] = W_LIII[offset] - eta[0]*ERROR_LAYERIII[row]*LAYERII[columns];

    }
  }


	//modification BIAIS et POIDS pour LAYERII
//	#pragma omp parallel for shared(b_LII, eta, ERROR_LAYERII)
#pragma omp for nowait
	for (int j=0; j<TAILLE_LAYERII; j = j+1){
		//#pragma omp atomic
    b_LII[j] = b_LII[j] - eta[0]*ERROR_LAYERII[j];

  }

  //row = 0; columns = 0;
	//#pragma omp  parallel for shared(W_LII,eta,ERROR_LAYERII,LAYER)
	#pragma omp for nowait
  for (int row=0; row<TAILLE_LAYERII; row++)
{
    for(int columns=0; columns<TAILLE_LAYER; columns++)
    {
      int offset = row * TAILLE_LAYER + columns;
			//#pragma omp atomic
      W_LII[offset] = W_LII[offset] - eta[0]*ERROR_LAYERII[row]*LAYER[columns];

    }
}
  // modification BIAIS et POIDS pour LAYER
//	#pragma omp parallel for shared( b_L,eta,ERROR_LAYER)
	#pragma omp for nowait
  for (int j=0; j<TAILLE_LAYER; j = j+1){
		//#pragma omp atomic
    b_L[j] = b_L[j] - eta[0]*ERROR_LAYER[j];
  }

  int row2, columns2;
	//#pragma omp parallel for shared(W_L,eta,ERROR_LAYER,INPUT) private(row2, columns2)
	#pragma omp for nowait
  for (int row2=0; row2<TAILLE_LAYER; row2++)
  {
    for(int columns2=0; columns2<TAILLE_INPUT; columns2++)
    {
      int offset = row2 * TAILLE_INPUT + columns2;
		//	#pragma omp atomic
      W_L[offset] = W_L[offset] - eta[0]*ERROR_LAYER[row2]*INPUT[columns2];


		}
  }


}

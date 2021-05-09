#include "Struct.h"

void init_b(long double *b, int Taille_b){
  for (int j=0; j<Taille_b; j = j+1){
    b[j] = 1.0;
	}
}

void init_Pooling(long double *POOLING){
	for(int k=0; k<TAILLE_POOL; k++){
		POOLING[k] = 0;
	}
}

void init_Pooling2(long double *POOLING2){
	for (int k=0; k<TAILLE_POOLII; k++){
		POOLING2[k] = 0;
	}
}

void init_Input(long double *INPUT){
  for (int j=0; j<TAILLE_INPUT; j = j+1){
    INPUT[j] = (rand()%100000)/100000.0;
	}
}

void init_Convolution(long double *CONVOLUTION){
	for (int j=0; j<pow(TAILLE_IMAGE-2,2); j++){
		CONVOLUTION[j] = (rand()%100000)/100000.0;//possible car matrice en row ou col major et carrée
	}
}

void init_Convolution2(long double *CONVOLUTION2){
	for (int j=0; j<pow(DIM_POOL-2,2); j++){
		CONVOLUTION2[j] = (rand()%100000)/100000.0;
	}
}

void init_Layer(long double *LAYER, long double *LAYERII, long double *LAYERIII){
  for (int j=0; j<TAILLE_LAYER; j = j+1){
    LAYER[j] = (rand()%100000)/100000.0;
	}
	for (int j=0; j<TAILLE_LAYERII; j++){
		LAYERII[j] = (rand()%100000)/100000.0;
	}
	for (int j=0; j<TAILLE_LAYERIII; j++){
		LAYERIII[j] = (rand()%100000)/100000.0;
	}
}

void init_Output(long double *OUTPUT){
	for (int j=0; j<TAILLE_OUTPUT; j = j+1){
		OUTPUT[j] = (rand()%100000)/100000.0;
	}
}

void init_W(long double *W_L, long double *W_LII, long double *W_LIII,
						long double *W_O, long double *W_C, long double *W_C2){
		for (int i=0; i<TAILLE_LAYER; i = i+1){
			for (int j=0; j<TAILLE_INPUT; j = j+1){
        int offset = i * TAILLE_INPUT + j;
				W_L[offset] = (rand()%100000)/100000.0;
			}
		}
		for (int i=0; i<TAILLE_LAYERII; i++){
			for(int j=0; j<TAILLE_LAYER; j++){
				int offset = i*TAILLE_LAYER + j;
				W_LII[offset] = (rand()%100000)/100000.0;
			}
		}
		for (int i=0; i<TAILLE_LAYERIII; i++){
			for (int j=0; j<TAILLE_LAYERII; j++){
				int offset = i*TAILLE_LAYERII + j;
				W_LIII[offset] = (rand()%100000)/100000.0;
			}
		}
		for (int i=0; i<TAILLE_OUTPUT; i = i+1){
			for (int j=0; j<TAILLE_LAYERIII; j = j+1){
        int offset = i*TAILLE_LAYERIII + j;
				W_O[offset] = (rand()%100000)/100000.0;
			}
		}
		for (int i=0; i<3; i++){
			for (int j=0; j<3; j++){
				int offset = i*3 + j;
				W_C[offset] = (rand()%100000)/100000.0;
			}
		}

		for (int i=0; i<3; i++){
			for (int j=0; j<3; j++){
				int offset = i*3 + j;
				W_C2[offset] = (rand()%100000)/100000.0;
			}
		}
}

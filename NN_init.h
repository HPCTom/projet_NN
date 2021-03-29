#include "Struct.h"

void init_b(long double *b, int Taille_b){
  for (int j=0; j<Taille_b; j = j+1){
    b[j] = 1.0;
	}
}

void init_Input(long double *INPUT){
  for (int j=0; j<TAILLE_INPUT; j = j+1){
    INPUT[j] = (rand()%100000)/100000.0;
	}
}

void init_Layer(long double *LAYER){
  for (int j=0; j<TAILLE_LAYER; j = j+1){
    LAYER[j] = (rand()%100000)/100000.0;
	}
}

void init_Output(long double *OUTPUT){
	for (int j=0; j<TAILLE_OUTPUT; j = j+1){
		OUTPUT[j] = (rand()%100000)/100000.0;
	}
}

void init_Solution(long double *SOLUTION){
  // Initialise la pseudo solution pour l'INPUT aléatoire
	SOLUTION[0] = 1.0;
  SOLUTION[1] = 0.0;
	}

void init_W(long double *W_L, long double *W_O){
		for (int i=0; i<TAILLE_LAYER; i = i+1){
			for (int j=0; j<TAILLE_INPUT; j = j+1){
        int offset = i * TAILLE_INPUT + j;
				W_L[offset] = (rand()%100000)/100000.0;
			}
		}
		for (int i=0; i<TAILLE_OUTPUT; i = i+1){
			for (int j=0; j<TAILLE_LAYER; j = j+1){
        int offset = i * TAILLE_LAYER + j;
				W_O[offset] = (rand()%100000)/100000.0;
			}
		}
	}

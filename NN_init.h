#include "Struct.h"

void init_b(long double *b, int Taille_b){
  for (int j=0; j<Taille_b; j = j+1){
    b[j] = 1.0;
	}
}

void init_Input(long double *INPUT, int Taille_input){
  for (int j=0; j<Taille_input; j = j+1){
    INPUT[j] = (rand()%100000)/100000.0;
	}
}

void init_Layer(long double *LAYER, int Taille_layer){
  for (int j=0; j<Taille_layer; j = j+1){
    LAYER[j] = (rand()%100000)/100000.0;
	}
}

void init_Output(long double *OUTPUT, int Taille_output){
	for (int j=0; j<Taille_output; j = j+1){
		OUTPUT[j] = (rand()%100000)/100000.0;
	}
}

void init_Solution(long double *SOLUTION,int Taille_output){
	SOLUTION[0] = 0.0;
  SOLUTION[1] = 1.0;
	}

void init_W(long double *W_L, long double *W_O, int Taille_input, int Taille_layer, int Taille_output){
		for (int i=0; i<Taille_layer; i = i+1){
			for (int j=0; j<Taille_input; j = j+1){
        int offset = i * Taille_input + j;
				W_L[offset] = (rand()%100000)/100000.0;
			}
		}
		for (int i=0; i<Taille_output; i = i+1){
			for (int j=0; j<Taille_layer; j = j+1){
        int offset = i * Taille_layer + j;
				W_O[offset] = (rand()%100000)/100000.0;
			}
		}
	}

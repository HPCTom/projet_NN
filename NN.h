#include "NN_fct.h"

void front_prop(long double *Z_L, long double *Z_l, long double *INPUT,
                long double *LAYER, long double *OUTPUT, long double *b_layer,
                long double *b_output,long double* W_L,long double* W_O,
                int Taille_input, int Taille_layer, int Taille_output){
		//premiere propagation Input à Layer
		for (int i=0; i<Taille_layer; i++){
			for (int j=0; j<Taille_input; j = j+1){
        int offset = i * Taille_input + j;
        LAYER[i] = LAYER[i] + W_L[offset]*INPUT[j];
			}
      Z_l[i] = LAYER[i];
			LAYER[i] = sigmoid(LAYER[i]+b_layer[i]);
		 }
		 //deuxième propagation Layer à Output
		for (int i=0; i<Taille_output; i++){
			for (int j=0; j<Taille_layer; j = j+1){
        int offset = i * Taille_layer + j;
				OUTPUT[i] = OUTPUT[i] + W_O[offset]*LAYER[j];
			}
      Z_L[i] = OUTPUT[i];
			OUTPUT[i] = sigmoid(OUTPUT[i]+b_output[i]);
		}
  }

void error_output(long double *Z_L,long double *ERROR_OUTPUT,
                  long double *SOLUTION,long double *OUTPUT,
                  int Taille_output){
  for (int j=0; j<Taille_output; j = j+1){
    ERROR_OUTPUT[j] = (OUTPUT[j]-SOLUTION[j])*d_sigmoid(Z_L[j]);
  }
}

void error_layer(long double *ans, long double *W_OT, long double *ERROR_LAYER,
                  long double *ERROR_OUTPUT, long double *Z_l,int Taille_layer){
  multiplAV(W_OT, ERROR_OUTPUT, ans, TAILLE_LAYER, TAILLE_OUTPUT);
  for (int j=0; j<Taille_layer; j = j+1){
    ERROR_LAYER[j] = ans[j]*d_sigmoid(Z_l[j]);
  }
}



void backprop(long double *W_L, long double *W_O, long double *b_L,
              long double *b_O, long double *eta, long double *ERROR_OUTPUT,
              long double *ERROR_LAYER,long double *INPUT,long double *LAYER,
              long double *OUTPUT, int Taille_layer,int Taille_output,
               int Taille_input){

  // modification BIAIS et POIDS pour OUTPUT
  for (int j=0; j<Taille_output; j = j+1){
    b_O[j] = b_O[j] - eta[0]*ERROR_OUTPUT[j];
  }

  int row, columns;
  for (row=0; row<Taille_output; row++)
  {
    for(columns=0; columns<Taille_layer; columns++)
    {
      int offset = row * Taille_layer + columns;
      W_O[offset] = W_O[offset] - eta[0]*ERROR_OUTPUT[row]*LAYER[columns];
    }
  }

  // modification BIAIS et POIDS pour LAYER
  for (int j=0; j<Taille_layer; j = j+1){
    b_L[j] = b_L[j] - eta[0]*ERROR_LAYER[j];
  }

  int row2, columns2;
  for (row2=0; row2<Taille_layer; row2++)
  {
    for(columns2=0; columns2<Taille_input; columns2++)
    {
      int offset = row2 * Taille_input + columns2;
      W_L[offset] = W_L[offset] - eta[0]*ERROR_LAYER[row2]*INPUT[columns2];
    }
  }


}

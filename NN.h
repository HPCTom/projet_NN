#include "NN_fct.h"

void front_prop(long double *Z_L, long double *Z_l, long double *INPUT, long double *LAYER, long double *OUTPUT, long double *b_layer,
                long double *b_output,long double* W_L,long double* W_O,int Taille_input, int Taille_layer, int Taille_output){
		//premiere propagation Input à Layer
		for (int i=0; i<Taille_layer; i++){
      /*
        int row, columns;
        for (row=0; row<Taille_layer; row++)
        {
          for(columns=0; columns<Taille_input; columns++)
          {
            int offset = row * Taille_input + columns;
            printf("%Lf     ", W_L[offset]);
          }
          printf("\n");
        }
      printf("LAYER \t");
      for (int x = 0; x<Taille_layer; x++){
        printf("%Lf ",LAYER[x]);
      }
      printf("\n");
      printf("INPUT \t");
      for (int x = 0; x<Taille_input; x++){
        printf("%Lf ",INPUT[x]);
      }
      printf("\n");
      */
			for (int j=0; j<Taille_input; j = j+1){
        int offset = i * Taille_input + j;
        /*
        printf("W_L[i,j] = %Lf\t",W_L[offset]);
        printf("LAYER[i] = %Lf\t",LAYER[i]);
        printf("INPUT[j] = %Lf \n",INPUT[j]);
        */
        // printf("IN LAYER[i] = %Lf \n",LAYER[i]);
        // printf("IN W_L[offset] = %Lf \n",W_L[offset]);
        // printf("\n");
        LAYER[i] = LAYER[i] + W_L[offset]*INPUT[j];
        //printf("LAYER[i] = %Lf\n",LAYER[i]);
			}
      Z_l[i] = LAYER[i];
      // printf("IN OUTPUT[i] = %Lf \n",OUTPUT[i]);
      // printf("IN W_O[offset] = %Lf \n",W_O[offset]);
      // printf("IN LAYER[j] = %Lf \n",LAYER[j]);
      // printf("\n")
			LAYER[i] = sigmoid(LAYER[i]+b_layer[i]);
		 }

     //printf("\n\n W000\n");
		 //deuxième propagation Layer à Output
		for (int i=0; i<Taille_output; i++){
      /*
      int row, columns;
      for (row=0; row<Taille_output; row++)
      {
        for(columns=0; columns<Taille_layer; columns++)
        {
          int offset = row * Taille_layer + columns;
          printf("%Lf     ", W_O[offset]);
        }
        printf("\n");
      }
    printf("LAYER \t");
    for (int x = 0; x<Taille_layer; x++){
      printf("%Lf ",LAYER[x]);
    }
    printf("\n");
    printf("OUTPUT \t");
    for (int x = 0; x<Taille_output; x++){
      printf("%Lf ",OUTPUT[x]);
    }
    printf("\n");
    */
			for (int j=0; j<Taille_layer; j = j+1){
        int offset = i * Taille_layer + j;
        /*
        printf("W_0[i,j] = %Lf\t",W_O[offset]);
        printf("LAYER[i] = %Lf\t",LAYER[j]);
        printf("OUTPUT[j] = %Lf \n",OUTPUT[i]);
        */
        // printf("IN OUTPUT[i] = %Lf \n",OUTPUT[i]);
        // printf("IN W_O[offset] = %Lf \n",W_O[offset]);
        // printf("IN LAYER[j] = %Lf \n",LAYER[j]);
        // printf("\n");
				OUTPUT[i] = OUTPUT[i] + W_O[offset]*LAYER[j];
        //printf("OUTPUT[i] = %Lf\n",OUTPUT[i]);
			}
      Z_L[i] = OUTPUT[i];
			OUTPUT[i] = sigmoid(OUTPUT[i]+b_output[i]);
		}
  }

void error_output(long double *Z_L,long double *ERROR_OUTPUT, long double *SOLUTION,long double *OUTPUT,
                  int Taille_output,int n){
  for (int j=0; j<Taille_output; j = j+1){
    ERROR_OUTPUT[j] = (OUTPUT[j]-SOLUTION[j])*d_sigmoid(Z_L[j]);
  }
}

void error_layer(long double *ans, long double *W_OT, long double *ERROR_LAYER, long double *ERROR_OUTPUT, long double *Z_l,
                 int Taille_layer){
  multiplAV(W_OT, ERROR_OUTPUT, ans, TAILLE_LAYER, TAILLE_OUTPUT);
  for (int j=0; j<Taille_layer; j = j+1){
    // printf("ans = %Lf\n", ans[j]);
    //printf("d_sig = %Lf\n",d_sigmoid(Z_l[j]));
    ERROR_LAYER[j] = ans[j]*d_sigmoid(Z_l[j]);
    //printf("ERROR_LAYER[j] = %Lf\n",ERROR_LAYER[j]);
  }
}



void backprop(long double *W_L, long double *W_O, long double *b_L, long double *b_O, long double *eta, long double *ERROR_OUTPUT,
              long double *ERROR_LAYER,long double *INPUT,long double *LAYER,long double *OUTPUT, int Taille_layer,
              int Taille_output, int Taille_input){

  //// modification BIAIS et POIDS pour OUTPUT
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

  //// modification BIAIS et POIDS pour LAYER
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

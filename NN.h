#include "NN_fct.h"

void convolution(double *W_C, double *CONVOLUTION, double *IMAGE){
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

void pooling(double *CONVOLUTION, double *POOLING){
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

void convolution2(double *W_C2, double *CONVOLUTION2, double *POOLING){
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

void pooling2(double *CONVOLUTION2, double *POOLING2){
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

void front_prop(double *Z_L,double *Z_lIII,double *Z_lII,
								double *Z_l, double *INPUT,double *LAYER,
								double *LAYERII, double *LAYERIII, double *OUTPUT,
								double *b_L, double *b_LII, double *b_LIII,
								double *b_output,double* W_L, double *W_LII,
								double *W_LIII, double* W_O){
		//premiere propagation Input à Layer
		for (int i=0; i<TAILLE_LAYER; i++){
			for (int j=0; j<TAILLE_INPUT; j = j+1){
        int offset = i * TAILLE_INPUT + j;
        LAYER[i] = LAYER[i] + W_L[offset]*INPUT[j];
			}
      Z_l[i] = LAYER[i];
			LAYER[i] = sigmoid(LAYER[i]-b_L[i]);
		 }

		 for (int i=0; i<TAILLE_LAYERII; i++){
 			for (int j=0; j<TAILLE_LAYER; j = j+1){
         int offset = i * TAILLE_LAYER + j;
         LAYERII[i] = LAYERII[i] + W_LII[offset]*LAYER[j];
 			}
       Z_lII[i] = LAYERII[i];
 			LAYERII[i] = sigmoid(LAYERII[i]-b_LII[i]);
 		 }

		 for (int i=0; i<TAILLE_LAYERIII; i++){
 			for (int j=0; j<TAILLE_LAYERII; j = j+1){
         int offset = i * TAILLE_LAYERII + j;
         LAYERIII[i] = LAYERIII[i] + W_LIII[offset]*LAYERII[j];
 			}
       Z_lIII[i] = LAYERIII[i];
 			LAYERIII[i] = sigmoid(LAYERIII[i]-b_LIII[i]);
 		 }
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

void error_output(double *Z_L,double *ERROR_OUTPUT,
                  double *SOLUTION,double *OUTPUT){
  for (int j=0; j<TAILLE_OUTPUT; j = j+1){
    ERROR_OUTPUT[j] = (OUTPUT[j]-SOLUTION[j])*d_sigmoid(Z_L[j]);
  }
}

void error_layerIII(double *ans3, double *W_OT, double *ERROR_LAYERIII,
                  	double *ERROR_OUTPUT, double *Z_lIII){
  multiplAV(W_OT, ERROR_OUTPUT, ans3, TAILLE_LAYERIII, TAILLE_OUTPUT);
  for (int j=0; j<TAILLE_LAYERIII; j = j+1){
    ERROR_LAYERIII[j] = ans3[j]*d_sigmoid(Z_lIII[j]);
  }
}

void error_layerII(double *ans2, double *W_LIIIT, double *ERROR_LAYERII,
									 double *ERROR_LAYERIII, double *Z_lII){
	multiplAV(W_LIIIT, ERROR_LAYERIII, ans2, TAILLE_LAYERII, TAILLE_LAYERIII);
	for (int j=0; j<TAILLE_LAYERII; j++){
		ERROR_LAYERII[j] = ans2[j]*d_sigmoid(Z_lII[j]);
	}
}

void error_layer(double *ans, double *W_LIIT, double *ERROR_LAYER,
 								 double *ERROR_LAYERII, double *Z_l){
	multiplAV(W_LIIT, ERROR_LAYERII, ans, TAILLE_LAYER, TAILLE_LAYERII);
	for (int j=0; j< TAILLE_LAYER; j++){
		ERROR_LAYER[j] = ans[j]*d_sigmoid(Z_l[j]);
	}
}

void backprop(double *W_L, double *W_LII, double *W_LIII,
	 						double *W_O, double *b_L, double *b_LII,
							double *b_LIII, double *b_O, double *eta,
							double *ERROR_OUTPUT, double *ERROR_LAYERIII,
							double *ERROR_LAYERII, double *ERROR_LAYER,double *INPUT,
							double *LAYER, double *LAYERII, double *LAYERIII,
							double *OUTPUT){

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
      W_O[offset] = W_O[offset] - eta[0]*ERROR_OUTPUT[row]*LAYERIII[columns];
    }
  }

	//modification BIAIS et POIDS pour LAYERIII
	for (int j=0; j<TAILLE_LAYERIII; j = j+1){
    b_LIII[j] = b_LIII[j] - eta[0]*ERROR_LAYERIII[j];
  }

  row = 0; columns = 0;
  for (row=0; row<TAILLE_LAYERIII; row++)
  {
    for(columns=0; columns<TAILLE_LAYERII; columns++)
    {
      int offset = row * TAILLE_LAYERII + columns;
      W_LIII[offset] = W_LIII[offset] - eta[0]*ERROR_LAYERIII[row]*LAYERII[columns];
    }
  }

	//modification BIAIS et POIDS pour LAYERII
	for (int j=0; j<TAILLE_LAYERII; j = j+1){
    b_LII[j] = b_LII[j] - eta[0]*ERROR_LAYERII[j];
  }

  row = 0; columns = 0;
  for (row=0; row<TAILLE_LAYERII; row++)
  {
    for(columns=0; columns<TAILLE_LAYER; columns++)
    {
      int offset = row * TAILLE_LAYER + columns;
      W_LII[offset] = W_LII[offset] - eta[0]*ERROR_LAYERII[row]*LAYER[columns];
    }
  }
  // modification BIAIS et POIDS pour LAYER
  for (int j=0; j<TAILLE_LAYER; j = j+1){
    b_L[j] = b_L[j] - eta[0]*ERROR_LAYER[j];
  }

  int row2, columns2;
  for (row2=0; row2<TAILLE_LAYER; row2++)
  {
    for(columns2=0; columns2<TAILLE_INPUT; columns2++)
    {
      int offset = row2 * TAILLE_INPUT + columns2;
      W_L[offset] = W_L[offset] - eta[0]*ERROR_LAYER[row2]*INPUT[columns2];
    }
  }
}

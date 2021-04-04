#include "NN.h"
#include "lirepng.h"




int main(int argc, char *argv[])
{
srand(time(NULL));
long double* IMAGE = malloc(TAILLE_IMAGE*sizeof(long double));
long double* CONVOLUTION = malloc(pow(TAILLE_IMAGE-2,2)*sizeof(long double)); //Convolution matrix
long double* POOLING = malloc(TAILLE_POOL*sizeof(long double));
long double* CONVOLUTION2 = malloc(pow(DIM_POOL-2,2)*sizeof(long double));
long double* POOLING2 = malloc(TAILLE_POOLII*sizeof(long double));
long double* INPUT =  malloc(TAILLE_INPUT*sizeof(long double)); //Input layer
long double* LAYER = malloc(TAILLE_LAYER*sizeof(long double)); // Middle Layer
long double* OUTPUT = malloc(TAILLE_OUTPUT*sizeof(long double)); //
long double* SOLUTION = malloc(TAILLE_OUTPUT*sizeof(long double));
long double* COUT = malloc(1*sizeof(long double));
long double* ERROR_OUTPUT = malloc(TAILLE_OUTPUT*sizeof(long double));
long double* ERROR_LAYER = malloc(TAILLE_LAYER*sizeof(long double));

long double *W_C = malloc(3*3*sizeof(long double)); //poids de convolution
long double *W_C2 = malloc(3*3*sizeof(long double));
long double *W_L = malloc(TAILLE_LAYER * TAILLE_INPUT * sizeof(long double));
long double *W_O = malloc(TAILLE_OUTPUT * TAILLE_LAYER * sizeof(long double));
long double *W_OT = malloc(TAILLE_LAYER * TAILLE_OUTPUT * sizeof(long double));

long double *b_L = malloc(TAILLE_LAYER * sizeof(long double));
long double *b_O = malloc(TAILLE_OUTPUT * sizeof(long double));

long double *Z_L = malloc(TAILLE_OUTPUT * sizeof(long double)); //Dans sigmoid output
long double *Z_l = malloc(TAILLE_LAYER * sizeof(long double)); //Dans sigmoid layer

long double *ans = malloc(TAILLE_LAYER * sizeof(long double)); //Dans error_layer
long double *eta = malloc(1*sizeof(long double)); //Taux d'apprentissage à modifier dans NN_fct.h (fct_eta)

init_Convolution(CONVOLUTION);
init_Pooling(POOLING);
init_Convolution2(CONVOLUTION2);
init_Pooling2(POOLING2);
init_b(b_L,TAILLE_LAYER);
init_b(b_O,TAILLE_OUTPUT);
init_Layer(LAYER);
init_Output(OUTPUT);
init_W(W_L,W_O,W_C,W_C2);
fct_eta(eta);
COUT[0] = 1.0;


int run = 0;
int pas = 4;
int nb_0 = 0;
int nb_1 = 0;
int bon = 0;
int faux = 0;
int null = 0;

presentation(pas);

//sleep(30);

while(run < 100000){

PNG_to_INPUT(IMAGE,SOLUTION,&nb_0,&nb_1);

mem_0(LAYER,OUTPUT);

convolution(W_C, CONVOLUTION, IMAGE);
pooling(CONVOLUTION, POOLING);
convolution2(W_C2,CONVOLUTION2, POOLING);
pooling2(CONVOLUTION2, POOLING2);

INPUT = POOLING2;

front_prop(Z_L,Z_l,INPUT,LAYER,OUTPUT,b_L,b_O,W_L,W_O);

fct_cout(SOLUTION,OUTPUT,COUT);

error_output(Z_L,ERROR_OUTPUT,SOLUTION,OUTPUT);

transpose(W_OT,W_O);
error_layer(ans,W_OT,ERROR_LAYER,ERROR_OUTPUT,Z_l);

backprop(W_L, W_O, b_L, b_O, eta, ERROR_OUTPUT, ERROR_LAYER, INPUT, LAYER, OUTPUT);

resultat(OUTPUT,SOLUTION,COUT,run,pas,nb_0,nb_1,&bon,&faux,&null);

run+= 1;

}


free_all(INPUT,LAYER,OUTPUT,SOLUTION,COUT,ERROR_OUTPUT,ERROR_LAYER,W_L,W_O,
					W_OT,b_L,b_O,Z_L,Z_l,ans, eta, IMAGE, CONVOLUTION, W_C, POOLING,
					CONVOLUTION2, W_C2, POOLING2);
return 0;
}

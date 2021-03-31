#include "NN.h"
#include "lirepng.h"




int main(int argc, char *argv[])
{
srand(time(NULL));
long double* INPUT =  malloc(TAILLE_INPUT*sizeof(long double));
long double* LAYER = malloc(TAILLE_LAYER*sizeof(long double));
long double* OUTPUT = malloc(TAILLE_OUTPUT*sizeof(long double));
long double* SOLUTION = malloc(TAILLE_OUTPUT*sizeof(long double));
long double* COUT = calloc(1,sizeof(long double));
long double* ERROR_OUTPUT = malloc(TAILLE_OUTPUT*sizeof(long double));
long double* ERROR_LAYER = malloc(TAILLE_LAYER*sizeof(long double));

long double *W_L = malloc(TAILLE_LAYER * TAILLE_INPUT * sizeof(long double));
long double *W_LT = malloc(TAILLE_LAYER * TAILLE_INPUT * sizeof(long double));
long double *W_O = malloc(TAILLE_OUTPUT * TAILLE_LAYER * sizeof(long double));
long double *W_OT = malloc(TAILLE_LAYER * TAILLE_OUTPUT * sizeof(long double));

long double *b_L = malloc(TAILLE_LAYER * sizeof(long double));
long double *b_O = malloc(TAILLE_OUTPUT * sizeof(long double));

long double *Z_L = malloc(TAILLE_OUTPUT * sizeof(long double)); //Dans sigmoid output
long double *Z_l = malloc(TAILLE_LAYER * sizeof(long double)); //Dans sigmoid layer

long double *ans = calloc(TAILLE_LAYER , sizeof(long double));
long double *eta = calloc(1,sizeof(long double));

init_b(b_L,TAILLE_LAYER);
init_b(b_O,TAILLE_OUTPUT);
//init_Input(INPUT);
init_Layer(LAYER);
init_Output(OUTPUT);
//init_Solution(SOLUTION);
init_W(W_L,W_O);
fct_eta(eta);
COUT[0] = 1.0;

presentation();


while(1){
PNG_to_INPUT(INPUT,SOLUTION);
mem_0(LAYER,OUTPUT,ans);
front_prop(Z_L,Z_l,INPUT,LAYER,OUTPUT,b_L,b_O,W_L,W_O);
fct_cout(SOLUTION,OUTPUT,COUT);

error_output(Z_L,ERROR_OUTPUT,SOLUTION,OUTPUT);

transpose(W_OT,W_O);
error_layer(ans,W_OT,ERROR_LAYER,ERROR_OUTPUT,Z_l);

backprop(W_L, W_O, b_L, b_O, eta, ERROR_OUTPUT, ERROR_LAYER, INPUT, LAYER, OUTPUT);

resultat(OUTPUT,SOLUTION,COUT);
}

//resultat(OUTPUT,SOLUTION,COUT);

free_all(INPUT,LAYER,OUTPUT,SOLUTION,COUT,ERROR_OUTPUT,ERROR_LAYER,W_L,W_LT,W_O,W_OT,b_L,b_O,Z_L,Z_l,ans,eta);
return 0;
}

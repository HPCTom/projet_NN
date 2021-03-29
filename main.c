#include "NN.h"


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
init_Input(INPUT,TAILLE_INPUT);
init_Layer(LAYER,TAILLE_LAYER);
init_Output(OUTPUT,TAILLE_OUTPUT);
init_Solution(SOLUTION,TAILLE_OUTPUT);
init_W(W_L,W_O,TAILLE_INPUT,TAILLE_LAYER,TAILLE_OUTPUT);
fct_eta(eta);
COUT[0] = 1.0;

presentation(NB_LAYER,TAILLE_INPUT,TAILLE_LAYER,TAILLE_OUTPUT);

double lim = 0.001;

while(COUT[0]>lim){

mem_0(LAYER,OUTPUT,ans,TAILLE_LAYER,TAILLE_OUTPUT);
front_prop(Z_L,Z_l,INPUT,LAYER,OUTPUT,b_L,b_O,W_L,W_O,TAILLE_INPUT,TAILLE_LAYER,TAILLE_OUTPUT);
fct_cout(SOLUTION,OUTPUT,COUT,SOLUTION,OUTPUT,TAILLE_OUTPUT);

error_output(Z_L,ERROR_OUTPUT,SOLUTION,OUTPUT,TAILLE_OUTPUT);

transpose(W_OT,W_O,TAILLE_OUTPUT,TAILLE_LAYER);
error_layer(ans,W_OT,ERROR_LAYER,ERROR_OUTPUT,Z_l,TAILLE_LAYER);

backprop(W_L, W_O, b_L, b_O, eta, ERROR_OUTPUT, ERROR_LAYER, INPUT, LAYER, OUTPUT,TAILLE_LAYER,
         TAILLE_OUTPUT,TAILLE_INPUT);

}

resultat(OUTPUT,SOLUTION,COUT);

free(INPUT);
free(LAYER);
free(OUTPUT);
free(W_L);
free(W_O);
free(b_L);
free(b_O);

return 0;
}

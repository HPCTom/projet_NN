// #include "NN.h"
// #include "lirepng.h"
// #include <mpi.h>
// #include "mesure.h"
//
//
//
//
// int main(int argc, char *argv[])
// {
// srand(time(NULL));
// long double* IMAGE = malloc(pow(TAILLE_IMAGE,2)*sizeof(long double));
// long double* CONVOLUTION = malloc(pow(TAILLE_IMAGE-2,2)*sizeof(long double)); //Convolution matrix
// long double* POOLING = malloc(TAILLE_POOL*sizeof(long double));
// long double* CONVOLUTION2 = malloc(pow(DIM_POOL-2,2)*sizeof(long double));
// long double* POOLING2 = malloc(TAILLE_POOLII*sizeof(long double));
// long double* INPUT =  malloc(TAILLE_INPUT*sizeof(long double)); //Input Layer
// long double* LAYER = malloc(TAILLE_LAYER*sizeof(long double)); // First Layer
// long double* LAYERII = malloc(TAILLE_LAYERII*sizeof(long double)); //Second Layer
// long double* LAYERIII = malloc(TAILLE_LAYERIII*sizeof(long double)); //Third Layer
// long double* OUTPUT = malloc(TAILLE_OUTPUT*sizeof(long double)); //
// long double* SOLUTION = malloc(TAILLE_OUTPUT*sizeof(long double));
// long double* COUT = malloc(1*sizeof(long double));
// long double* ERROR_OUTPUT = malloc(TAILLE_OUTPUT*sizeof(long double));
// long double* ERROR_LAYERIII = malloc(TAILLE_LAYERIII * sizeof(long double));
// long double* ERROR_LAYERII = malloc(TAILLE_LAYERII * sizeof(long double));
// long double* ERROR_LAYER = malloc(TAILLE_LAYER*sizeof(long double));
//
// long double *W_C = malloc(3*3*sizeof(long double)); //poids de convolution
// long double *W_C2 = malloc(3*3*sizeof(long double)); // poids convolution2
// long double *W_L = malloc(TAILLE_LAYER * TAILLE_INPUT * sizeof(long double));
// long double *W_LII = malloc(TAILLE_LAYERII * TAILLE_LAYER * sizeof(long double));
// long double *W_LIII = malloc(TAILLE_LAYERIII * TAILLE_LAYERII * sizeof(long double));
// long double *W_O = malloc(TAILLE_OUTPUT * TAILLE_LAYERIII * sizeof(long double));
// long double *W_OT = malloc(TAILLE_LAYERIII * TAILLE_OUTPUT * sizeof(long double));
// long double *W_LIIIT = malloc(TAILLE_LAYERII * TAILLE_LAYERIII * sizeof(long double));
// long double *W_LIIT = malloc(TAILLE_LAYER * TAILLE_LAYERII * sizeof(long double));
// //long double *W_LT = malloc(TAILLE_LAYER * TAILLE_LAYERII * sizeof(long double));
//
// long double *b_L = malloc(TAILLE_LAYER * sizeof(long double));
// long double *b_LII = malloc(TAILLE_LAYERII * sizeof(long double));
// long double *b_LIII = malloc(TAILLE_LAYERIII * sizeof(long double));
// long double *b_O = malloc(TAILLE_OUTPUT * sizeof(long double));
//
// long double *Z_L = malloc(TAILLE_OUTPUT * sizeof(long double)); //Dans sigmoid output
// long double *Z_lIII = malloc(TAILLE_LAYERIII * sizeof(long double));//Dans sigmoid layer III
// long double *Z_lII = malloc(TAILLE_LAYERII * sizeof(long double));//Dans sigmoid layer II
// long double *Z_l = malloc(TAILLE_LAYER * sizeof(long double)); //Dans sigmoid layer
//
// long double *ans3 = malloc(TAILLE_LAYERIII * sizeof(long double)); //Dans ERROR_LAYERIII
// long double *ans2 = malloc(TAILLE_LAYERII * sizeof(long double)); //Dans ERROR_LAYERII
// long double *ans = malloc(TAILLE_LAYER * sizeof(long double));
// long double *eta = malloc(1*sizeof(long double)); //Taux d'apprentissage à modifier dans NN_fct.h (fct_eta)
//
// init_Convolution(CONVOLUTION);
// init_Pooling(POOLING);
// init_Convolution2(CONVOLUTION2);
// init_Pooling2(POOLING2);
// init_b(b_L,TAILLE_LAYER);
// init_b(b_LII,TAILLE_LAYERII);
// init_b(b_LIII,TAILLE_LAYERIII);
// init_b(b_O,TAILLE_OUTPUT);
// init_Layer(LAYER, LAYERII, LAYERIII);
// init_Output(OUTPUT);
// init_W(W_L, W_LII, W_LIII, W_O, W_C, W_C2);
// eta[0] = 3.5;
// COUT[0] = 1.0;
//
//
// int run = 1;
// int pas = 50;
// int nb_0 = 0;
// int nb_1 = 0;
// float bon = 0;
// float faux = 0;
// int fauxneg = 0;
// int fauxpos = 0;
// int bonneg = 0;
// int bonpos = 0;
// float null = 0;
//
// presentation(pas);
//
// int nb_run = 0;
// int N = 250;
// int rank, comm_size;
// //sleep(30);
// // MPI_Init( &argc, &argv );
// while(nb_run < N){
// 	// MPI_Comm_rank( MPI_COMM_WORLD, &rank);
// 	// MPI_Comm_size( MPI_COMM_WORLD, &comm_size);
//
// 	// double temps_mpi[N];
// 	// clock_t temps_clock[N];
// 	// double temps_mpi_mesure_mesure[N];
// 	// clock_t temps_clock_mesure_mesure[N];
// 	// double t1 =  MPI_Wtime();
// 	// clock_t a = rdtsc();
//
// 	// debut_mesure_opti(t1,a,rank);
//
// 	fct_eta(eta,run);
// 	PNG_to_INPUT(IMAGE,SOLUTION,&nb_0,&nb_1);
//
// 	mem_0(LAYER, LAYERII, LAYERIII, OUTPUT);
// 	/*
// 	convolution(W_C, CONVOLUTION, IMAGE);
// 	pooling(CONVOLUTION, POOLING);
// 	convolution2(W_C2,CONVOLUTION2, POOLING);
// 	pooling2(CONVOLUTION2, POOLING2);
// 	*/
// 	INPUT = IMAGE;
//
// 	front_prop(Z_L, Z_lIII, Z_lII, Z_l,INPUT,LAYER,LAYERII,LAYERIII,OUTPUT,b_L,b_LII, b_LIII,b_O,
// 						W_L,W_LII, W_LIII, W_O);
//
// 	fct_cout(SOLUTION,OUTPUT,COUT, run);
//
// 	error_output(Z_L,ERROR_OUTPUT,SOLUTION,OUTPUT);
// 	transpose(W_OT,W_O, TAILLE_OUTPUT, TAILLE_LAYERIII);
// 	error_layerIII(ans3,W_OT,ERROR_LAYERIII,ERROR_OUTPUT,Z_lIII);
// 	transpose(W_LIIIT,W_LIII, TAILLE_LAYERIII, TAILLE_LAYERII);
// 	error_layerII(ans2, W_LIIIT, ERROR_LAYERII, ERROR_LAYERIII, Z_lII);
// 	transpose(W_LIIT, W_LII, TAILLE_LAYERII, TAILLE_LAYER);
// 	error_layer(ans,W_LIIT, ERROR_LAYER, ERROR_LAYERII, Z_l);
// 	backprop(W_L, W_LII, W_LIII,W_O, b_L, b_LII, b_LIII, b_O, eta, ERROR_OUTPUT,
// 				 ERROR_LAYERIII, ERROR_LAYERII, ERROR_LAYER, INPUT, LAYER, LAYERII,
// 				 LAYERIII, OUTPUT);
//
// 	//resultat(OUTPUT,SOLUTION,COUT,run,pas,nb_0,nb_1,&fauxpos,&fauxneg,&bonneg,&bonpos,&bon,&faux,&null);
// 	resultat2(OUTPUT,SOLUTION,COUT,run,pas,nb_0,nb_1,&fauxpos,&fauxneg,&bonneg,&bonpos,&bon,&faux,&null);
//
// 	// double t2 =  MPI_Wtime();
//   // clock_t b = rdtsc();
//  	// fin_mesure_opti(t1,a,t2,b,rank,temps_mpi,temps_clock,nb_run,N,argv[1]);
//
// 	run+= 1;
// 	nb_run++;
// }
//
// // MPI_Finalize();
//
// free_all(INPUT,LAYER, LAYERII, LAYERIII, OUTPUT,SOLUTION,COUT,ERROR_OUTPUT,
// 				 ERROR_LAYERIII, ERROR_LAYERII, ERROR_LAYER, W_L, W_LII, W_LIII, W_O,
// 				 W_OT,W_LIIIT, W_LIIT, b_L, b_LII, b_LIII, b_O,Z_L, Z_lIII, Z_lII, Z_l,
// 				 ans3, ans2,ans, eta, IMAGE, CONVOLUTION, W_C, POOLING, CONVOLUTION2, W_C2, POOLING2);
//
//
// return 0;
// }

#include "NN.h"
#include "lirepng.h"




int main(int argc, char *argv[])
{
srand(time(NULL));
long double* IMAGE = malloc(pow(TAILLE_IMAGE,2)*sizeof(long double));
long double* CONVOLUTION = malloc(pow(TAILLE_IMAGE-2,2)*sizeof(long double)); //Convolution matrix
long double* POOLING = malloc(TAILLE_POOL*sizeof(long double));
long double* CONVOLUTION2 = malloc(pow(DIM_POOL-2,2)*sizeof(long double));
long double* POOLING2 = malloc(TAILLE_POOLII*sizeof(long double));
long double* INPUT =  malloc(TAILLE_INPUT*sizeof(long double)); //Input Layer
long double* LAYER = malloc(TAILLE_LAYER*sizeof(long double)); // First Layer
long double* LAYERII = malloc(TAILLE_LAYERII*sizeof(long double)); //Second Layer
long double* LAYERIII = malloc(TAILLE_LAYERIII*sizeof(long double)); //Third Layer
long double* OUTPUT = malloc(TAILLE_OUTPUT*sizeof(long double)); //
long double* SOLUTION = malloc(TAILLE_OUTPUT*sizeof(long double));
long double* COUT = malloc(1*sizeof(long double));
long double* ERROR_OUTPUT = malloc(TAILLE_OUTPUT*sizeof(long double));
long double* ERROR_LAYERIII = malloc(TAILLE_LAYERIII * sizeof(long double));
long double* ERROR_LAYERII = malloc(TAILLE_LAYERII * sizeof(long double));
long double* ERROR_LAYER = malloc(TAILLE_LAYER*sizeof(long double));

long double *W_C = malloc(3*3*sizeof(long double)); //poids de convolution
long double *W_C2 = malloc(3*3*sizeof(long double)); // poids convolution2
long double *W_L = malloc(TAILLE_LAYER * TAILLE_INPUT * sizeof(long double));
long double *W_LII = malloc(TAILLE_LAYERII * TAILLE_LAYER * sizeof(long double));
long double *W_LIII = malloc(TAILLE_LAYERIII * TAILLE_LAYERII * sizeof(long double));
long double *W_O = malloc(TAILLE_OUTPUT * TAILLE_LAYERIII * sizeof(long double));
long double *W_OT = malloc(TAILLE_LAYERIII * TAILLE_OUTPUT * sizeof(long double));
long double *W_LIIIT = malloc(TAILLE_LAYERII * TAILLE_LAYERIII * sizeof(long double));
long double *W_LIIT = malloc(TAILLE_LAYER * TAILLE_LAYERII * sizeof(long double));
//long double *W_LT = malloc(TAILLE_LAYER * TAILLE_LAYERII * sizeof(long double));

long double *b_L = malloc(TAILLE_LAYER * sizeof(long double));
long double *b_LII = malloc(TAILLE_LAYERII * sizeof(long double));
long double *b_LIII = malloc(TAILLE_LAYERIII * sizeof(long double));
long double *b_O = malloc(TAILLE_OUTPUT * sizeof(long double));

long double *Z_L = malloc(TAILLE_OUTPUT * sizeof(long double)); //Dans sigmoid output
long double *Z_lIII = malloc(TAILLE_LAYERIII * sizeof(long double));//Dans sigmoid layer III
long double *Z_lII = malloc(TAILLE_LAYERII * sizeof(long double));//Dans sigmoid layer II
long double *Z_l = malloc(TAILLE_LAYER * sizeof(long double)); //Dans sigmoid layer

long double *ans3 = malloc(TAILLE_LAYERIII * sizeof(long double)); //Dans ERROR_LAYERIII
long double *ans2 = malloc(TAILLE_LAYERII * sizeof(long double)); //Dans ERROR_LAYERII
long double *ans = malloc(TAILLE_LAYER * sizeof(long double));
long double *eta = malloc(1*sizeof(long double)); //Taux d'apprentissage à modifier dans NN_fct.h (fct_eta)

init_Convolution(CONVOLUTION);
init_Pooling(POOLING);
init_Convolution2(CONVOLUTION2);
init_Pooling2(POOLING2);
init_b(b_L,TAILLE_LAYER);
init_b(b_LII,TAILLE_LAYERII);
init_b(b_LIII,TAILLE_LAYERIII);
init_b(b_O,TAILLE_OUTPUT);
init_Layer(LAYER, LAYERII, LAYERIII);
init_Output(OUTPUT);
init_W(W_L, W_LII, W_LIII, W_O, W_C, W_C2);
eta[0] = 3.5;
COUT[0] = 1.0;


int run = 1;
int pas = 50;
int nb_0 = 0;
int nb_1 = 0;
float bon = 0;
float faux = 0;
int fauxneg = 0;
int fauxpos = 0;
int bonneg = 0;
int bonpos = 0;
float null = 0;

presentation(pas);

//sleep(30);
neuralNet_t reseaux;
int tab_size[]={TAILLE_LAYER,TAILLE_LAYERII,TAILLE_LAYERIII};
allocation_neuralNet(&reseaux, 3 , TAILLE_IMAGE*TAILLE_IMAGE, TAILLE_OUTPUT,tab_size);
init_neuralNet(&reseaux);
long double *eta = malloc(1*sizeof(long double)); //Taux d'apprentissage à modifier dans NN_fct.h (fct_eta)
long double* cout = malloc(1*sizeof(long double));
long double* solution = malloc(TAILLE_OUTPUT*sizeof(long double));

while(run < 51){

fct_eta(eta,run);
PNG_to_INPUT(reseaux.input,solution,&nb_0,&nb_1);

front_prop(&reseaux);
fct_cout(solution,reseaux.output,cout, run);
error_output(solution, &reseaux);
t1 = reseaux.dim_out;
t2 = reseaux.dim_hidd[2];
W_OT = (long double*)malloc(t1*t2*sizeof(long double));
rslt = (long double*)malloc(t1*sizeof(long double));
transpose(W_OT, reseaux.w_out,t1,t2);
error_end_layer( rslt, W_OT, &reseaux);
 free(W_OT);
 free(rslt);

for (k = reseaux.nbr_hidd-2 ;k>-1; k--)
{
	t1 = reseaux.dim_hidd[k];
	t2 = reseaux.dim_hidd[k+1];
	W_LT = (long double*)malloc(t1*t2*sizeof(long double));
	rslt = (long double*)malloc(t1*sizeof(long double));
	transpose(W_LT, reseaux.layer[k].weight,t1,t2);
	 error_layer_cons( rslt, W_LT,  &reseaux.layer[k], &reseaux.layer[k+1]);
	 free(W_LT);
	 free(rslt);
}
resultat2(reseaux.output,solution,cout,run,pas,nb_0,nb_1,&fauxpos,&fauxneg,&bonneg,&bonpos,&bon,&faux,&null);
//mem_0(LAYER, LAYERII, LAYERIII, OUTPUT);
/*
convolution(W_C, CONVOLUTION, IMAGE);
pooling(CONVOLUTION, POOLING);
convolution2(W_C2,CONVOLUTION2, POOLING);
pooling2(CONVOLUTION2, POOLING2);
*/
/*INPUT = IMAGE;

front_prop(Z_L, Z_lIII, Z_lII, Z_l,INPUT,LAYER,LAYERII,LAYERIII,OUTPUT,b_L,b_LII, b_LIII,b_O,
						W_L,W_LII, W_LIII, W_O);

fct_cout(SOLUTION,OUTPUT,COUT, run);

error_output(Z_L,ERROR_OUTPUT,SOLUTION,OUTPUT);
transpose(W_OT,W_O, TAILLE_OUTPUT, TAILLE_LAYERIII);
error_layerIII(ans3,W_OT,ERROR_LAYERIII,ERROR_OUTPUT,Z_lIII);
transpose(W_LIIIT,W_LIII, TAILLE_LAYERIII, TAILLE_LAYERII);
error_layerII(ans2, W_LIIIT, ERROR_LAYERII, ERROR_LAYERIII, Z_lII);
transpose(W_LIIT, W_LII, TAILLE_LAYERII, TAILLE_LAYER);
error_layer(ans,W_LIIT, ERROR_LAYER, ERROR_LAYERII, Z_l);
backprop(W_L, W_LII, W_LIII,W_O, b_L, b_LII, b_LIII, b_O, eta, ERROR_OUTPUT,
				 ERROR_LAYERIII, ERROR_LAYERII, ERROR_LAYER, INPUT, LAYER, LAYERII,
				 LAYERIII, OUTPUT);
*/

//resultat(OUTPUT,SOLUTION,COUT,run,pas,nb_0,nb_1,&fauxpos,&fauxneg,&bonneg,&bonpos,&bon,&faux,&null);
//resultat2(OUTPUT,SOLUTION,COUT,run,pas,nb_0,nb_1,&fauxpos,&fauxneg,&bonneg,&bonpos,&bon,&faux,&null);
run+= 1;

}
free_neuralNetwork(&reseaux);
// free_all(INPUT,LAYER, LAYERII, LAYERIII, OUTPUT,SOLUTION,COUT,ERROR_OUTPUT,
// 				 ERROR_LAYERIII, ERROR_LAYERII, ERROR_LAYER, W_L, W_LII, W_LIII, W_O,
// 				 W_OT,W_LIIIT, W_LIIT, b_L, b_LII, b_LIII, b_O,Z_L, Z_lIII, Z_lII, Z_l,
// 				 ans3, ans2,ans, eta, IMAGE, CONVOLUTION, W_C, POOLING, CONVOLUTION2, W_C2, POOLING2);

return 0;
}

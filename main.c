#include "NN.h"
#include "lirepng.h"
#include "mesure.h"



int main(int argc, char *argv[])
{
srand(time(NULL));
int size,rank;
MPI_Init(&argc,&argv);
//MPI_Comm_rank(MPI_COMM_WORLD,&rank);
//MPI_Comm_size(MPI_COMM_WORLD,&size);

double debut = MPI_Wtime();
double** IMAGE = malloc(100*sizeof(*double));
for(int i = 0 ; i<100; i++){
  IMAGE[i]=malloc(pow(TAILLE_IMAGE,2)*sizeof(double));
}
//double* IMAGE = malloc(pow(TAILLE_IMAGE,2)*sizeof(double));
double* CONVOLUTION = malloc(pow(TAILLE_IMAGE-2,2)*sizeof(double)); //Convolution matrix
double* POOLING = malloc(TAILLE_POOL*sizeof(double));
double* CONVOLUTION2 = malloc(pow(DIM_POOL-2,2)*sizeof(double));
double* POOLING2 = malloc(TAILLE_POOLII*sizeof(double));
double* INPUT =  malloc(TAILLE_INPUT*sizeof(double)); //Input Layer
double* LAYER = malloc(TAILLE_LAYER*sizeof(double)); // First Layer
double* LAYERII = malloc(TAILLE_LAYERII*sizeof(double)); //Second Layer
double* LAYERIII = malloc(TAILLE_LAYERIII*sizeof(double)); //Third Layer
double* OUTPUT = malloc(TAILLE_OUTPUT*sizeof(double)); //
double* SOLUTION = malloc(TAILLE_OUTPUT*sizeof(double));
double* COUT = malloc(1*sizeof(double));
double* ERROR_OUTPUT = malloc(TAILLE_OUTPUT*sizeof(double));
double* ERROR_LAYERIII = malloc(TAILLE_LAYERIII * sizeof(double));
double* ERROR_LAYERII = malloc(TAILLE_LAYERII * sizeof(double));
double* ERROR_LAYER = malloc(TAILLE_LAYER*sizeof(double));

double *W_C = malloc(3*3*sizeof(double)); //poids de convolution
double *W_C2 = malloc(3*3*sizeof(double)); // poids convolution2
double *W_L = malloc(TAILLE_LAYER * TAILLE_INPUT * sizeof(double));
double *W_LII = malloc(TAILLE_LAYERII * TAILLE_LAYER * sizeof(double));
double *W_LIII = malloc(TAILLE_LAYERIII * TAILLE_LAYERII * sizeof(double));
double *W_O = malloc(TAILLE_OUTPUT * TAILLE_LAYERIII * sizeof(double));
double *W_OT = malloc(TAILLE_LAYERIII * TAILLE_OUTPUT * sizeof(double));
double *W_LIIIT = malloc(TAILLE_LAYERII * TAILLE_LAYERIII * sizeof(double));
double *W_LIIT = malloc(TAILLE_LAYER * TAILLE_LAYERII * sizeof(double));
double *W_LT = malloc(TAILLE_LAYER * TAILLE_LAYERII * sizeof(double));

double *b_L = malloc(TAILLE_LAYER * sizeof(double));
double *b_LII = malloc(TAILLE_LAYERII * sizeof(double));
double *b_LIII = malloc(TAILLE_LAYERIII * sizeof(double));
double *b_O = malloc(TAILLE_OUTPUT * sizeof(double));

double *Z_L = malloc(TAILLE_OUTPUT * sizeof(double)); //Dans sigmoid output
double *Z_lIII = malloc(TAILLE_LAYERIII * sizeof(double));//Dans sigmoid layer III
double *Z_lII = malloc(TAILLE_LAYERII * sizeof(double));//Dans sigmoid layer II
double *Z_l = malloc(TAILLE_LAYER * sizeof(double)); //Dans sigmoid layer

double *ans3 = malloc(TAILLE_LAYERIII * sizeof(double)); //Dans ERROR_LAYERIII
double *ans2 = malloc(TAILLE_LAYERII * sizeof(double)); //Dans ERROR_LAYERII
double *ans = malloc(TAILLE_LAYER * sizeof(double));
double *eta = malloc(1*sizeof(double)); //Taux d'apprentissage à modifier dans NN_fct.h (fct_eta)

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
int pas = 1;
int nb_0 = 0;
int nb_1 = 0;
float bon = 0;
float faux = 0;
int fauxneg = 0;
int fauxpos = 0;
int bonneg = 0;
int bonpos = 0;
float null = 0;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
mpi_decomp_t decomp_layer1, decomp_layer2, decomp_input;
//if(rank ==0){
presentation(pas);
//}

mpi_decomp_init(TAILLE_LAYER, &decomp_layer1);
mpi_decomp_init(TAILLE_LAYERII, &decomp_layer2);
mpi_decomp_init(TAILLE_INPUT, &decomp_input);
//sleep(30);
 int nb_run = 0;
 int N = 301;
 while(nb_run < N){
   int i =0
   // double temps_mpi[N];
   // clock_t temps_clock[N];
   // double temps_mpi_mesure_mesure[N];
   // clock_t temps_clock_mesure_mesure[N];
   // double t1 =  0; //MPI_Wtime()
   // clock_t a = rdtsc();

  //debut_mesure_opti(t1,a,rank);
 	//debut_mesure_scalabilite(t1,a,rank);
 	//debut_mesure_stabilite(t1,a,0);

   fct_eta(eta,run);
   if(rank ==0){
     if ((run % 100) == 0){
       for (int i=0; i<100;i++)
       {
         PNG_to_INPUT(IMAGE[i],SOLUTION,&nb_0,&nb_1);
       }
     }
    //init_Input(INPUT);
   //SOLUTION[0]=0.0;
   //SOLUTION[1]=1.0;
   //nb_0=1;
   //nb_1=0;

    }

        //init_Input(INPUT);
   mem_0(LAYER, LAYERII, LAYERIII, OUTPUT);
MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(IMAGE[i],TAILLE_IMAGE,MPI_LONG_DOUBLE,0,MPI_COMM_WORLD);

    MPI_Bcast(SOLUTION,TAILLE_OUTPUT,MPI_LONG_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&nb_0,1,MPI_LONG_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&nb_1,1,MPI_LONG_DOUBLE,0,MPI_COMM_WORLD);
// /*
// convolution(W_C, CONVOLUTION, IMAGE);
// pooling(CONVOLUTION, POOLING);
// convolution2(W_C2,CONVOLUTION2, POOLING);
// pooling2(CONVOLUTION2, POOLING2);
// */
//memcpy(INPUT, IMAGE, pow(TAILLE_IMAGE,2)*sizeof(double)+1);
  INPUT = IMAGE[i];
MPI_Barrier(MPI_COMM_WORLD);
  front_prop(Z_L, Z_lIII, Z_lII, Z_l,INPUT,LAYER,LAYERII,LAYERIII,OUTPUT,b_L,b_LII, b_LIII,b_O,
						W_L,W_LII, W_LIII, W_O, &decomp_input, &decomp_layer1, &decomp_layer2);

  fct_cout(SOLUTION,OUTPUT,COUT, run);


  error_output(Z_L,ERROR_OUTPUT,SOLUTION,OUTPUT);
  transpose(W_OT,W_O, TAILLE_OUTPUT, TAILLE_LAYERIII);
  error_layerIII(ans3,W_OT,ERROR_LAYERIII,ERROR_OUTPUT,Z_lIII);
  transpose(W_LIIIT,W_LIII, TAILLE_LAYERIII, TAILLE_LAYERII);
  error_layerII(ans2, W_LIIIT, ERROR_LAYERII, ERROR_LAYERIII, Z_lII);
  transpose(W_LIIT, W_LII, TAILLE_LAYERII, TAILLE_LAYER);
  error_layer(ans,W_LIIT, ERROR_LAYER, ERROR_LAYERII, Z_l);
MPI_Barrier(MPI_COMM_WORLD);
  backprop(W_L, W_LII, W_LIII,W_O, b_L, b_LII, b_LIII, b_O, eta, ERROR_OUTPUT,
				 ERROR_LAYERIII, ERROR_LAYERII, ERROR_LAYER, INPUT, LAYER, LAYERII,
				 LAYERIII, OUTPUT,&decomp_input, &decomp_layer1, &decomp_layer2);

//resultat(OUTPUT,SOLUTION,COUT,run,pas,nb_0,nb_1,&fauxpos,&fauxneg,&bonneg,&bonpos,&bon,&faux,&null);
  // double t2 = 0;
  // clock_t b = rdtsc();
  //debut_mesure_mesure(t2,b,rank);
  //fin_mesure_opti(t1,a,t2,b,rank,temps_mpi,temps_clock,nb_run,N,argv[1]);
  //fin_mesure_scalabilite(t1,a,t2,b,rank,temps_mpi,temps_clock,nb_run,N,comm_size);
  //fin_mesure_stabilite(t1,a,t2,b,0,temps_mpi,temps_clock,nb_run,N,atoi(argv[1]));
  if(rank ==0){
  resultat2(OUTPUT,SOLUTION,COUT,run,pas,nb_0,nb_1,&fauxpos,&fauxneg,&bonneg,&bonpos,&bon,&faux,&null);
  }
  i++;
  run+= 1;
  nb_run++;
//
 }
double fin = MPI_Wtime();
double duree = fin - debut;
printf("mesure du temps : %f \n", duree);

free_all(INPUT,LAYER, LAYERII, LAYERIII, OUTPUT,SOLUTION,COUT,ERROR_OUTPUT,
				 ERROR_LAYERIII, ERROR_LAYERII, ERROR_LAYER, W_L, W_LII, W_LIII, W_O,
				 W_OT,W_LIIIT, W_LIIT, b_L, b_LII, b_LIII, b_O,Z_L, Z_lIII, Z_lII, Z_l,
				 ans3, ans2,ans, eta, IMAGE, CONVOLUTION, W_C, POOLING, CONVOLUTION2, W_C2, POOLING2);
MPI_Finalize();

return 0;
}

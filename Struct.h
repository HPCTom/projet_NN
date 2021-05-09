#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#define PNG_DEBUG 3
#include <png.h>

#define NB_LAYER 3
//revérifier les tailles il y a des erreurs de calcul
#define TAILLE_IMAGE 50 //IMAGE 50X50 DONC 50 EST UNE DIMENSION DE L'IMAGE
#define TAILLE_POOL 576 // (TAILLE_CONVOLUTION = 2304) / 4 = 576
#define DIM_POOL 24 //POOL est une matrice 24x24
//CONVOLUTION2 est donc une matrice de 22*22 = 484
#define TAILLE_POOLII 121 // TAILLE_CONVOLUTION2/4 = 121
#define TAILLE_INPUT 2500 //A CHANGÉ APRES INTRO CONVOLUTION
#define TAILLE_LAYER  1200
#define TAILLE_LAYERII 450
#define TAILLE_LAYERIII 20
#define TAILLE_OUTPUT 2

void presentation(int pas){
  printf(("Le réseau est un réseau Fully Connected avec sigmoid et est composé de:\n\t 1 input de %d neuronnes (images 50x50 pixels) \n\t %d middlelayer de %d neuronnes \n\t 1 output de %d neuronnes\n"),TAILLE_INPUT,NB_LAYER,TAILLE_LAYER,TAILLE_OUTPUT);
  printf("Les biais et les poids sont modifiés lors de la back-propagation.\n");
  printf("\n\n");
  printf("!!! Affichage des runs par pas de %d, peut etre modifier dans main.c dans la variable 'pas' (1 run  = front_prop + back_prop) !!!\n\n",pas);
  printf("!!! Il se peut qu'une execution ne soit pas interpretable (OUTPUT[i] bloqué ou error mem par exemple), relancer le code !!!\n\n");
  printf("!!! J'invite également à changer le taux d'apprentissage dans la fonction 'fct_eta' dans 'NN_fct.h', pour arreter l'apprentissage CTRL+C !!!\n\n");
  printf("!!! NB 0 le nombre d'images non cancéreuses, NB 1 le nombre d'images cancéreuses  !!!\n\n");
  printf("!!! NB BON le nombre de succès, NB FAUX le nombre d'échecs et NB NULL le nombre de résultats inexploitables !!!\n\n");
  printf("NB: le sleep(30) permettant de lire cette introduction peu etre retirer dans main.c\n\n");
  printf("Le code va bientot se lancer...\n");
}
/*******************************************************
 definition de la structure LAYER_S
 structure d'une couche de réseau
 size: taille de la couche de neuronnes
 neuron : tableau de valeurs des neuronnes
 weight: matrice de poids de la couche
 bias: tableau des biais des neurones
 Z: tableau de valeur de la fonction d'activation
 error: tableau des erreurs sur les pois
*********************************************************/
struct LAYER_S {
  int size;
  int dim_w;
  long double *neuron;
  long double *weight;
  long double *bias;
  long double *Z;
  long double *error;
};
typedef struct LAYER_S LAYER_T;  // definition du type LAYER_T qui modelise une couche de neuronne

/*****************************************************************
Definition de la structure neuralNet_s
modelise le reseau de neuronnes
dim_out: taille de la couche d'entree ,l'output
dim_in: taille de la couche de sortie, l'input
nbr_hidd: nombre de couche cachée ou d'hidden layer
*layer: tableau de structure LAYER_T de taille nbr_hidd
output: couche d'entree
input: couche de sortie
******************************************************************/
struct neuralNet_s {
  int dim_out;
  int dim_in;
  int nbr_hidd;
  int *dim_hidd;
  LAYER_T *layer;
  long double *output;
  long double *error_out;
  long double *w_out;
  long double *input;
};
typedef struct neuralNet_s neuralNet_t;  // definition du type qui modelisera notre reseau de neuronne

void free_layer(LAYER_T *layer){
  free(layer->neuron);
  free(layer->weight);
  free(layer->bias);
  free(layer->Z);
  free(layer->error);
  layer->size=0;
  layer->dim_w=0;
}

void free_neuralNetwork(neuralNet_t *neuralNet){
  int i;
  free(neuralNet->input);
  free(neuralNet->output);
  free(neuralNet->w_out);
  free(neuralNet->error_out);
  for(i = 0 ; i < neuralNet->nbr_hidd;i++)
  {
    free_layer(&neuralNet->layer[i]);
    free(&neuralNet->layer[i]);
  }
  neuralNet->dim_out =0;
  neuralNet->dim_in=0;
  neuralNet->nbr_hidd =0;
  free(neuralNet->dim_hidd);
}
/***********************************************************************
  allocation_layer() alloue l'espace mémoire d'une couche de neurones
  @*layer: pointeur de layer
  @dim: taille du layer
*************************************************************************/

void allocation_layer(LAYER_T *layer, int dim){
  layer->size = dim;
  layer->neuron=(long double*)malloc(layer->size*sizeof(long double));
  layer->bias=(long double*)malloc(layer->size*sizeof(long double));
  layer->Z = (long double*)malloc(layer->size*sizeof(long double));
  layer->error=(long double *)malloc(layer->size*sizeof(long double));
}

/**************************************************************************
  allocation_weight() alloue l'espace memoire de la matrice de poid
  @*l1: pointeur du layer 1 associe au la matrice de poid
  @*l2: pointeur de layer 2 lie au layer 1
*****************************************************************************/
void allocation_weight(LAYER_T *l1, LAYER_T *l2){
  l1->dim_w = l1->size*l2->size;
  l1->weight=(long double*)malloc(l1->size*l2->size*sizeof(long double));
}

/***************************************************************************
  allocation_neualNet alloue l'espace mémoire necessaire pour le réseau
  de neuronnes , il fait appel aux autres fonctions defnis précedement
  @neuralNet: pointeur sur la structure du reseau de neuronne
  @nbr_hidd: nombre de couche cachee ou hidden layer
  @size_in: taille l'INPUT
  @size_out: taille de l'OUTPUT
  @sizes_hidd: tableau des tailles des hidden layers
****************************************************************************/
void allocation_neuralNet(neuralNet_t *neuralNet, int nbr_hidd, int size_in, int size_out, int *sizes_hidd){
  int i;
  neuralNet->output=(long double*)malloc(size_out*sizeof(long double));
  neuralNet->input=(long double*)malloc(size_in*sizeof(long double));
  neuralNet->nbr_hidd=nbr_hidd;
  neuralNet->dim_hidd=(int*)malloc(nbr_hidd*sizeof(int));
  neuralNet->layer=(LAYER_T*)malloc(nbr_hidd*sizeof(struct LAYER_S));
  int dim_wo = neuralNet->dim_out*neuralNet->dim_hidd[nbr_hidd-1];
  for(i = 0 ; i < nbr_hidd;i++)
  {
    neuralNet->dim_hidd[i]=sizes_hidd[i];
    allocation_layer(&neuralNet->layer[i],sizes_hidd[i]);
  }
  neuralNet->layer[0].dim_w = size_in*sizes_hidd[0];
  neuralNet->layer[0].weight=(long double*)malloc(size_in*sizes_hidd[0]*sizeof(long double));
  for(i=0;i<nbr_hidd-2;i++){

    allocation_weight(&neuralNet->layer[i+1],&neuralNet->layer[i]);
  }
  neuralNet->layer[nbr_hidd-1].dim_w = size_out*sizes_hidd[nbr_hidd-1];
  neuralNet->layer[nbr_hidd-1].weight=(long double*)malloc(size_in*sizes_hidd[nbr_hidd-1]*sizeof(long double));
  neuralNet->w_out=(long double*)malloc(dim_wo*sizeof(long double));
}

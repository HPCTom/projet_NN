#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#define PNG_DEBUG 3
#include <png.h>
#include <omp.h>

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

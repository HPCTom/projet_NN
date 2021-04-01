#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#define PNG_DEBUG 3
#include <png.h>

#define NB_LAYER 1

#define TAILLE_INPUT  2500
#define TAILLE_LAYER  20
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

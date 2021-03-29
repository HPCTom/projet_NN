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
#define TAILLE_LAYER  16
#define TAILLE_OUTPUT 2

void presentation(int Nb_layer,int Taille_input,int Taille_layer,int Taille_output){
  printf(("Le réseau est composé de:\n\t 1 input de %d neuronnes \n\t %d middlelayer de %d neuronnes \n\t 1 output de %d neuronnes\n"),Taille_input,Nb_layer,Taille_layer,Taille_output);
  printf("\n\n");
}

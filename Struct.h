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
#ifndef TAILLE_LAYER
#define TAILLE_LAYER  20
#endif
#define TAILLE_OUTPUT 2

void presentation(){
  printf(("Le réseau est un réseau Fully Connected avec sigmoid et est composé de:\n\t 1 input de %d neuronnes (images 50x50 pixels) \n\t %d middlelayer de %d neuronnes \n\t 1 output de %d neuronnes\n"),TAILLE_INPUT,NB_LAYER,TAILLE_LAYER,TAILLE_OUTPUT);
  printf("Les biais et les poids sont modifiés lors de la back-propagation.\n");
  printf("\n\n");
}

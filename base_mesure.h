#ifndef BASE_H
#define BASE_H

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#ifdef __i386
extern __inline__ uint64_t rdtsc(void) {
  uint64_t x;
  __asm__ volatile ("rdtsc" : "=A" (x));
  return x;
}

#elif defined __amd64
extern __inline__ uint64_t rdtsc(void) {
  uint64_t a, d;
  __asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
  return (d<<32) | a;
}
#endif

/////////////////////// Type double /////////////////////////////

double moyenne(int N,double *tab){
	double S = 0.0;
	for(int i=0; i<N; i++){
		S = S + tab[i];
	}
	return S/N;
}

double ecart_type(int N,double *tab){
	double S = 0.0;
	double moy = moyenne(N,tab);
	for(int i=0; i<N; i++){
		S = S + pow((tab[i]-moy),2);
	}
	return sqrt(S/N);
}

double pourcent_ecart_moy(int N, double *tab){
  double moy = moyenne(N,tab);
  double ecart = ecart_type(N,tab);

  return (ecart*100)/moy;
}


/////////////////////// Type clock_t /////////////////////////////
double moyenne2(int N,clock_t *tab){
	double S = 0.0;
	for(int i=0; i<N; i++){
		S = S + tab[i];
	}
	return S/N;
}


double ecart_type2(int N,clock_t *tab){
	double S = 0.0;
	double moy = moyenne2(N,tab);
	for(int i=0; i<N; i++){
		S = S + pow((tab[i]-moy),2);
	}
	return sqrt(S/N);
}

double pourcent_ecart_moy2(int N, clock_t *tab){
  double moy = moyenne2(N,tab);
  double ecart = ecart_type2(N,tab);

  return (ecart*100)/moy;
}



#endif

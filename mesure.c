#include "NN.h"

int main(int argc, char** arg[]){
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
	long double *Z_l = malloc(TAILLE_LAYER * sizeof(long double)); //Dans sigmoid layer:
	clock_t t_i,t_f;
	float t_init_input, t_front_prop,t_init_layer, t_init_w,t_init_b;

	t_i=clock();
	init_Input(INPUT);
	t_f=clock();
	t_init_input=(t_f-t_i)*1e-6;

	t_i=clock();
	init_Layer(LAYER);
	t_f=clock();
	t_init_layer=(t_f-t_i)*1e-6;

	t_i=clock();
	init_W(W_L,W_O);
	t_f=clock();
	t_init_w=(t_f-t_i)*1e-6;

	t_i=clock();
	init_b(b_L,TAILLE_LAYER);
	t_f=clock();
	t_init_b=(t_f-t_i)*1e-6;

	t_i =clock();
	front_prop(Z_L,Z_l,INPUT,LAYER,OUTPUT,b_L,b_O,W_L,W_O);
	t_f =clock();
	t_front_prop=(t_f-t_i)*1.0e-6;

	FILE* file = NULL;

	if ((file = fopen("mesure.csv","r")) == NULL){
		file = fopen("mesure.dat","a");
		fprintf(file,"#TAILLE_LAYER t#TEMPS front prop (cpu)\t#TEMPS init_input (cpu)\t#init_layer\t#init_w\t#init_b\n");
		fclose(file);

	}
	file = fopen("mesure.dat","a");
	fprintf(file,"%d\t%f\t%f\t%f\t%f\t%f\n", TAILLE_LAYER,t_front_prop,t_init_input,t_init_layer, t_init_w,t_init_b);
	//fprintf(file,"%d;%d;%d;%f\n", TAILLE_LAYER, TAILLE_LAYER * TAILLE_INPUT, TAILLE_LAYER * TAILLE_OUTPUT,temps);
	fclose(file);

	return EXIT_SUCCESS;
}

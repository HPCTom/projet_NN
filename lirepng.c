#include "lirepng.h"
#include <stdarg.h>
#include "dossier.h"
#define PNG_DEBUG 3


///////////////////////// Variables  /////////////////////////////
void abort_(const char * s, ...)
{
	va_list args;
  va_start(args, s);
  vfprintf(stderr, s, args);
  fprintf(stderr, "\n");
  va_end(args);
  abort();
}


void read_png_file(char* file_name)
{
	char header[8];    // 8 is the maximum size that can be checked

  /* open file and test for it being a png */
  FILE *fp = fopen(file_name, "rb");
  if (fp==NULL)
  	abort_("[read_png_file] File %s could not be opened for reading", file_name);
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8))
  	abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
  /* initialize stuff */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
		abort_("[read_png_file] png_create_read_struct failed");

	info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  	abort_("[read_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
  	abort_("[read_png_file] Error during init_io");

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);

  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  /* read file */
	if (setjmp(png_jmpbuf(png_ptr)))
		abort_("[read_png_file] Error during read_image");

  row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
  for (y=0; y<height; y++)
    row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

  png_read_image(png_ptr, row_pointers);
  fclose(fp);
}


void process_file(void)
{
	if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGB)
		abort_("[process_file] input file is not PNG_COLOR_TYPE_RGB");

  for (y=0; y<height; y++) {
  	png_byte* row = row_pointers[y];
    for (x=0; x<width; x++) {
    	png_byte* ptr = &(row[x*4]);
			//int offset = width*x+y;
      moy[x][y] = (ptr[0] + ptr[1] + ptr[2])/3;
		}
	}

    free(row_pointers);

}

int PNG_to_INPUT(long double *IMAGE, long double *SOLUTION,int* nb_0, int* nb_1){
	char chemin[100];
	char nom[100];
	strcpy(chemin,"Data");
	FILE* ptr_file = NULL;
	/*
	if((ptr_file = fopen("liste.txt","r")) == NULL){
		lireDossierRec(chemin);
		// fclose(ptr_file);
	}
	*/
	if ((piocherFichier(nom))==1){  //il verifie si c'est un dossier ou fichier
		if ((strstr(nom,"/0/")) !=0){
			float R =  (float)(rand()%10000) / 100 ;
			if (R <= 28.38){
				while((strstr(nom,"/0/")) !=NULL){
					piocherFichier(nom);
				}
			}
		}
		//printf("nom = %s\n",nom);
		read_png_file(nom);
		process_file();
	}
	if((strstr(nom,"ss0")!= NULL)){ // Non cancéreu
		SOLUTION[0]=0.0;
		//SOLUTION[1]=1.0;
		*nb_0 = *nb_0 + 1;
	}
	else if((strstr(nom,"ss1"))!=NULL){ //cancéreu
		SOLUTION[0]=1.0;
		//SOLUTION[1]=0.0;
		*nb_1 = *nb_1 + 1;
	}
 int k =0;
		for (int x=0; x < 50; x++){
			for (int y=0; y< 50; y++){
				IMAGE[k] = (moy[x][y]+1)/(256);
				// printf("moy[%d][%d] = %Lf\n",x,y,(moy[x][y]+1)/(256));
				// printf("pas d'erreur pour i = %d ; x = %d, y = %d, INPUT = %Lf\n",k,x,y,INPUT[k]);
				k++;
				//if(INPUT[k] == 0){
					//printf("INPUT EST ZERO a la pos i %d \n", i);
					//printf("[%d - %d] MOY %f \n",x,y,moy[x][y]);
				//}
	//printf("Input[%d], valeur =  %f \n",i,INPUT[i]); //tableau INPUT rangé de gauche à droite ligne par ligne
			}
		}

	return EXIT_SUCCESS;
}

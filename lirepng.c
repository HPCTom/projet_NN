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

// variables globales

/*int x, y;
int width, height;
png_byte color_type;
png_byte bit_depth;
png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;
double moy[50][50];
*/

void read_png_file(char* file_name)
{
    /*png_infop end_info = NULL;
    png_structp png_ptr=NULL;
    png_infop info_ptr = NULL;*/
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
	printf("x %d \n",width);
	printf("y %d \n",height);
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
   /* png_infop end_info = NULL;
    png_structp png_ptr=NULL;
    png_infop info_ptr = NULL;
    png_bytep * row_pointers;*/

	if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGB)
		abort_("[process_file] input file is not PNG_COLOR_TYPE_RGB");

  for (y=0; y<height; y++) {
  	png_byte* row = row_pointers[y];
    for (x=0; x<width; x++) {
    	png_byte* ptr = &(row[x*4]);
      //printf("Pixel at position [ %d - %d ] has RGB values: %d - %d - %d \n",
      //x, y, ptr[0], ptr[1], ptr[2]);
      moy[x][y] = (ptr[0] + ptr[1] + ptr[2])/3;
      ptr[0] = moy[x][y];
      //printf("now pixel at position has grayscale value %d \n",moy[x][y]);
        //printf("erreur 2 \n");
		}
        //printf("erreur 3 \n");
	}
    //printf("erreur 4 \n");
    free(row_pointers);
    //png_read_end (png_ptr, NULL);
    //png_destroy_read_struct (&png_ptr, &info_ptr, NULL);
}

int PNG_to_INPUT(long double *INPUT, long double *SOLUTION){
	char chemin[100];
	int nbr_rep, cpt;
	char nom[100];
	printf("Entrez le nom du dossier que l'on utilisera  ");
	scanf("%s", chemin);
	printf("Combien de fois voulez vous entrainez le réseau \n");
	scanf("%d", &nbr_rep);
 	//printf(" -- Lecture du dossier '%s' -- \n", chemin);
	//listFilesRecursively(chemin);
	lireDossierRec(chemin);

	printf(" -- Lecture du dossier '%s' -- \n", chemin);
	printf("Initialisation du réseaux de neurones  \n");

 	//printf("save : %s \n",save);
	while (cpt < nbr_rep){ /* Lecture du dossier. */;
	//printf(" lecture du fichier %s\n", fichierLu->d_name);  //affiche le nom du fichier lu
	//init_Input(INPUT, Taille_input);
	//if (argc != 2)
	//  abort_("Usage: program_name <file_in>");
	//closedir(rep);
		if ((piocherFichier(nom))==1){  //il verifie si c'est un dossier ou fichier
				//strcpy(chemin,save);
				printf("Pioche l'image %s\n",nom);
			 // strcat(chemin, fichierLu -> d_name);
				read_png_file(nom);
				process_file();
				}
				if((strstr(nom,"ss0")!= NULL)){
						SOLUTION[0]=0.0;
				}else if((strstr(nom,"ss1"))!=NULL){
						SOLUTION[0]=1.0;
				}
				printf("Solution affecte :%lf a %s \n", SOLUTION[0], nom);
				//strcpy(chemin,save);
	int i = 0;

		for (int x=0; x < 50; x++){

			i = x*50;
			for (int y=0; y< 50; y++){
				//i = i+1;
				INPUT[i] = (moy[x][y]+1)/(256);
						i = i+1;
						if(INPUT[i-1] == 0){
								//printf("INPUT EST ZERO a la pos i %d \n", i);
								//printf("[%d - %d] MOY %f \n",x,y,moy[x][y]);
						}
	//printf("Input[%d], valeur =  %f \n",i,INPUT[i]); //tableau INPUT rangé de gauche à droite ligne par ligne
		}
		i=0;
	}
}
	return EXIT_SUCCESS;
}

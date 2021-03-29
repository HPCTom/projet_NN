#include <png.h>
#define PNG_DEBUG 3


///////////////////////// Variables  /////////////////////////////
void abort_(const char * s, ...);

// variables globales

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;
long double moy[50][50];


void read_png_file(char* file_name);
void process_file(void);
int PNG_to_INPUT(long double *INPUT, long double *SOLUTION);

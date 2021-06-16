#include "headers/gnu_pipe.h"

void plot_function(char *file_name)
{
    FILE *gnupipe = NULL; 
	gnupipe = popen("gnuplot -persistent", "w");
    fprintf(gnupipe, "set terminal wxt size 1600,900\n");
    fprintf(gnupipe, "set style fill solid\n");
    fprintf(gnupipe, "plot 'data/%s.dat' lt rgb \"blue\"\n", file_name);
}

void plot_histogram(char *file_name, float min, float max)
{
    FILE *gnupipe = NULL; 
	gnupipe = popen("gnuplot -persistent", "w");
    fprintf(gnupipe, "set terminal wxt size 1600,900\n");
    fprintf(gnupipe, "set style fill solid\n");
    if (min!=0 && min!=max) fprintf(gnupipe, "set xrange [%f:%f]\n", min, max);
    fprintf(gnupipe, "plot 'data/%s_histogram.dat' with boxes lt rgb \"blue\"\n", file_name);
}
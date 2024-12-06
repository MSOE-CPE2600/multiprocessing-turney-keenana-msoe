/*****************************************************************************
* Filename: procesor.c
* Description: multiprocessing lab
* Author: Andrew Keenan
* Date: 11-22-24 
* Note: Processor for the image using methods I copied over from Mandel 
*****************************************************************************/
#include "jpegrw.h"
#include <pthread.h>
#include <stdlib.h>
typedef struct {
	imgRawImage *img;
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	int max;
	int start;
	int end;
} args;
/*
Return the number of iterations at point x, y
in the Mandelbrot space, up to a maximum of max.
*/
int iterations_at_point( double x, double y, int max )
{
	double x0 = x;
	double y0 = y;

	int iter = 0;

	while( (x*x + y*y <= 4) && iter < max ) {

		double xt = x*x - y*y + x0;
		double yt = 2*x*y + y0;

		x = xt;
		y = yt;

		iter++;
	}

	return iter;
}

/*
Convert a iteration number to a color.
Here, we just scale to gray with a maximum of imax.
Modify this function to make more interesting colors.
*/
int iteration_to_color( int iters, int max )
{
	int color = 0xFFFFFF*iters/(double)max;
	return color;
}

void *compute_rows(void *input) {
	// cast args to data
	args *values = (args*)input;
	// pull out raw img
	imgRawImage *img = values->img;
	int width = img->width;
	int height = img->height;
	// pull out other data into variables
	double xmin = values->xmin;
	double xmax = values->xmax;
	double ymin = values->ymin;
	double ymax = values->ymax;
	int max = values->max;

	for(int j= values->start;j<values->end;j++) {

		for(int i=0;i<width;i++) {

			// Determine the point in x,y space for that pixel.
			double x = xmin + i*(xmax-xmin)/width;
			double y = ymin + j*(ymax-ymin)/height;

			// Compute the iterations at that point.
			int iters = iterations_at_point(x,y,max);

			// Set the pixel in the bitmap.
			setPixelCOLOR(img,i,j,iteration_to_color(iters,max));
		}
	}
	return NULL;
}

/*
Compute an entire Mandelbrot image, writing each point to the given bitmap.
Scale the image to the range (xmin-xmax,ymin-ymax), limiting iterations to "max"
*/
void compute_image(imgRawImage* img, double xmin, double xmax, double ymin, double ymax, int max, int threads )
{
	// initialize variables for threads
	pthread_t pthreads[threads];
	args data[threads];
	// setup image parameters 
	int height = img->height;
    int num_rows = height / threads;
    int leftover = height % threads;

	// loop through each thread and chunk off portion of image
	for (int i = 0; i < threads; i++) {
		// set data
		data[i].img = img;
        data[i].xmin = xmin;
        data[i].xmax = xmax;
        data[i].ymin = ymin;
        data[i].ymax = ymax;
        data[i].max = max;
		data[i].start = i * num_rows;
		data[i].end = data[i].start + num_rows;
		// handle the leftover rows
		if (i == threads - 1) {
			data[i].end += leftover; 
		}
		// create the thread
		pthread_create(&pthreads[i], NULL, compute_rows, (void*)&data[i]);
	}
	// wait for all threads to complete
	for (int i = 0; i < threads; i++) {
		pthread_join(pthreads[i], NULL);
	}
}


/*****************************************************************************
* Filename: processor.h
* Description: multiprocessing lab
* Author: Andrew Keenan
* Date: 11-22-24
* Note: Header file for mandel processes that I copied over
*****************************************************************************/
#include "jpegrw.h"
static int iteration_to_color( int i, int max );
static int iterations_at_point( double x, double y, int max );
static void compute_image( imgRawImage *img, double xmin, double xmax,
									double ymin, double ymax, int max );
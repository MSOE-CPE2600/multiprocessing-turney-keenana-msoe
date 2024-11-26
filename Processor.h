/*****************************************************************************
* Filename: processor.h
* Description: multiprocessing lab
* Author: Andrew Keenan
* Date: 11-22-24 
* Note: Header file for mandel processes that I copied over
*****************************************************************************/
#include "jpegrw.h"
int iteration_to_color( int i, int max );
int iterations_at_point( double x, double y, int max );
void compute_image( imgRawImage *img, double xmin, double xmax,
									double ymin, double ymax, int max );
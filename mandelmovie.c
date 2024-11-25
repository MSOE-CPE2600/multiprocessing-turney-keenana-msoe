/*****************************************************************************
* Filename: mandelmovie.c
* Description: multiprocessing lab
* Author: Andrew Keenan
* Date: 11-22-24
* Note:
*****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/wait.h>
#include "jpegrw.h"
#define TOTAL_IMAGES 50

int main(int argc, char *argv[]) {
    int processes;
    char c;
    // argument parsing to find number of child processes
    while ((c = getopt(argc, argv, "p:")) != -1) {
        switch (c) {
            case 'p':
                processes = atoi(optarg);
                break;
            default:
                printf("Error recognizing number of processes: try -p <NUM>\n");
                return 0;
                break;
        }
    }
    // display status message
    printf("Using %d processes\n", processes);

    // declare a semaphore
    sem_t *sem = sem_open("/sem", O_CREAT, 0666, processes);
    if (sem == SEM_FAILED) {
        printf("Error with creating semaphore\n");
        return 0;
    }

    // loop through each image using the semaphore
    for (int i = 0; i < TOTAL_IMAGES; i++) {
        sem_wait(sem);
        int pid = fork();
        if (pid == -1) {
            printf("error forking terminating process\n");
            return 0;
        } else if (pid == 0) { // child
            // setup output file
            char filename[100];
            sprintf(filename, "mandel_%d.jpg", i);
            // setup image 
            double xscale = 4.0 - (i * 0.04);
            double yscale = xscale * 1.0; 
            double xcenter = 0.0;
            double ycenter = 0.0; 
            int image_width = 1000;
            int image_height = 1000;
            int max_iter = 1000;
        }
    }

}
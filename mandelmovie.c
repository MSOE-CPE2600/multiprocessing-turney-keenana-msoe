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
#include <fcntl.h>
#include "jpegrw.h"
#include "processor.h"
#define TOTAL_IMAGES 50

int main(int argc, char *argv[]) {
    int processes;
    int threads;
    char c;
    sem_t *sem;
    // argument parsing to find number of child processes
    while ((c = getopt(argc, argv, "p:t:")) != -1) {
        switch (c) {
            case 'p':
                processes = atoi(optarg);
                printf("processes : %d\n", processes);
                break;
            case 't':
                threads = atoi(optarg);
                printf("Threads: %d\n", threads);
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
    sem = sem_open("/mysem", O_CREAT, 0666, processes);
    printf("sem created\n");
    if (sem == SEM_FAILED) {
        printf("Error with creating semaphore\n");
        return 0;
    }
    printf("processing image\n");
    // loop through each image using the semaphore
    for (int i = 0; i < TOTAL_IMAGES; i++) {
        sem_wait(sem);
        int pid = fork();
        if (pid == -1) {
            printf("error forking terminating process\n");
            return 0;
        } else if (pid == 0) { 
            // setup output file
            char filename[100];
            sprintf(filename, "mandel_%d.jpg", i);
            // setup image 
            double xscale = 4.0 - (i * 0.04);
            double yscale = xscale; 
            double xcenter = 0.0;
            double ycenter = 0.0; 
            int width = 1000;
            int height = 1000;
            int max_iter = 1000;
            // initialize image
            imgRawImage *img = initRawImage(width, height);
            setImageCOLOR(img, 0);
            // create the image using mandel processes
            compute_image(img, xcenter - xscale / 2, xcenter + xscale / 2,
                          ycenter - yscale / 2, ycenter + yscale / 2, max_iter, threads);
            // save the image to a file
            storeJpegImageFile(img, filename);
            // cleanup image
            freeRawImage(img);
            // status message
            printf("Image #%d created\n", i);
            // free up a semaphore slot
            sem_post(sem);
            return 0;
        } 
    }
    // wait for processes to finish
    while (wait(NULL) > 0);

    // cleanup semaphore and exit
    if (sem_close(sem) == -1) {
        printf("Closing semaphore failed memory leaked\n");
    }
    if (sem_unlink("/mysem") == -1) {
        printf("Unlinking semaphore failed memory leaked\n");
    }
    return 0;
}
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "blob2pass.hh"
#include "execute.hh"

int main(int argc, char *argv[])
{
    srand((unsigned) time(0));

    int w = 120;
    int h = 20;
    
    int ** img = new int*[h];
    for (int i = 0; i < h; i ++) {
        img[i] = new int[w];
        for (int j = 0; j < w; j++) {
            int randInt = rand() % 3;
            if (randInt < 1) {
                img[i][j] = 1;
            } else {
                img[i][j] = 0;
            }
        }
    }

    // printImg(img, w, h);

    int time = clock_gettime(CLOCK_MONOTONIC,&ts);
    printf("time before: %ld, %ld \n", ts.tv_sec, ts.tv_nsec);

    while(true) {
        int ** blobImg = blob2pass(img, w, h);
        free_labelmap();
        usleep(20000);
    }

    int ** blobImg = blob2pass(img, w, h);

    time = clock_gettime(CLOCK_MONOTONIC,&ts);
    printf("time after: %ld, %ld \n", ts.tv_sec, ts.tv_nsec);

    // printf("\nBLOB IMAGE: \n");
    // printImg(blobImg, w, h);
    // free_labelmap();

    return 0;
}

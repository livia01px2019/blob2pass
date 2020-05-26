#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include "blob2pass.hh"
#include "execute.hh"

int main(int argc, char *argv[])
{
    srand((unsigned) time(0));

    int size = 5;
    
    int ** img = new int*[size];
    for (int i = 0; i < size; i ++) {
        img[i] = new int[size];
        for (int j = 0; j < size; j++) {
            img[i][j] = rand()%2;
        }
    }
    printImg(img, size, size);

    int ** blobImg = blob2pass(img, size, size);
    printf("\nBLOB IMAGE: \n");
    printImg(blobImg, size, size);

    free_labelmap();
    return 0;
}

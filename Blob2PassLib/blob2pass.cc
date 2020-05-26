#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "blob2pass.hh"

int* uf = 0;
int** labelmap = 0;
int height;

int** blob2pass(int** img, int w, int h) {
    labelmap = new int*[h];
    for (int i = 0; i < h; i ++) {
        labelmap[i] = new int[w];
        memset(labelmap[i],0,w*sizeof(int));
    }
    height = h;
    uf = new int[10000];

    int time = clock_gettime(CLOCK_MONOTONIC,&ts);
    printf("before pass 1: %ld, %ld \n", ts.tv_sec, ts.tv_nsec);

    // Pass 1
    int labelmax = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if(img[i][j] == 1) {
                neighborsStruct neighbors = findNeighbors(labelmap, i, j, w, h);
                int lowest = __INT_MAX__;

                int nonzeroNeighbors[4];
                int nonzeroNeighborCnt = 0;

                // finding lowest nonzero label out of neighbors
                for (int k = 0; k < 4; k++) {
                    int currLabel = neighbors.arr[k];
                    if (currLabel != 0) {
                        // adding current label to nonzero labels
                        nonzeroNeighbors[nonzeroNeighborCnt] = currLabel;
                        nonzeroNeighborCnt ++;
                        if (currLabel < lowest) {
                            lowest = currLabel;
                        }
                    }
                }

                // Joining equivalent labels
                for (int k = 0; k < nonzeroNeighborCnt - 1; k++) {
                    join(nonzeroNeighbors[k], nonzeroNeighbors[k+1]);
                }

                // assigning current label
                if (lowest == __INT_MAX__) {
                    labelmax ++;
                    labelmap[i][j] = labelmax;
                } else {
                    labelmap[i][j] = lowest;
                }
            }
        }
    }
    time = clock_gettime(CLOCK_MONOTONIC,&ts);
    printf("before pass 2: %ld, %ld \n", ts.tv_sec, ts.tv_nsec);

    // Pass 2
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if(labelmap[i][j] != 0) {
                labelmap[i][j] = root(labelmap[i][j]);
            }
        }
    }
    delete[] uf;
    return labelmap;
}

// return NW, N, NE, and W values in a neighborsStruct
neighborsStruct findNeighbors(int** img, int x, int y, int w, int h) {
    bool top = (x == 0);
    bool left = (y == 0); 
    bool right = (y == (w-1));

    struct neighborsStruct ns;

    if (top) {
        ns.arr[0] = 0;
        ns.arr[1] = 0;
        ns.arr[2] = 0;
        if (left) {
            ns.arr[3] = 0;
        } else {
            ns.arr[3] = img[x][y-1];
        }
    } else {
        ns.arr[1] = img[x-1][y];
        if (left) {
            ns.arr[0] = 0;
            ns.arr[3] = 0;
        } else {
            ns.arr[0] = img[x-1][y-1];
            ns.arr[3] = img[x][y-1];
        }
        if (right) {
            ns.arr[2] = 0;
        } else {
            ns.arr[2] = img[x-1][y+1];
        }
    }
    return ns;
}

// UNION FIND

// find the root
int root(int x) {
    int r = x;
    
    while(uf[r] > 0) {
        r = uf[r];
    }

    while(uf[x]>0){
        int tmp = uf[x];
        uf[x] = r;
        x = tmp;
    }

    return r;
}

// join two numbers
void join(int x, int y) {
    x = root(x);
    y = root(y);

    if (x != y) {
        if (x < y) {
            uf[x] += uf[y];
            uf[y] = x;
        } else {
            uf[y] += uf[x];
            uf[x] = y;
        }
    }
}

void free_labelmap() {
    for (int i = 0; i < height; i ++) {
        delete[] labelmap[i];
    }
    delete[] labelmap;
}

void printImg(int** img, int w, int h) {
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            printf("%d", img[i][j]);
        }
        printf("\n");
    }
}

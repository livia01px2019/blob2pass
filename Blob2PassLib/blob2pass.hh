#ifndef __BLOB_2_PASS__
#define __BLOB_2_PASS__

struct neighborsStruct {
    int arr[4];
};
extern struct timespec ts;

int** blob2pass(int** img, int w, int h);
void free_labelmap();
neighborsStruct findNeighbors(int** img, int x, int y, int w, int h);
int root(int x);
void join(int x, int y);
void printImg(int** img, int w, int h);

#endif
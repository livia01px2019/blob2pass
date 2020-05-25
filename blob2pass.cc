#include "blob2pass.hh"

struct neighborsStruct {
    int arr[4];
};

int* uf = 0;
int** labelmap = 0;
int height;

int** blob2pass(int** img, int w, int h) {
    labelmap = new int*[h];
    for (int i = 0; i < h; i ++) {
        labelmap[i] = new int[w];
    }
    height = h;
    uf = new int[w * h];

    int labelmax = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if(img[i][j] == 1) {
                neighborsStruct neighbors = findNeighbors(img, i, j, w, h);
                int lowest = __INT_MAX__;
                for (int k = 0; k < 4; k++) {
                    int currLabel = neighbors.arr[k];
                    if (currLabel != 0) {
                        if (k != 0) {
                            join(k-1, k);
                        }
                        if (neighbors.arr[k] > lowest) {
                            lowest = neighbors.arr[k];
                        }
                    }
                }
                if (lowest == __INT_MAX__) {
                    labelmax ++;
                    labelmap[i][j] = labelmax;
                } else {
                    labelmap[i][j] = lowest;
                }
            }
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if(labelmap[i][j] != 0) {
                labelmap[i][j] = root(labelmap[i][j]);
            }
        }
    }

    delete[] uf;
}

neighborsStruct findNeighbors(const int** img, int x, int y, int w, int h) {
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
            ns.arr[2] = img[x+1][y+1];
        }
    }
    return ns;
}

int root(int x) {
    int r = x;
    
    while(uf[r] >= 0) {
        r = uf[r];
    }

    while(uf[x] >= 0) {
        uf[x] = r;
    }

    return r;
}

void join(int x, int y) {
    x = root(x);
    y = root(y);

    if (x < y) {
        uf[y] = x;
    } else {
        uf[x] = y;
    }
}

void free_labelmap() {
    for (int i = 0; i < height; i ++) {
        delete[] labelmap[i];
    }
    delete[] labelmap;
}

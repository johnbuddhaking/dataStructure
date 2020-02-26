#ifndef _TSMATRIX_H
#define _TSMATRIX_H

#define MAX_SIZE 100

struct Triple {
    int i;
    int j;
    ElemType e;
};

struct TSMatrix {
    Triple data[MAX_SIZE + 1];
    int mu; // rows num
    int nu; // columns num
    int tu; // non-zero elements num
};
#endif

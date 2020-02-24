#ifndef _ARRAY_H
#define _ARRAY_H

#define MAX_ARRAY_DIM 8

struct Array{
    ElemType * base;
    int dim;
    int * bounds;
    int * constants; // 定位速乘数
};
#endif

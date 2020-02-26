#ifndef _RLSMATRIX_H
#define _RLSMATRIX_H

#define MAX_SIZE 100 // 非零元个数最大值
#define MAX_RC 20 // 最大行数

struct Triple {
    int i;
    int j;
    ElemType e;
};

struct RLSMatrix {
    Triple data[MAX_SIZE + 1];
    int rpos[MAX_RC + 1]; // 存放各行第一个非零元在data数组中的位置
    int mu; // row number
    int nu; // column number
    int tu; // element number
};

#endif

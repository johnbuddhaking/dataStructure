// File Name: main_fast_transpose.cpp
// Author: 
// Created Time: 2020年02月25日 星期二 21时34分16秒

#include "c1.h"
typedef int ElemType;
#include "tsmatrix.h"
#include "tsmatrix_bo.h"

int main(){

    TSMatrix A, B;
    printf("创建矩阵A:");
    CreateSMatrix(A);
    PrintSMatrix(A);

    FastTransposeSMatrix(A, B);
    printf("矩阵B(A的快速转置):\n");
    PrintSMatrix(B);
    return 0;
}

// File Name: main_array.cpp
// Author: 
// Created Time: 2020年02月24日 星期一 09时13分08秒

#include "c1.h"
typedef int ElemType;
#include "array.h"
#include "array_bo.h"


int main(){
    Array A;
    int dim = 3;
    int bound1 = 3;
    int bound2 = 4;
    int bound3 = 2;

    InitArray(A, dim, bound1, bound2, bound3);
    
    printf("A.bounds=");
    for (int i = 0; i < dim; ++i) {
        printf("%d", *(A.bounds + i));
    }
    printf("\n");

    printf("A.constants=");
    for (int i = 0; i < dim; ++i) {
        printf("%d", *(A.constants + i));
    }
    printf("\n");

    ElemType e;
    printf("%d页%d行%d列矩阵元素如下：\n", bound1, bound2, bound3);
    for (int i = 0; i < bound1; ++i) {
        for (int j = 0; j < bound2; ++j) {
            for (int k = 0; k < bound3; ++k) {
                Assign(A, i * 100 + j * 10 + k, i, j, k);

                Value(e, A, i, j, k);
                printf("A[%d][%d][%d] = %2d ", i, j, k, e);
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("A.base = \n");
    for (int i = 0; i < bound1 * bound2 * bound3; ++i) {
        printf("%4d", *(A.base + i));
        if (i % (bound2 * bound3) == bound2 * bound3 - 1){
            printf("\n");
        }
    }
    return 0;
}

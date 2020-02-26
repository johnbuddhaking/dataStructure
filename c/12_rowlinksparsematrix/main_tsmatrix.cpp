// File Name: main_tsmatrix.cpp
// Author: 
// Created Time: 2020年02月25日 星期二 09时15分07秒

#include "c1.h"
typedef int ElemType;
#include "rlsmatrix.h"
#include "rlsmatrix_bo.h"

struct a{
    int data[1];
};

int main(){
    freopen("input.txt", "r", stdin);
    
    RLSMatrix A, B, C;
    printf("创建矩阵A:\n");
    CreateSMatrix(A);
    PrintSMatrix(A);

    CopySMatrix(A, B);
    printf("由矩阵A复制矩阵B:\n");
    PrintSMatrix(B);

    DestroySMatrix(B);
    printf("销毁矩阵B后:\n");
    PrintSMatrix(B);

    printf("创建矩阵B2:(与矩阵A的行数，列数相同，行、列分别为%d, %d)\n", A.mu, A.nu);
    CreateSMatrix(B);
    PrintSMatrix(B);

    AddSMatrix(A, B, C);
    printf("矩阵C1(A+B):\n");
    PrintSMatrix(C);
    for (int i = 1; i <= C.mu; ++i) {
        printf("%d ", C.rpos[i]);
    }
    printf("\n");

    SubtSMatrix(A, B, C);
    printf("矩阵C2(A-B):\n");
    PrintSMatrix(C);
    
    TransposeSMatrix(A, C);
    printf("矩阵C3(A的转置):\n");
    PrintSMatrix(C);

    for (int i = 1; i <= C.mu; ++i) {
        printf("%d ", C.rpos[i]);
    }
    printf("\n");

    printf("创建矩阵A2:");
    CreateSMatrix(A);
    PrintSMatrix(A);

    printf("创建矩阵B3:(行数应与矩阵A2的列数相同 = %d)\n", A.nu);
    CreateSMatrix(B);
    PrintSMatrix(B);

    MultSMatrix(A, B, C);

    printf("矩阵C5(A*B):\n");
    PrintSMatrix(C);

    for (int i = 1; i <= C.mu; ++i) {
        printf("%d ", C.rpos[i]);
    }
    printf("\n");

    return 0;
}

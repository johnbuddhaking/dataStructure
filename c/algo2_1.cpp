/*************************************************************************
	> File Name: algo2-1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年03月16日 星期六 11时29分55秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include "c1.h"
typedef int ElemType;
#include "c2_1.h"
#include "bo2_1.h"
#include "func2_2.h"


void MergeList(SqList La, SqList Lb, SqList &Lc){

    ElemType* aPointer = La.elem;
    ElemType* bPointer = Lb.elem;

    while(aPointer <= La.elem + La.length - 1 && bPointer <= Lb.elem + Lb.length - 1){
        if(*aPointer <= *bPointer){
            ListInsert(Lc, Lc.length + 1, *aPointer++);
        }
        else{
            ListInsert(Lc, Lc.length + 1, *bPointer++);
        }

    }

    while(aPointer <= La.elem + La.length - 1){
        ListInsert(Lc, Lc.length + 1, *aPointer++);
    }

    while(bPointer <= Lb.elem + Lb.length - 1){
        ListInsert(Lc, Lc.length + 1, * bPointer++);
    }
}

int main(){
    SqList La, Lb, Lc;
    InitList(La);
    InitList(Lb);
    InitList(Lc);

    for(int index = 1; index <= 5; ++index){
        ListInsert(La, index, index);
        ListInsert(Lb, index, index * 2);
    }

    printf("La = ");
    ListTraverse(La, print1);

    printf("Lb = ");
    ListTraverse(Lb, print1);

    MergeList(La, Lb, Lc);

    printf("Lc = ");
    ListTraverse(Lc, print1);

    return 0;

}

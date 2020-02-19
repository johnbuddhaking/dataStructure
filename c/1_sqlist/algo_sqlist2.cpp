/*************************************************************************
	> File Name: algo2_2.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年03月16日 星期六 22时05分24秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include "c1.h"
typedef int ElemType;

#define Sq

#ifdef Sq
#include "sqlist.h"
#include "sqlist_bo.h"
typedef SqList List;
#define printer print1

#else
#include "c2_2.h"
#include "bo2_2.h"
typedef LinkList List;
#define printer print

#endif


#include "func2_2.h"
#include "func_union_merge.h"

int main(){
    List La, Lb, Lc;
    int b[7] = {2, 6, 8, 9, 11, 15, 20};
    InitList(La);
    InitList(Lb);
    InitList(Lc);

    for(int index = 1; index <= 5; ++index){
        ListInsert(La, index, index);
    }

    printf("La = ");
    ListTraverse(La, printer);

    for(int index = 1; index <= 5; ++index){
        ListInsert(Lb, index, 2 * index);
    }

    printf("Lb = ");
    ListTraverse(Lb, printer);

    Union(La, Lb);
    printf("New La = ");
    ListTraverse(La, printer);

    ClearList(Lb);
    for(int index = 1; index <= 7; ++index){
        ListInsert(Lb, index, b[index - 1]);
    }
    printf("Lb = ");
    ListTraverse(Lb, printer);

    MergeList(La, Lb, Lc);
    printf("Lc = ");
    ListTraverse(Lc, printer);

    return 0;
}

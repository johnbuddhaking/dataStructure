/*************************************************************************
	> File Name: algo_linklist.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年03月16日 星期六 22时37分27秒
 ************************************************************************/

#include<iostream>
using namespace std;

#include "c1.h"
typedef int ElemType;

#include "linklist.h"
#include "linklist_bo.h"
#include "func2_2.h"


void CreateList(LinkList &L, int n){
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    printf("请输入%d个数据\n", n);
    for(int index = n; index > 0; --index){
        LNode* p = (LNode*)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
}

void CreateList1(LinkList &L, int n){
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    printf("请输入%d个数据\n", n);

    LNode* endp = L;

    for(int index = n; index > 0; --index){
        LNode* p = (LNode*)malloc(sizeof(LNode));
        scanf("%d", &p->data);
        
        endp->next = p;
        endp = p;
    }   
    endp->next = NULL;
}

void MergeList(LinkList La, LinkList &Lb, LinkList &Lc){
    Lc = La;

    LNode* ap = La;
    LNode* bp = Lb->next;

    while(ap->next && bp){
        if(ap->next->data <= bp->data){
            ap = ap->next;
        }
        else{
            LNode* tmpp = bp;
            bp = bp->next;

            tmpp->next = ap->next;
            ap->next = tmpp;
            ap = ap->next;
        }
    }
    
    if(bp){
        ap->next = bp;
    }

    free(Lb);
    Lb = NULL;
}

int main(){
    int n = 5;
    LinkList La, Lb, Lc;
    printf("按非递减顺序，");
    CreateList1(La, n);
    printf("La = ");
    ListTraverse(La, print);

    printf("按非递增顺序，");
    CreateList(Lb, n);
    printf("Lb = ");
    ListTraverse(Lb, print);

    MergeList(La, Lb, Lc);
    printf("Lc = ");
    ListTraverse(Lc, print);

    return 0;
}

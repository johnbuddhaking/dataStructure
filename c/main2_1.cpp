/*************************************************************************
	> File Name: main2-1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年02月19日 星期二 07时43分29秒
 ************************************************************************/

#include<iostream>
using namespace std;

#include "c1.h"
typedef int ElemType;
#include "c2_1.h"
#include "bo2_1.h"
#include "func2_2.h"

Status sq(ElemType c1, ElemType c2){
    if(c1 == c2 * c2){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

void dbl(ElemType &c){
    c *= 2;
}

int main(){
    SqList L;
    Status status;
    InitList(L);
    printf("初始化L后，L.length = %d, L.listsize = %d, L.elem = %p\n", L.length, L.listsize, L.elem);

    for(int i = 1; i <= 5; ++i){
        status = ListInsert(L, 1, i);
    }

    printf("在L的表头依次插入1~5后，*L.elem = ");
    for(int index = 1; index <= 5; ++index){
        printf("%d ", *(L.elem + index - 1));
    }
    printf("\n调用ListTravrese()函数，依次输出表L中的元素：");
    ListTraverse(L, print1);


    status = ListEmpty(L);

    printf("L.length = %d, L.listsize = %d,", L.length, L.listsize);
    printf("L.elem = %p, L是否空？ status = %d\n", L.elem, status);

    ClearList(L);
    status = ListEmpty(L);

    printf("清空后，L.length = %d, L.listsize = %d,", L.length, L.listsize);
    printf("L.elem = %p, L是否空？ status = %d\n", L.elem, status);
    
    for(int index = 1; index <= 10; ++index){
        ListInsert(L, index, index);
    }

    printf("在L的表尾依次插入1~10后，L=");
    ListTraverse(L, print1);

    printf("L.length = %d, L.listsize = %d, L.elem = %p\n", L.length, L.listsize, L.elem);

    ListInsert(L, 1, 0);
    printf("在L的表头插入0后，L.length = %d, L.listsize = %d, L.elem = %p\n", L.length, L.listsize, L.elem);


    ElemType e;
    GetElem(L, 5, e);
    printf("第5个元素的值为%d\n", e);

    for(int index = 10; index <= 11; ++index){
        int k = LocateElem(L, index, equal);

        if(k){
            printf("第%d个元素的值为%d，", k, index);
        }
        else{
            printf("没有值为%d的元素。\n", index);
        }

    }

    for(int index = 3; index <= 4; ++index){
        int k = LocateElem(L, index, sq);

        if(k){
            printf("第%d个元素的值为%d的平方，", k, index);
        }
        else{
            printf("没有值为%d的平方的元素。\n",index);
        }
    }
    
    for(int index = 1; index <= 2; ++index){
        ElemType e0;
        GetElem(L, index, e0);

        status = PriorElem(L, e0, e);

        if(status == ERROR){
            printf("元素%d无前驱，", e0);
        }
        else{
            printf("元素%d的前驱为%d\n", e0, e);
        }
    }

    for(int index = ListLength(L) - 1; index <= ListLength(L); ++index){
        ElemType e0;
        GetElem(L, index, e0);

        status = NextElem(L, e0, e);

        if(status == ERROR){
            printf("元素%d无后继\n", e0);
        }
        else{
            printf("元素%d的后继为%d，", e0, e);
        }
    }

    for(int index = L.length + 1; index <= L.length; ++index){
        status = ListDelete(L, index, e);

        if(status == ERROR){
            printf("删除第%d个元素失败。", index);
        }
        else{
            printf("删除第%d个元素成功，其值为%d\n", index, e);
        }
    }


    ListTraverse(L, dbl);
    printf("L的元素值加倍后，L = ");
    ListTraverse(L, print1);


    DestroyList(L);
    printf("销毁L后，L.length = %d, L.listsize = %d, L.elem = %p\n", L.length, L.listsize, L.elem);
}

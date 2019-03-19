/*************************************************************************
	> File Name: func2_3.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月16日 星期六 16时37分39秒
 ************************************************************************/

#ifndef _FUNC2_3_H
#define _FUNC2_3_H

int main(){
    LinkList L;
    Status status;

    InitList(L);

    for(int index = 1; index <= 5; ++index){
        status = ListInsert(L, 1, index);
    }

    printf("在L的表头依次插入1~5后，L = ");
    ListTraverse(L, print);

    status = ListEmpty(L);
    printf("L是否为空？ status = %d(1:是 0:否)，表L的长度 = %d\n", status, ListLength(L));
    
    ClearList(L);
    printf("清空L后，L = ");
    ListTraverse(L, print);

    status = ListEmpty(L);
    printf("L是否为空？ status = %d(1:是 0:否)，表L的长度 = %d\n", status, ListLength(L));

    for(int index = 1; index <= 10; ++index){
        ListInsert(L, index, index);
    }
    printf("在L的表尾依次插入1~10后，L = ");
    ListTraverse(L, print);

    for(int index = 0; index <= 1; ++index){
#ifdef SLL
        int k = LocateElem(L, index);
        if(k){
            printf("值为%d的元素的位序为%d\n", index, k);
        }
#else
        int k = LocateElem(L, index, equal);
        if(k){
            printf("值为%d的元素的位序为%d\n", index, k);
            
        }
#endif
        else{
            printf("没有值为%d的元素，", index);
        }
    }


    ElemType e, e0;

    for(int index = 1; index <= 2; ++index){
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

        GetElem(L, index, e0);
        status = NextElem(L, e0, e);

        if(status == ERROR){
            printf("元素%d无后继.\n", e0);
        }
        else{
            printf("元素%d的后继为%d，", e0, e);
        }

    }

    int k = ListLength(L);

    for(int index = k + 1; index >= k; --index){
        status = ListDelete(L, index, e);

        if(status == ERROR){
            printf("删除第%d个元素失败（不存在此元素）。", index);
        }
        else{
            printf("删除第%d个元素成功，其值为%d\n", index, e);
        }
    }

    printf("依次输出L的元素：");
    ListTraverse(L, print);
    
    DestroyList(L);

#ifdef SLL
    printf("销毁L后，L = %p\n", L);
#endif

}

#endif

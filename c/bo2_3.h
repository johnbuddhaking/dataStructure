/*************************************************************************
	> File Name: bo2_3.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月17日 星期日 16时05分50秒
 ************************************************************************/

#ifndef _BO2_3_H
#define _BO2_3_H

#define DestroyList ClearList

void InitList(LinkList &L){
    L = NULL;
}

void ClearList(LinkList &L){
    LinkList p;

    while(L){
        p = L;
        L = L->next;
        free(p);
    }
}

Status ListEmpty(LinkList L){
    if(L){
        return FALSE;
    }
    else{
        return OK;
    }
}

int ListLength(LinkList L){
    int count = 0;

    LNode* p = L;

    while(p){
        ++count;
        p = p->next;
    }

    return count;
}

Status GetElem(LinkList L, int i, ElemType &e){
    int count = 0;
    LNode* p = L;

    while(p){
        ++count;
        
        if(count == i){
            e = p->data;
            return OK;
        }

        p = p->next;
    }

    return ERROR;


}

int LocateElem(LinkList L, ElemType e, Status(* compare)(ElemType, ElemType)){
    int count = 0;

    LNode* p = L;

    while(p){
        ++count;

        if(compare(e, p->data)){
            return count;
        }

        p = p->next;
    }

    return 0;
}

Status ListInsert(LinkList &L, int i, ElemType e){
    LNode* q = (LNode*)malloc(sizeof(ElemType));
    q->data = e;

    if(i == 1){
        q->next = L;
        L = q;
        return OK;
    }

    int count = 1;
    LNode* p = L;

    while(p){
        ++count;

        if(count == i){
            q->next = p->next;
            p->next = q;
            return OK;
        }

        p = p->next;

    }

    return ERROR;
}

Status ListDelete(LinkList &L, int i, ElemType &e){
    LNode* p;

    if(i == 1 && L){
        p = L;
        L = p->next;
        e = p->data;
        free(p);
        return OK;
    }

    p = L;
    int count = 1;

    while(p){
        ++count;

        if(count == i && p->next){
            LNode* q = p->next;
            p->next = q->next;
            e = q->data;
            free(q);
            return OK;
        }
        
        p = p->next;
    }
    
    return ERROR;

}

void ListTraverse(LinkList L, void(*vi)(ElemType)){
    LNode* p = L;

    while(p){
        vi(p->data);
        p = p->next;
    }
    printf("\n");
}

#endif


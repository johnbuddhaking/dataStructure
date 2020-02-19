/*************************************************************************
	> File Name: dulinklist_bo.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月19日 星期二 21时20分04秒
 ************************************************************************/

#ifndef _DULINKLIST_BO_H
#define _DULINKLIST_BO_H

void InitList(DuLinkList &L){
    L = (DuLinkList)malloc(sizeof(DuLNode));

    if(L){
        L->next = L->prior = L;
    }
    else{
        exit(OVERFLOW);
    }
}

void ClearList(DuLinkList L){
    DuLinkList p = L->next;

    while(p != L){
        p = p->next;
        free(p->prior);
    }

    L->next = L->prior = L;
}

void DestroyList(DuLinkList &L){
    ClearList(L);
    free(L);
    L = NULL;
}

Status ListEmpty(DuLinkList L){
    if(L->next == L && L->prior == L){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int ListLength(DuLinkList L){
    int count = 0;

    DuLinkList p = L->next;

    while(p != L){
        ++count;
        p = p->next;
    }

    return count;
}

Status GetElem(DuLinkList L, int i, ElemType &e){
    int count = 0;

    DuLinkList p = L;

    while(p->next != L){
        ++count;
        p = p->next;

        if(count == i){
            e = p->data;
            return OK;
        }
    }
    
    return ERROR;

}

int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType, ElemType)){
    int count = 0;

    DuLinkList p = L->next;

    while(p != L){
        ++count;

        if(compare(p->data, e)){
            return count;
        }

        p = p->next;
    }

    return 0;
}

Status PriorElem(DuLinkList L, ElemType cur_e, ElemType &pre_e){
    DuLinkList p = L->next->next;

    while(p != L){
        if(p->data == cur_e){
            pre_e = p->prior->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

Status NextElem(DuLinkList L, ElemType cur_e, ElemType &next_e){
    DuLinkList p = L->next->next;

    while(p != L){
        if(p->prior->data == cur_e){
            next_e = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

DuLinkList GetElemP(DuLinkList L, int i){
    int j;
    DuLinkList p = L;

    if(i < 0 || i > ListLength(L)){
        return NULL;
    }

    for(j = 1; j <= i; ++j){
        p = p->next;
    }

    return p;
}

Status ListInsert(DuLinkList L, int i, ElemType e){
    
    int count = 0;
    DuLinkList p = L;

    while(p->next != L && count < i - 1){
        p = p->next;
        ++count;
    }

    if(count != i - 1){
        return ERROR;
    }

    DuLinkList q = (DuLinkList)malloc(sizeof(DuLNode));
    q->data = e;
    
    q->prior = p;
    q->next = p->next;

    p->next = q;
    q->next->prior = q;
    return OK;


}


Status ListDelete(DuLinkList L, int i, ElemType &e){
    int count = 0;
    DuLinkList p = L;

    while(p->next != L && count < i - 1){
        p = p->next;
        ++count;
    }

    if(count != i - 1){
        return ERROR;
    }

    DuLinkList q = p->next;
    e = q->data;

    p->next = q->next;
    q->next->prior = p;
    
    free(q);

    return OK;
}

void ListTraverse(DuLinkList L, void(*visit)(ElemType)){
    DuLinkList p = L->next;

    while(p != L){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}

void ListTraverseBack(DuLinkList L, void(*visit)(ElemType)){
    DuLinkList p = L->prior;

    while(p != L){
        visit(p->data);
        p = p->prior;
    }
    printf("\n");
}
#endif

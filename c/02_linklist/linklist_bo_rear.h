/*************************************************************************
	> File Name: linklist_bo_rear.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月18日 星期一 07时41分57秒
 ************************************************************************/

#ifndef _LINKLIST_BO_REAR_H
#define _LINKLIST_BO_REAR_H

void InitList(LinkList &L){
    L = (LNode*)malloc(sizeof(LNode));

    if(!L){
        exit(OVERFLOW);
    }

    L->next = L;
}

void ClearList(LinkList &L){
    LinkList p = L->next;

    while(p != L){
        LinkList q = p;
        p = p->next;
        free(q);
    }

    L->next = L;
}

void DestroyList(LinkList &L){
    ClearList(L);
    free(L);
    L = NULL;
}

Status ListEmpty(LinkList L){
    if(L->next == L){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int ListLength(LinkList L){
    int count = 0;

    LNode* p = L->next;

    while(p != L){
        ++count;
        p = p->next;
    }

    return count;
}

Status GetElem(LinkList L, int i, ElemType &e){
    int count = 0;

    LNode* p = L->next;

    while(p != L){
        ++count;

        if(count == i){
            e = p->data;
            return OK;
        }

        p = p->next;
    }

    return ERROR;
}

int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType)){
    int count = 0;

    LNode* p = L->next;

    while(p != L){
        ++count;

        if(p->data == e){
            return count;
        }

        p = p->next;
    }

    return 0;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e){
    LNode* p = L->next;

    while(p != L && p->next != L){
        if(p->next->data == cur_e){
            pre_e = p->data;
            return OK;
        }

        p = p->next;
    }

    return ERROR;
}

Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e){
    LNode* p = L->next;

    while(p != L && p->next != L){
        if(p->data == cur_e){
            next_e = p->next->data;
            return OK;
        }

        p = p->next;
    }

   return ERROR; 
}

Status ListInsert(LinkList &L, int i, ElemType e){

    if(i < 1 || i > ListLength(L) + 1){
        return ERROR;
    }

    LinkList p = L;
    int idx = 1;

    while(idx < i){
        ++idx;
        p = p->next;
    }

    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;

    return OK;
}

Status ListDelete(LinkList &L, int i, ElemType &e){
    if(i < 1 || i > ListLength(L) ){
        return ERROR;
    }

    LinkList p = L;
    int idx = 1;

    while(idx < i){
        idx++;
        p = p->next;
    }

    LNode* q = p->next;
    p->next = q->next;
    
    e = q->data;
    free(q);

    return OK;
}
    
void ListTraverse(LinkList L, void(*vi)(ElemType)){
    LNode* p = L->next;


    while(p != L){
        vi(p->data);
        p = p->next;
    }
    printf("\n");
}

#endif

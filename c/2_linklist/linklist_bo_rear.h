/*************************************************************************
	> File Name: bo2_6.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月18日 星期一 07时41分57秒
 ************************************************************************/

#ifndef _BO2_6_H
#define _BO2_6_H

void InitList(LinkList &L){
    L = (LNode*)malloc(sizeof(LNode));

    if(!L){
        exit(OVERFLOW);
    }

    L->next = L;

}

void ClearList(LinkList &L){
    L = L->next;
    LinkList p = L;

    while(p->next != L){
        LinkList q = p->next;
        p->next = q->next;
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

    while(p->next != L->next){
        p = p->next;
        ++count;
    }

    return count;
}

Status GetElem(LinkList L, int i, ElemType &e){
    int count = 0;

    LNode* p = L->next;

    while(p->next != L->next){
        ++count;

        if(count == i){
            e = p->next->data;
            return OK;
        }

        p = p->next;
    }

    return ERROR;
}

int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType)){
    int count = 0;

    LNode* p = L->next;

    while(p->next != L->next){
        ++count;

        p = p->next;

        if(p->data == e){
            return count;
        }
    }

    return 0;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e){
    LNode* p = L->next->next;
    LNode* q = p->next;

    while(q != L->next){
        if(q->data == cur_e){
            pre_e = p->data;
            return OK;
        }

        p = q;
        q = p->next;
    }

    return ERROR;
}

Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e){
    LNode* p = L->next->next;
    LNode* q = p->next;

    while(q != L->next){
        if(p->data == cur_e){
            next_e = q->data;
            return OK;
        }

        p = q;
        q = p->next;
    }

   return ERROR; 
}

Status ListInsert(LinkList &L, int i, ElemType e){

    if(i <= 0 || i > ListLength(L) + 1){
        return ERROR;
    }

    LinkList p = L->next;
    int j = 0;

    while(j < i - 1){
        j++;
        p = p->next;
    }

    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;

    if(p == L){
        L = s;
    }

    return OK;
}

Status ListDelete(LinkList &L, int i, ElemType &e){
    if(i <= 0 || i > ListLength(L) ){
        return ERROR;
    }

    LinkList p = L->next;
    int j = 0;

    while(j < i - 1){
        j++;
        p = p->next;
    }

    LNode* q = p->next;
    e = q->data;
    p->next = q->next;

    if(L == q){
        L = p;
    }

    free(q);

    return OK;
}
    
void ListTraverse(LinkList L, void(*vi)(ElemType)){
    LNode* p = L->next;


    while(p->next != L->next){
        vi(p->next->data);
        p = p->next;
    }
    printf("\n");
}

#endif

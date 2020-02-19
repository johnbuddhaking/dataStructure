/*************************************************************************
	> File Name: linklist_bo.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月16日 星期六 14时56分54秒
 ************************************************************************/

#ifndef _LINKLIST_BO_H
#define _LINKLIST_BO_H

void InitList(LinkList &L){
    L = (LinkList)malloc(sizeof(LNode));

    if(!L){
        exit(OVERFLOW);
    }

    L->next = NULL;
}

void DestroyList(LinkList &L){

    LNode* p;
    while(L){
        p = L->next;
        
        free(L);
        L = p;
    }
}

void ClearList(LinkList &L){
    DestroyList(L->next);
}

Status ListEmpty(LinkList L){
    if(L->next){
        return FALSE;
    }
    else{
        return TRUE;
    }
}

int ListLength(LinkList L){
    LNode *p = L;
    int count = 0;
    while(p->next){
        ++count;
        p = p->next;
    }
    return count;
}

Status GetElem(LinkList L, int i, ElemType &e){
    int count = 0;

    LNode *p = L;
    
    while(p->next){
        ++count;
        p = p->next;

        if(count == i){
            e = p->data;
            return OK;
        }
    }

    return ERROR;
}

int LocateElem(LinkList L, ElemType e, Status(* compare)(ElemType, ElemType)){
    LNode* p = L;
    int count = 0;

    while(p->next){
        ++count;
        p = p->next;
        
        if(compare(p->data, e)){
            return count;
        }

    }

    return 0;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e){
    LNode* p1 = L->next;
    LNode* p2;

    while(p1 && p1->next){
        p2 = p1->next;

        if(p2->data == cur_e){
            pre_e = p1->data;
            return OK;
        }

        p1 = p2;
    }

    return ERROR;
}


Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e){
    LNode* p = L->next;

    while(p && p->next){
        if(p->data == cur_e){
            next_e = p->next->data;
            return OK;
        }
        p = p->next;
    }

    return ERROR;
}

Status ListInsert(LinkList L, int i, ElemType e){
    int count = 0;
    LNode* p = L;
    LNode* auxp;

    while(p){
        ++count;
        
        if(count == i){
            auxp = p->next;

            p->next = (LNode*)malloc(sizeof(LNode));
            p->next->data = e;
            p->next->next = auxp;
            return OK;
        }

        p = p->next;
    }

    return ERROR;
}

Status ListDelete(LinkList L, int i, ElemType &e){
    
    LNode* p = L;
    int count = 0;

    while(p->next){
        ++count;

        if(count == i){
            LNode* deleteP = p->next;
            p->next = deleteP->next;

            e = deleteP->data;
            free(deleteP);
            deleteP = NULL;
            return OK;
        }

        p = p->next;
    }

    return ERROR;
}

void ListTraverse(LinkList L, void(* visit)(ElemType)){
    LNode* p = L;

    while(p->next){
        p = p->next;
        visit(p->data);
    }

    printf("\n");
}
#endif

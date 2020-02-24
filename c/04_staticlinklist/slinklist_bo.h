/*************************************************************************
	> File Name: slinklist_bo.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月17日 星期日 21时11分31秒
 ************************************************************************/

#ifndef _SLINKLIST_BO_H
#define _SLINKLIST_BO_H

#define DestroyList ClearList

int Malloc(SLinkList space){
    int i = space[0].cur;

    if(i){
        space[0].cur = space[i].cur;
    }

    return i;
}

void Free(SLinkList space, int k){
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

void InitList(SLinkList L){
    L[MAX_SIZE - 1].cur = 0;
    for(int index = 0; index < MAX_SIZE - 2; ++index){
        L[index].cur = index + 1;
    }
    L[MAX_SIZE - 2].cur = 0;
}


void ClearList(SLinkList L){
    InitList(L);
}

Status ListEmpty(SLinkList L){
    if(L[MAX_SIZE - 1].cur == 0){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int ListLength(SLinkList L){
    int count = 0;

    int cur = L[MAX_SIZE - 1].cur;

    while(cur){
        ++count;
        cur = L[cur].cur;
    }

    return count;
}

Status GetElem(SLinkList L, int i, ElemType &e){
    int count = 0;
    int cur = L[MAX_SIZE - 1].cur;

    while(cur){
        ++count;
        
        if(count == i){
            e = L[cur].data;
            return OK;
        }

        cur = L[cur].cur;
    }

    return ERROR;
}

int LocateElem(SLinkList L, ElemType e){

    int cur = L[MAX_SIZE - 1].cur;

    while(cur && L[cur].data != e){
        cur = L[cur].cur;
    }

    return cur;
}

Status PriorElem(SLinkList L, ElemType cur_e, ElemType &pre_e){
    
    int cur = L[MAX_SIZE - 1].cur;

    while(cur && L[cur].cur){
        if(L[L[cur].cur].data == cur_e){
            pre_e = L[cur].data;
            return OK;
        }

        cur = L[cur].cur;
    }

    return ERROR;
}

Status NextElem(SLinkList L, ElemType cur_e, ElemType &next_e){
    int cur = L[MAX_SIZE - 1].cur;

    while(cur && L[cur].cur){
        if(L[cur].data == cur_e){
            next_e = L[L[cur].cur].data;
            return OK;
        }

        cur = L[cur].cur;
    }

    return ERROR;
    
}

Status ListInsert(SLinkList L, int i, ElemType e){
    
    int cur = MAX_SIZE - 1;

    int count = 0;

    while(cur){
        ++count;

        if(count == i){
            int j = Malloc(L);
            L[j].data = e;
            L[j].cur = L[cur].cur;
            L[cur].cur = j;
            return OK;
        }

        cur = L[cur].cur;

    }

    return ERROR;
}


Status ListDelete(SLinkList L, int i, ElemType &e){
    int count = 0;

    int cur = MAX_SIZE - 1;

    while(cur){
        ++count;

        if(count == i && L[cur].cur){
            int deleteCur = L[cur].cur;
            L[cur].cur = L[deleteCur].cur;
            e = L[deleteCur].data;
            Free(L, deleteCur);
            return OK;
        }

        cur = L[cur].cur;
    }

    return ERROR;
}

void ListTraverse(SLinkList L, void(*visit)(ElemType)){
    int cur = L[MAX_SIZE - 1].cur;
    while(cur){
        visit(L[cur].data);
        cur = L[cur].cur;
    }
    printf("\n");
}

#endif

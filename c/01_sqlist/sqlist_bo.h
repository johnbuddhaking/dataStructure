void InitList(SqList &L){
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));

    if(!L.elem){
        exit(OVERFLOW);
    }
    
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
}

void DestroyList(SqList &L){
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
}

void ClearList(SqList &L){
    L.length = 0;
}

Status ListEmpty(SqList L){
    if(L.length == 0){
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int ListLength(SqList L){
    return L.length;
}

Status GetElem(SqList L, int i, ElemType &e){

    if (i < 1 || i > L.length){
        return ERROR;
    }

    e = *(L.elem + i - 1);
    return OK;
}

int LocateElem(SqList L, ElemType e, Status(* compare)(ElemType, ElemType)){
    int i = 1;
    ElemType *p = L.elem;

    while ( i <= L.length && !compare(*p++,e)){
        ++i;
    }

    if (i <= L.length){
        return i;
    } else {
        return 0;
    }

}

Status PriorElem(SqList L, ElemType cur_e, ElemType &pre_e){
    
    int i = 2;

    ElemType *p = (L.elem + i - 1);

    while (i <= L.length && *p != cur_e){
        ++p;
        ++i;
    }

    if (i > L.length){
        return ERROR;
    } else {
        pre_e = *--p;
        return OK;
    }
}

Status NextElem(SqList L, ElemType cur_e, ElemType &next_e){
    int i = 1;
    ElemType *p = L.elem;

    while (i < L.length && *p != cur_e){
        ++p;
        ++i;
    }

    if (i == L.length){
        return ERROR;
    } else {
        next_e = *++p;
        return OK;
    }
}

Status ListInsert(SqList &L, int i, ElemType e){
    ElemType* newbase, * q, * p;

    if(i < 1 || i > L.length + 1){
        return ERROR;
    }

    if(L.length == L.listsize){
        newbase = (ElemType*)realloc(L.elem, (L.listsize + LIST_INCREMENT) * sizeof(ElemType));

        if(!newbase){
            exit(OVERFLOW);
        }
 
        L.elem = newbase;
        L.listsize += LIST_INCREMENT;
    }

    q = L.elem + i - 1;

    p = L.elem + L.length;

    while(p != q){
        *p = *(p - 1);
        --p;
    }

    *q = e;
    L.length++;
    return OK;
}

Status ListDelete(SqList &L, int i, ElemType &e){
    
    if(i < 1 || i > L.length){
        return ERROR;
    }


    ElemType* beginPointer, * endPointer;
    beginPointer = L.elem + i - 1;
    endPointer = L.elem + L.length - 1;

    e = *beginPointer;
    ++beginPointer;

    while(beginPointer <= endPointer){
        *(beginPointer - 1) = *beginPointer;
        ++beginPointer;
    }

    L.length--;
    return OK;


}

void ListTraverse(SqList L, void(* visit)(ElemType&)){
    
    for(int index = 0; index < L.length; ++index){
        visit(*(L.elem + index));
    }

    printf("\n");
}

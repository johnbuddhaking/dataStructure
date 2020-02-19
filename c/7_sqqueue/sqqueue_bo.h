void InitQueue(SqQueue &Q){
    Q.base = (QElemType*)malloc(MAX_QSIZE*sizeof(QElemType));
    if(!Q.base){
        exit(OVERFLOW); }

    Q.front = Q.rear = 0;
}

void DestroyQueue(SqQueue &Q){
    if(Q.base){
        free(Q.base);
    }

    Q.front = Q.rear = 0;
}

void ClearQueue(SqQueue &Q){
    Q.front = Q.rear = 0;
}

Status QueueEmpty(SqQueue &Q){
    if(Q.front == Q.rear){
        return TRUE;
    }
    else {
        return FALSE;
    }
}

Status GetHead(SqQueue &Q, QElemType &e){
    if(QueueEmpty(Q)){
        return ERROR;
    }
    else {
        e = Q.base[Q.front];
        return OK;
    }
}

Status EnQueue(SqQueue &Q, QElemType e){
    if(Q.front == (Q.rear + 1) % MAX_QSIZE){
        return ERROR;
    }

    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAX_QSIZE;
    return OK;
}

int QueueLength(SqQueue &Q){
    return (Q.rear - Q.front + MAX_QSIZE) % MAX_QSIZE;
}

Status DeQueue(SqQueue &Q, QElemType &e){
    if(QueueEmpty(Q)){
        return ERROR;
    }

    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAX_QSIZE;
    return OK;
}

void QueueTraverse(SqQueue &Q, void(*visit)(QElemType)){
    int idx = Q.front;
    while( idx != Q.rear){
        visit(Q.base[idx]);
        idx = (idx + 1) % MAX_QSIZE;
    }
    printf("\n");
}

void InitQueue(LinkQueue &Q){
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q.front){
        exit(OVERFLOW);
    }
    Q.front->next = NULL;
}

void DestroyQueue(LinkQueue &Q){
    while(Q.front){
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
}

void ClearQueue(LinkQueue &Q){
    DestroyQueue(Q);
    InitQueue(Q);
}


Status QueueEmpty(LinkQueue &Q){
    if (Q.front->next){
        return FALSE;
    }
    else {
        return TRUE;
    }
}

int QueueLength(LinkQueue &Q){
    int l = 0;
    QueuePtr p = Q.front->next;
    while(p){
        ++l;
        p = p->next;
    }

    return l;
}

Status GetHead(LinkQueue &Q, QElemType &e){
    if(Q.front->next){
        e = Q.front->next->data;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void EnQueue(LinkQueue &Q, QElemType e){
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if(!p){
        exit(OVERFLOW);
    }

    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

Status DeQueue(LinkQueue &Q, QElemType &e){
    if(Q.front->next){
        QueuePtr p = Q.front->next;
        Q.front->next = p->next;
        e = p->data;

        if(Q.rear == p){
            Q.rear = Q.front;
        }
        free(p);
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void QueueTraverse(LinkQueue &Q, void(* visit)(QElemType)){
    QueuePtr p = Q.front->next;

    while(p){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}

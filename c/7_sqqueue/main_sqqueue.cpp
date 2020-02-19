#include "c1.h"
typedef int QElemType;
#include "sqqueue.h"
#include "sqqueue_bo.h"
#define ElemType QElemType
#include "func2_2.h"

int main(){
    SqQueue q;
    InitQueue(q);
    printf("after init, is the queue empty?%d,(1yes, 0no)\n", QueueEmpty(q));
    printf("input all queue elements, no more than %d:", MAX_QSIZE - 1);

    QElemType e;
    for(int i = 0; i < MAX_QSIZE - 1; ++i){
        scanf("%d", &e);
        EnQueue(q, e);
    }

    printf("queue length is:%d\n", QueueLength(q));
    printf("is the queue empty?%d,(1yes, 0no)\n", QueueEmpty(q));

    printf("after %d times dequeue and enqueue:\n", MAX_QSIZE);
    for(int i = 0; i < MAX_QSIZE; ++i){
        DeQueue(q, e);
        printf("deleted element is %d, input the enqueue element:", e);
        scanf("%d", &e);
        EnQueue(q, e);
    }

    printf("all elements in queue is:");
    QueueTraverse(q, print);

    GetHead(q, e);
    printf("header element is %d\n", e);

    ClearQueue(q);
    printf("after clear, is the queue empty?%d,(1yes, 0no)\n", QueueEmpty(q));

    DestroyQueue(q);

    return 0;
}

#include "c1.h"
typedef int QElemType;
#include "c3_2.h"
#include "bo3_2.h"
#define ElemType QElemType
#include "func2_2.h"

int main(){
    LinkQueue q;
    InitQueue(q);

    printf("success init an empty queue.\n");
    printf("is the queue empty?%d(1:yes 0:no),", QueueEmpty(q));
    printf("the queue length is:%d\n", QueueLength(q));

    EnQueue(q, -5);
    EnQueue(q, 5);
    EnQueue(q, 10);
    printf("after insert 3 elements, the queue length is %d\n", QueueLength(q));
    printf("is the queue empty?%d(1:yes 0:no),", QueueEmpty(q));
    printf("the elements in queue are:");
    QueueTraverse(q, print);

    QElemType d;
    int i = GetHead(q, d);
    if(i == OK){
        printf("the header element is %d,", d);
    }
    DeQueue(q, d);
    printf("delete header element %d,", d);

    i = GetHead(q, d);
    if(i == OK){
        printf("the new header element is %d\n", d);
    }

    ClearQueue(q);
    printf("queue clear, q.front= %u, q.rear= %u, q.front->next= %u\n", q.front, q.rear, q.front->next);
    DestroyQueue(q);
    printf("queue destroy, q.front= %u, q.rear= %u\n", q.front, q.rear);
    return 0;
}

#define ClearTree DestroyTree

void InitTree(CSTree &T) {
    T = NULL;
}

void DestroyTree(CSTree &T) {
    if (T) {
        DestroyTree(T->firstchild);
        DestroyTree(T->nextsibling);
        free(T);
        T = NULL;
    }
}

typedef CSTree QElemType;

#include "../06_linkqueue/linkqueue.h"
#include "../06_linkqueue/linkqueue_bo.h"

void CreateTree(CSTree &T) {
    char c[20]; // 临时存放孩子结点
    CSTree p, p1;

    LinkQueue q;
    InitQueue(q);

    printf("请输入根节点(字符型，#为空)：");
    scanf("%c%*c", &c[0]);

    if (c[0] != Nil) {
        T = (CSTree)malloc(sizof(CSNode));
        T->data = c[0];
        T->nextsibling = NULL;

        // 先入栈根结点，即第一棵树的根结点
        EnQueue(q, T);

        while (!QueueEmpty(q)) {
            DeQueue(q, p);
            printf("请按长幼顺序输入结点%c的所有孩子：", p->data);
            gets(c);
            m = strlen(c);

            // 如果有孩子，继续添加
            if (m > 0) {
                p1 = p->firstchild = (CSTree)malloc(sizeof(CSNode));
                p1->data=c[0];

                EnQueue(q, p1);

                for (int i = 1; i < m; ++i) {
                    p1->nextsibling = (CSTree)malloc(sizeof(CSNode));
                    p1 = p1->nextsibling;
                    p1->data = c[i];
                    EnQueue(q, p1);
                }
                p1->nextsibling = NULL;
            }
            else {  // 如果没孩子，置空
                p->firstchild = NULL;
            }
        }
        else {
            T = NULL;
        }
    }
}

Status TreeEmpty(CSTree T) {
    if (T) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

int TreeDepth(CSTree T) {
    CSTree p;
    int depth = 0;
    int max = 0;

    if (!T) {
        return 0;
    }

    for (p = T->firstchild; p; p = p->nextsibling) {
        depth = TreeDepth(p);
        if (depth > max) {
            max = depth;
        }
    }

    return max +1;
}

TElemType Value(CSTree p) {
    return p->data;
}
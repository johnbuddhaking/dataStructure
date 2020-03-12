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

TElemType Root(CSTree T) {
    if (T) {
        return Value(T);
    }
    else {
        return Nil;
    }
}

CSTree Point(CSTree T, TElemType s) {
    LinkQueue q;
    QElemType a;

    if (T) {
        InitQueue(q);
        EnQueue(q, T);

        while (!QueueEmpty(q)) {
            DeQueue(q, a);

            if (a->data == s) {
                return a;
            }

            if (a->firstchild) {
                EnQueue(q, a->firstchild);
            }

            if (a->nextsibling) {
                EnQueue(q, a->nextsibling);
            }
        }
    }

    return NULL;
}


Status Assign(CSTree &T, TElemType cur_e, TElemType value) {
    CSTree p;

    if (T) {
        p = Point(T, cur_e);
        if (p) {
            p->data = value;
            return OK;
        }
    }

    return ERROR;
}

TElemType Parent(CSTree T, TElemType cur_e) {
    LinkQueue q;
    InitQueue(q);

    if (T) {
        if (Value(T) == cur_e) {
            return Nil;
        }

        EnQueue(q, T);

        while (!QueueEmpty(q)) {
            CSTree p;
            DeQueue(q, p);

            if (p->firstchild) {
                t = p->firstchild;

                while (t) {
                    EnQueue(q, t);
                    if (Value(t) == cur_e) {
                        return Value(p);
                    }

                    t = t->nextsibling;
                }
            }
        }
    }

    return Nil;
}

TElemType LeftChild(CSTree T, TElemType cur_e) {
    CSTree f = Point(T, cur_e);

    if (f && f->firstchild) {
        return f->firstchild->data;
    }
    else {
        return Nil;
    }
}

TElemType RightSibling(CSTree T, TElemType cur_e) {
    CSTree f = Point(T, cur_e);

    if (f && f->nextsibling) {
        return f->nextsibling->data;
    }
    else {
        return Nil;
    }
}

TElemType InsertChild(CSTree &T, CSTree p, int i, CSTree c) {
    // 插入c为T中p结点的第i棵子树
    // p都知道了，要T干嘛
    if (T) {
        if (i == 1) {
            c->nextsibling = p->firstchild;
            p->firstchild = c;
        }
        else {
            CSTree q = p->firstchild;
            int j = 2;
            while (q && j < i) {
                q = q->nextsibling;
                ++j;
            }

            if (j == i) {
                c->nextsibling = q->nextsibling;
                q->nextsibling = c;
            }
            else {
                return ERROR;
            }
        }

        return OK;
    }
    else {
        return ERROR;
    }
}

Status DeleteChild(CSTree &T, CSTree p, int i) {
    if (T) {
        CSTree b, q;

        if (i == 1) {
            b = p->firstchild;
            p->firstchild = b->nextsibling;
            b->nextsibling = NULL;
            DestroyTree(b);
        }
        else {
            q = p->firstchild;
            int j = 2;

            while (q && j < i) {
                q = q->nextsibling;
                ++j;
            }

            if (j == i) {
                b = q->nextsibling;
                q->nextsibling = b->nextsibling;
                b->nextsibling = NULL;
                DestroyTree(b);
            }
            else {
                return ERROR;
            }
        }
    }
    else {
        return ERROR;
    }
}

void PostOrderTraverse(CSTree T, void(* visit)(TElemType)) {
    CSTree p;

    if (T) {
        p = T->firstchild;
        while (p) {
            PostOrderTraverse(p, visit); //先访问所有孩子
            p = p->nextsibling;
        }
        visit(Value(T)); //最后访问自己
    }
}

void LevelOrderTraverse(CSTree T, void(*visit)(TElemType)) {
    LinkQueue q;
    InitQueue(q);

    if (T) {
        EnQueue(q, T);
        while(!QueueEmpty(q)) {
            CSTree p;
            DeQueue(q, p);

            while (p) {
                visit(Value(p));

                if (p->firstchild) {
                    EnQueue(q, p->firstchild);
                }

                p = p->nextsibling
            }
        }
    }

    printf("\n");
}

void PreOrderTraverse(CSTree T, void(* visit)(TElemType)) {
    if (T) {
        visit(T->data);  // 先访问自己
        PreOrderTraverse(T->firstchild, visit);  // 再访问孩子
        PreOrderTraverse(T->nextsibling, visit); // 最后访问兄弟
    }
}

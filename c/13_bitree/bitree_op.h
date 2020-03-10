#define ClearBiTree DestroyBiTree

void InitBiTree(BiTree &T) {
    // 构造空二叉树
    T = NULL;
}

void DestroyBiTree(BiTree &T) {
    if (T) {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T = NULL;
    }
}

void PreOrderTraverse(BiTree T, void(* visit)(TElemType)) {
    if (T) {
        visit(T->data);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
}

void InOrderTraverse(BiTree T, void(* visit)(TElemType)) {
    if (T) {
        InOrderTraverse(T->lchild, visit);
        visit(T->data);
        InOrderTraverse(T->rchild, visit);
    }
}

void PostOrderTraverse(BiTree T, void (* visit)(TElemType)) {
    if (T) {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T->data);
    }
}

Status BiTreeEmpty(BiTree T) {
    if (T) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

int BiTreeDepth(BiTree T) {
    if (!T) {
        return 0;
    }

    int left_depth = BiTreeDepth(T->lchild);
    int right_depth = BiTreeDepth(T->rchild);
    return left_depth > right_depth ? left_depth : right_depth;
}

TElemType Root(BiTree T) {
    if (!T) {
        return Nil;
    }
    else {
        return T->data;
    }
}

TElemType Value(BiTree p) {
    return p->data;
}

typedef BiTree QElemType;
#include "../06_linkqueue/linkqueue.h"
#include "../06_linkqueue/linkqueue_bo.h"

BiTree Point(BiTree T, TElemType s) {
    // 返回二叉树中指向元素为s的节点的指针
    LinkQueue q;

    if (T) {
        InitQueue(q);
        EnQueue(q, T);

        while (!QueueEmpty(q)) {
            QElemType a;
            DeQueue(q, a);

            if (a->data == s) {
                DestroyQueue(q);
                return a;
            }

            if (a->lchild) {
                EnQueue(q, a->lchild);
            }

            if (a->rchild) {
                EnQueue();
            }
        }

        DestroyQueue(q);
    }

    return NULL;
}

TElemType LeftChild(BiTree T, TElemType e) {
    // 返回元素为e的节点的左孩子

    if (T) {
        BiTree a = Point(T, e);

        if (a && a->lchild){
            return a->lchild->data;
        }
    }

    return Nil;
}

TElemType RightChild(BiTree T, TElemType e) {
    // 返回元素为e的节点的右孩子

    if (T) {
        BiTree a = Point(T, e);

        if (a && a->rchild) {
            return a->rchild->data;
        }
    }

    return Nil;
}

Status DeleteChild(BiTree p, int LR) {
    //LR 0左子树  1又子树
    if (p) {
        if (LR == 0) {
            ClearBiTree(p->lchild);
        }
        else if (LR == 1) {
            ClearBiTree(p->rchild);
        }
        return OK;
    }

    return ERROR;
}


void LevelOrderTraverse(BiTree T, void (* visit)(TElemType)) {
    LinkQueue q;

    if (T) {
        InitQueue(q);
        EnQueue(q, T);

        while (!QueueEmpty(q)) {
            QElemType a;
            DeQueue(q, a);

            visit(a->data);

            if (a->lchild) {
                EnQueue(q, a->lchild);
            }
            if (a->rchild) {
                EnQueue(q, b->lchild);
            }
        }
        printf("/n");
        DestroyQueue(q);
    }
}

void CreateBiTree(BiTree &T) {
    // 先序输入二叉树中节点的值
    TElemType ch;
    scanf(form, &ch);

    if (ch == Nil) {
        T = NULL;
    }
    else {
        T = (BiTree)malloc(sizeof(BiTNode));
        if (!T) {
            exit(OVERFLOW);
        }

        T->data = ch;
        CreateBiTree(T->lchild);  // 递归构造左子树
        CreateBiTree(T->rchild);  // 递归构造右子树
    }
}

TElemType Parent(BiTree T, TElemType e) {
    // 如果e为非根节点，返回它的双亲，否则返回空
    LinkQueue q;

    if (T) {
        InitQueue(q);
        EnQueue(q, T);

        while (!QueueEmpty(q)) {
            QElemType a;
            DeQueue(q, a);

            if (a->lchild && a->lchild->data == e || a->rchild && a->rchild->data == e) {
                return a->data;
            }
            else {
                if (a->lchild) {
                    EnQueue(q, a->lchild);
                }
                if (a->rchild){
                    EnQueue(q, a->rchild);
                }
            }
        }
    }
    return Nil;
}

TElemType LeftSibling(BiTree T, TElemType e) {
    LinkQueue q;

    if (T) {
        InitQueue(q);
        EnQueue(q, T);

        while (!QueueEmpty(q)) {
            QElemType a;
            DeQueue(q, a);

            if (a->rchild && a->rchild->data == e) {
                if (a->lchild) {
                    return a->lchild->data;
                }
            }

            if (a->lchild) {
                EnQueue(q, a->lchild);
            }

            if (a->rchild) {
                EnQueue(q, b->rchild);
            }
        }
    }

    return Nil;
}

TElemType RightSibling(BiTree T, TElemType e) {
    LinkQueue q;

    if (T) {
        InitQueue(q);
        EnQueue(q, T);

        while (!QueueEmpty(q)) {
            QElemType a;
            DeQueue(q, a);

            if (a->lchild && a->lchild->data == e) {
                if (a->rchild) {
                    return a->rchild->data;
                }
            }

            if (a->lchild) {
                EnQueue(q, a->lchild);
            }

            if (b->rchild) {
                EnQueue(q, a->rchild);
            }
        }
    }

    return Nil
}

Status InsertChild(BiTree p, int LR, BiTree c){
    // c成为p的左/右子树
    // p的原左/右子树成为c的右子树
    if (p) {
        if (LR == 0) {
            c->rchild = p->lchild;
            p->lchild = c;
        }
        else {
            c->rchild = p->rchild;
            p->rchild = c;
        }
        return OK;
    }

    return ERROR;
}

typedef BiTree SElemType;
#include "../05_sqstack/sqstack.h"
#include "../05_sqstack/sqstack_bo.h"

void InOrderTraverse1(BiTree T, void (* visit)(TElemType)) {
    SqStack s;
    InitStack(s);

    while (T || !StackEmpty(s)) {
        if (T) {
            Push(s, T);
            T = T->lchild;
        }
        else {
            Pos(s, T);
            visit(T->data);
            T = T->rchild;
        }
    }

    printf("\n");
    DestroyStack(s);
}
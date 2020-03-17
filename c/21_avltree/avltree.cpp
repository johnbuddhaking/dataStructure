#include "c1.h"

typedef int KeyType;
struct ElemType {
    KeyType key;  // 关键字
    int others;  // 其他数据
};

void visit(ElemType c) {
    printf("(%d, %d) ", c.key, c.others);
}

void InputFromFile(FILE *f, ElemType &c) {
    fscanf(f, "%d%d", &c.key, &c.others);
}

void InputKey(KeyType &k) {
    scanf("%d", &k);
}

#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))
#define GT(a, b) ((a) > (b))

typedef ElemType TElemType;

typedef struct BSTNode {
    ElemType data;
    int bf;
    BSTNode *lchild;
    BSTNode *rchild;
}BSTNode, *BSTree;

typedef BSTree BiTree;

#define ClearBiTree DestroyBiTree

void InitBiTree(BSTree &T) {
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

// 查找值
BiTree SearchBST(BiTree T, KeyType key) {
    if (!T || EQ(key, T->data.key)) {
        return T;
    }
    else if (LT(key, T->data.key)){
        return SearchBST(T->lchild, key);
    }
    else {
        return SearchBST(T->rchild, key);
    }
}


// 右旋操作：
void R_Rotate(BSTree &p) {
    BSTree lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

// 左旋操作：
void L_Rotate(BSTree &p) {
    BSTree rc = p->rchild;
    p->rchild = rc->lchild;
    rc->lchild = p;
    p = rc;
}

// 左右旋操作
void LR_Rotate(BSTree &p) {
    BSTree lc = p->lchild;
    p->lchild = lc->rchild->rchild;
    lc->rchild->rchild = p;

    p = lc->rchild;
    lc->rchild = p->lchild;
    p->lchild = lc;
}

// 右左旋操作
void RL_Rotate(BSTree &p) {
    BSTree rc = p->rchild;
    p->rchild = rc->lchild->lchild;
    rc->lchild->lchild = p;

    p = rc->lchild;
    rc->lchild = p->rchild;
    p->rchild = rc;
}

#define LH +1  // 左高
#define EH 0   // 等高
#define RH -1  // 右高

void LeftBalance(BSTree &T) {
    // 原本平衡二叉排序树T的左子树比右子树高(T->bf = 1)
    // 又在左子树中插入了结点，并导致左子树更高

    BSTree lc = T->lchild;  // lc 指向*T的左孩子结点
    switch(lc->bf) {
        case LH:
            T->bf = lc->bf = EH;
            R_Rotate(T);
            break;
        case RH:
            BSTree rd = lc->rchild;
            switch(rd->bf) {
                case LH:
                    T->bf = RH;
                    lc->bf = EH;
                    break;
                case EH:
                    T->bf = lc->bf = EH;
                case RH:
                    T->bf = EH;
                    lc->bf = LH;
            }
            rd->bf = EH;

            // 没有定义FLAG，使用两个函数实现双旋处理
            #ifdef FLAG
            L_Rotate(T->lchild);
            R_Rotate(T);
            #else
            LR_Rotate(T);
            #endif
    }
}

void RightBalance(BSTree &T) {
    // 原本平衡二叉排序树T的右子树比左子树高(T->bf = -1)
    // 又在右子树中插入了结点，并导致右子树更高
    BSTree rc = T->rchild;
    switch(rc->bf) {
        case RH:
            T->bf = rc->bf = EH;
            L_Rotate(T);
            break;
        case LH:
            BSTree ld = rc->lchild;
            switch(ld->bf) {
                case RH:
                    T->bf = LH;
                    rc->bf = EH;
                    break;
                case EH:
                    T->bf = rc->bf = EH;
                    break;
                case LH:
                    T->bf = EH;
                    rc->bf = RH;
            }
            ld->bf = EH;

            // 没有定义FLAG，使用两个函数实现双旋处理
            #ifdef FLAG
            R_Rotate(T->rchild);
            L_Rotate(T);
            #else
            RL_Rotate(T);
            #endif
    }
}

Status InsertAVL(BSTree &T, ElemType e, int &taller) {
    // 若在平衡的二叉排序树T中不存在和e有相同关键字的结点
    // 则插入一个数据元素为e的新结点，并返回true
    // 否则返回false
    // 若因插入而使二叉排序树T失去平衡，则做平衡旋转处理
    // taller反映在调用InsertAVL()前后，T是否长高。


    // 如果树或子树T空，执行插入操作
    if (T == NULL) {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->data = e;
        T->lchild = T->rchild = NULL;
        T->bf = EH;
        taller = TRUE;
    }
    else {  // 树或子树T不空
        // 如果关键字存在，则返回
        if (EQ(e.key, T->data.key)) {
            taller = FALSE;
            return FALSE;
        }

        // 左插入
        if (LT(e.key, T->data.key)) {
            // 左插是否成功
            if (!InsertAVL(T->lchild, e, taller)) {
                return FALSE;
            }

            // 左插成功，并且树长高了
            if(taller) {
                switch(T->bf) {
                    case LH:
                        LeftBalance(T);
                        taller = FALSE;
                        break;
                    case EH:
                        T->bf = LH;
                        taller = TRUE;
                        break;
                    case RH:
                        T->bf = EH;
                        taller = FALSE;
                }
            }
        }
        // 右插入
        else {
            // 右插是否成功
            if(!InsertAVL(T->rchild, e, taller)) {
                return FALSE;
            }
            // 右插成功，并且树长高了
            if (taller) {
                switch (T->bf) {
                    case LH:
                        T->bf = EH;
                        taller = FALSE;
                        break;
                    case EH:
                        T->bf = RH;
                        taller = TRUE;
                        break;
                    case RH:
                        RightBalance(T);
                        taller = FALSE;
                }
            }
        }
    }

    return TRUE;
}

void D_LeftBalance(BSTree &p, int &lower) {
    BSTree ld;
    BSTree rc = p->rchild;

    switch(rc->bf) {
        case EH:
            rc->bf = LH;
            p->bf = RH;
            L_Rotate(p);
            lower = FALSE;
            break;
        case RH:
            p->bf = rc->bf = EH;
            L_Rotate(p);
            lower = TRUE;
            break;
        case LH:
            ld = rc->lchild;
            switch (ld->bf) {
                case EH:
                    p->bf = rc->bf = EH;
                    break;
                case LH:
                    p->bf = EH;
                    rc->bf = RH;
                    break;
                case RH:
                    p->bf = LH;
                    rc->bf = EH;
            }
            ld->bf = EH;

            #ifndef FLAG
            R_Rotate(p->rchild);
            L_Rotate(p);
            #else
            RL_Rotate(p);
            #endif

            lower = TRUE;
    }
}

void D_RightBalance(BSTree &p, int &lower) {
    BSTree rd;
    BSTree lc = p->lchild;

    switch (lc->bf) {
        case EH:
            lc->bf = RH;
            p->bf = LH;
            R_Rotate(p);
            lower = FALSE;
            break;
        case LH:
            p->bf = lc->bf = EH;
            R_Rotate(p);
            lower = TRUE;
            break;
        case RH:
            rd = lc->rchild;
            switch(rd->bf) {
                case EH:
                    p->bf = lc->bf = EH;
                    break;
                case RH:
                    p->bf = EH;
                    lc->bf = LH;
                    break;
                case LH:
                    p->bf = RH;
                    lc->bf = EH;
            }
            rd->bf = EH;

            #ifndef FLAG
            L_Rotate(p->lchild);
            R_Rotate(p);
            #else
            LR_ROtate(p);
            #endif

            lower = TRUE;


    }
}

Status DeleteAVL(BSTree &p, ElemType &e, int &lower) {
    // 若AVL树p中存在和e有相同关键字的结点，则删除结点，返回true
    // e返回删除的结点
    // 否则返回false
    // 若因删除而使AVL树p失去平衡，则做平衡旋转处理
    // lower 反映在调用DeleteAVL()前后，p是否降低

    BSTree rc;
    BSTree lc;
    ElemType e1;

    // 空树
    if (p == NULL) {
        return FALSE;
    }
    // 树非空
    else {
        // 找到关键字
        if (EQ(e.key, p->data.key)) {
            e = p->data;
            rc = p;

            // p所指结点的度为2，找前驱或后继结点代替删除
            if (p->lchild != NULL && p->rchild != NULL) {
                // 右子树更高，找后继代替删除
                if (p->bf == RH) {
                    lc = p->rchild;
                    while (lc->lchild != NULL) {
                        lc = lc->lchild;
                    }
                }
                // 左子树更高或等高，找前驱结点代替删除
                else {
                    lc = p->lchild;
                    while (lc->rchild != NULL) {
                        lc = lc->rchild;
                    }
                }

                e1 = lc->data;
                DeleteAVL(p, e1, lower);
                rc->data = e1;
            }
            else {
                if (p->rchild == NULL) {
                    p = p->lchild;
                }
                else {
                    p = p->rchild;
                }
                free(rc);
                lower = TRUE;
            }
        }
        else if (LT(e.key, p->data.key)) {
            if (!DeleteAVL(p->lchild, e, lower)){
                return FALSE;
            }

            if (lower) {
                switch (p->bf) {
                    case EH:
                        p->bf = RH;
                        lower = FALSE;
                        break;
                    case LH:
                        p->bf = EH;
                        lower = TRUE;
                        break;
                    case RH:
                        D_LeftBalance(p, lower);
                }
            }
        }
        else {
            if (!DeleteAVL(p->rchild, e, lower)) {
                return FALSE;
            }

            if (lower) {
                switch (p->bf) {
                    case EH:
                        p->bf = LH;
                        lower = FALSE;
                        break;
                    case RH:
                        p->bf=EH;
                        lower = TRUE;
                        break;
                    case LH:
                        D_RightBalance(p, lower);
                }
            }
        }
        return TRUE;
    }
}


#define FLAG

int main() {

    FILE *f = fopen("data.txt", "r");
    int n = 0;
    fscanf(f, "%d", &n);  // 由数据文件输入数据元素个数

    BSTree dt;
    InitBiTree(dt);

    int flag;
    for (int i = 0; i < n; ++i) {
        ElemType r;
        InputFromFile(f, r);

        Status k = InsertAVL(dt, r, flag);

        if (k) {
            printf("insert key %d, in-order traverse avl tree dt\n", r.key);
            InOrderTraverse(dt, visit);
            printf("\npre-order traverse avl tree dt\n");
            PreOrderTraverse(dt, visit);
            printf("\n");
        }
        else {
            printf("avl tree dt contains key %d, so (%d, %d) can not be inserted in dt.\n", r.key, r.key, r.others);
        }
    }

    fclose(f);

    printf("input the key to search:");
    KeyType j;
    InputKey(j);
    BSTree p = SearchBST(dt, j);

    if (p) {
        printf("dt contains key %d, the value is (%d, %d).\n", j, p->data.key, p->data.others);
    }
    else {
        printf("dt does not contains key %d.\n", j);
    }

    printf("input key which will be deleted:");
    ElemType r;
    InputKey(r.key);

    Status k = DeleteAVL(dt, r, flag);

    if (k) {
        printf("delete node (%d, %d), in-order traverse avl tree dt:\n", r.key, r.others);
        InOrderTraverse(dt, visit);
        printf("\npre-order traverse avl tree dt\n");
        PreOrderTraverse(dt, visit);
        printf("\n");
    }
    else {
        printf("avl tree dt does not contains key %d.\n", r.key);
    }

    DestroyBiTree(dt);
    return 0;
}
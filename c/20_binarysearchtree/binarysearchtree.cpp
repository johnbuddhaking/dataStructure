#include "c1.h"

typedef int KeyType;
struct ElemType {
    KeyType key;
    int others;
};

typedef ElemType TElemType;
#include "../13_bitree/bitree.h"


#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))
#define GT(a, b) ((a) > (b))

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

#define InitDSTable InitBiTree
#define DestroyDSTable DestroyBiTree
#define TraverseDSTable InOrderTraverse

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

// 以下均为对二叉查找树的操作
Status SearchBST(BiTree &T, KeyType key, BiTree f, BiTree &p) {
    // 指针f指向T的双亲，初始值为NULL
    // 如果查找成功，则用p指向该数据元素结点
    // 否则，p指向查找路径上访问的最后一个结点
    if (!T) {
        p = f;
        return FALSE;
    }
    else if (EQ(key, T->data.key)) {
        p = T;
        return TRUE;
    }
    else if (LT(key, T->data.key)) {
        return SearchBST(T->lchild, key, T, p);
    }
    else {
        return SearchBST(T->rchild, key, T, p);
    }
}

Status InsertBST(BiTree &T, ElemType e) {
    BiTree p;
    if (!SearchBST(T, e.key, NULL, p)) {
        BiTree s = (BiTree)malloc(sizeof(BiTNode));
        s->data = e;
        s->lchild = s->rchild = NULL;

        if (!p) {
            T = s;
        }
        else if (LT(e.key, p->data.key)) {
            p->lchild = s;
        }
        else {
            p->rchild = s;
        }
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void Delete(BiTree &p) {
    BiTree q = p;

    if (!p->rchild) {  // 如果右孩子为空，则左孩子顶上；待删除结点为叶子结点也走此分支
        p = p->lchild;
        free(q);
    }
    else if (!p->lchild) {  // 如果左孩子为空，则右孩子顶上
        p = p->rchild;
        free(q);
    }
    else {  // 左右子树均不空，把右孩子放到左子树的最右，删除结点
        BiTree s = p->lchild;

        // q 指向左孩子的最右结点
        while (s) {
            q = s;
            s = s->rchild;
        }

        // q 的右孩子 等于 待删除结点的右孩子
        q->rchild = p->rchild;
        // 用q 记录待删除结点
        q = p;
        //
        p = p->lchild;
        free(q);
    }
}

Status DeleteBST(BiTree &T, KeyType key) {
    if (!T) {
        return FALSE;
    }
    else {
        if (EQ(key, T->data.key)) {
            Delete(T);
            return TRUE;
        }
        else if (LT(key, T->data.key)) {
            return DeleteBST(T->lchild, key);
        }
        else {
            return DeleteBST(T->rchild, key);
        }
    }
}

void visit(ElemType c) {
    printf("(%d,%d)", c.key, c.others);
}

void InputFromFile(FILE *f, ElemType &c) {
    fscanf(f, "%d%d", &c.key, &c.others);
}

void InputKey(KeyType &k) {
    scanf("%d", &k);
}

int main() {
    FILE *f = fopen("data.txt", "r");

    int n;
    fscanf(f, "%d", &n);

    BiTree dt;
    InitDSTable(dt);

    for (int i = 0; i < n; ++i) {
        ElemType r;
        InputFromFile(f, r);
        Status k = InsertBST(dt, r);

        if (!k) {
            printf("binary search tree dt has already have the key %d, so (%d,%d) can not be inserted in dt.\n", r.key, r.key, r.others);
        }
    }

    fclose(f);

    printf("\ninorder traverse binary tree dt:\n");
    TraverseDSTable(dt, visit);

    printf("\npreorder traverse binary tree dt:\n");
    PreOrderTraverse(dt, visit);

    printf("\ninput the key which want to be searched:");
    KeyType j;
    InputKey(j);

    BiTree p = SearchBST(dt, j);

    if (p) {
        printf("dt has key %d.", j);
        DeleteBST(dt, j);
        printf("delete that key, inorder traverse the binary search tree dt:\n");
        TraverseDSTable(dt, visit);

        printf("\npreorder traverse binary tree dt:\n");
        PreOrderTraverse(dt, visit);

        printf("\n");
    }
    else {
        printf("\ndt does not contain key %d.\n", j);
    }

    DestroyDSTable(dt);
    return 0;
}
#include "c1.h"

typedef struct BSTNode {
    ElemType data;
    int bf;
    BSTNode *lchild;
    BSTNode *rchild;
}BSTNode, *BSTree;

void R_Rotate(BSTree &p) {
    BSTree lc = p->lchild;
    p->lchild = lc->rchild;
    lc->rchild = p;
    p = lc;
}

int main() {

    return 0;
}
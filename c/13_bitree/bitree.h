#ifndef _BITREE_H
#define _BITREE_H

typedef struct BiTNode{
    TElemType data;
    BiTNode *lchild;
    BiTNode *rchild;
}BiTNode, *BiTree;

#endif
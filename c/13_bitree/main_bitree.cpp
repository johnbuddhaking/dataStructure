#define CHAR 1  // 字符型
//#define CHAR 0
#include "c1.h"
#if CHAR
    typedef char TElemType;
    TElemType Nil = '#';
    #define form "%c"
#else
    typedef int TElemType;
    TElemType Nil = 0;
    #define form "%d"
#endif

void visit(TElemType e) {
    printf(form" ", e);
}

#include "bitree.h"
#include "bitree_op.h"

int main() {
    BiTree T;
    InitBiTree(T);
    printf("构造空二叉树后，树空否?%d(1:是，0:否)。树的深度=%d。\n", BiTreeEmpty(T), BiTreeDepth(T));

    TElemType e1 = Root(T);
    if (e1 != Nil) {
        printf("二叉树的根为"form".\n", e1);
    }
    else {
        printf("树空，无根。\n");
    }

    return 0;
}
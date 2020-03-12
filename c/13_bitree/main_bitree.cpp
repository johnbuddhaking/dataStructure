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

    #if CHAR
        printf("请按先序输入二叉树(如:ab###表示a为根节点，b为左子树的二叉树):\n)");
    #else
        printf("请按先序输入二叉树(如:1 2 0 0 0表示1为根节点，2为左子树的二叉树):\n)");
    #endif

    CreateBiTree(T);
    printf("建立空二叉树后，树空否?%d(1:是，0:否)。树的深度=%d。\n", BiTreeEmpty(T), BiTreeDepth(T));

    e1 = Root(T);
    if (e1 != Nil) {
        printf("二叉树的根为"form".\n", e1);
    }
    else {
        printf("树空，无根。\n");
    }

    printf("\n中序遍历二叉树：\n");
    InOrderTraverse(T, visit);

    printf("\n后序遍历二叉树：\n");
    PostOrderTraverse(T, visit);

    printf("\n请输入一个节点的值：");
    scanf("%*c"form, &e1);

    BiTree p = Point(T, e1);
    printf("结点的值为"form"。\n", Value(p));

    printf("欲改变此结点的值，请输入新值：");
    TElemType e2;
    scanf("%*c"form"%*c", &e2);
    Assign(p, e2);

    printf("层序遍历二叉树：\n");
    LevelOrderTraverse(T, visit);

    e1 = Parent(T, e2);
    if (e1 != Nil) {
        printf(form"的双亲是"form",", e2, e1);
    }
    else {
        printf(form"没有双亲,", e2);
    }

    e1 = LeftChild(T, e2);
    if (e1 != Nil) {
        printf("左孩子是"form",", e1);
    }
    else {
        printf("没有左孩子,");
    }

    e1 = RightChild(T, e2);
    if (e1 != Nil) {
        printf("右孩子是"form",", e1);
    }
    else {
        printf("没有右孩子,");
    }

    e1 = LeftSibling(T, e2);
    if (e1 != Nil) {
        printf("左兄弟是"form",", e1);
    }
    else {
        printf("没有左兄弟,");
    }

    e1 = RightSibling(T, e2);
    if (e1 != Nil) {
        printf("右兄弟是"form",", e1);
    }
    else {
        printf("没有右兄弟,");
    }

    BiTree c;
    InitBiTree(c);
    printf("\n请构造一个右子树为空的二叉树c:\n");
    #if CHAR
        printf("请按先序输入二叉树(如:ab###表示a为根节点，b为左子树的二叉树):\n)");
    #else
        printf("请按先序输入二叉树(如:1 2 0 0 0表示1为根节点，2为左子树的二叉树):\n)");
    #endif
    CreateBiTree(c);

    int i;

    printf("\n中序遍历二叉树c:\n");
    InOrderTraverse(c, visit);
    printf("\n树c插到树T中，请输入树T中树c的双亲结点c为左(0)或右(1)子树：");
    scanf("%*c"form"%d", &e1, &i);
    p = Point(T, e1);
    InsertChild(p, i, c);

    printf("\n先序遍历二叉树：\n");
    PreOrderTraverse(T, visit);

    printf("\n删除子树，请输入待删除子树的双亲结点 左(0)右(1)");
    scanf("%*c"form"%d", &e1, &i);

    p = Point(T, e1);
    DeleteChild(p, i);

    printf("\n先序递归遍历二叉树：\n");
    PreOrderTraverse(T, visit);

    printf("\n中序非递归遍历二叉树：\n");
    InOrderTraverse1(T, visit);

    printf("\n中序非递归遍历二叉树(另一种方法)：\n");
    InOrderTraverse2(T, visit);

    DestroyBiTree(T);

    return 0;
}
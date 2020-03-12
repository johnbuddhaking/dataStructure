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

#include "cstree.h"
#include "cstree_bo.h"


int main() {
    CSTree T;
    InitTree(T);
    printf("构造空树后，树空否?%d(1:是，0:否)。树根为%c, 树的深度=%d。\n", TreeEmpty(T), Root(T),TreeDepth(T));

    CreateTree(T);
    printf("构造树T后，树空否?%d(1:是，0:否)。树根为%c, 树的深度=%d。\n", TreeEmpty(T), Root(T),TreeDepth(T));

    printf("层序遍历树T：\n");
    LevelOrderTraverse(T, visit);

    printf("\n请输入待修改的结点的值 新值：");
    TElemType e;
    TElemType e1;
    scanf("%c%*c%c%*c", &e, &e1);

    Assign(T, e, e1);

    printf("层序遍历修改后的树T：\n");
    LevelOrderTraverse(T, visit);

    printf("%c的双亲是%c,长子是%c,下一个兄弟是%c. \n", e1, Parent(T, e1), LeftChild(T, e1), RightSibling(T, e1));

    printf("建立树p:\n");
    CSTree p;
    InitTree(p);
    CreateTree(p);
    printf("层序遍历树p：\n");
    LevelOrderTraverse(p, visit);

    int i;
    printf("\n树p插到树T中，请输入树T中树p的双亲结点 子树序号：");
    scanf("%c%d%*c", &e, &i);
    CSTree q = Point(T, e);
    InsertChild(T, q, i, p);

    printf("层序遍历修改后的树T：\n");
    LevelOrderTraverse(T, visit);

    printf("\n先根历树T：\n");
    PreOrderTraverse(T, visit);

    printf("\n后根历树T：\n");
    PostOrderTraverse(T, visit);

    printf("\n删除树T中结点e的第i棵子树，请输入e i:");
    scanf("%c%d", &e, &i);
    q = Point(T, e);
    DeleteChild(T, q, i);

    printf("层序遍历修改后的树T：\n");
    LevelOrderTraverse(T, visit);

    DestroyTree(T);

    return 0;
}
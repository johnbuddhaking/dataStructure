#include "c1.h"

typedef char KeyType;

struct ElemType {
    KeyType key;
    int weight;
};

void visit(ElemType c) {
    printf("(%c, %d)", c.key, c.weight);
}

void InputFromFile(FILE *f, ElemType &c) {
    fscanf(f, "%*c%c%d", &c.key, &c.weight); // %*c 吃掉回车符
}

void InputKey(KeyType &k) {
    scanf("%c", &k);
}


#include "sstable.h"
#include "sstable_bo.h"
typedef ElemType TElemType;
TElemType Nil;
#include "../13_bitree/bitree.h"
#define N 100

Status SecondOptimal(BiTree &T, ElemType R[], int sw[], int low, int high) {
    // 由有序表 R[low - high] 及其累积权值表 sw (其中sw[0] == 0)
    // 递归构造次优查找树T

    // 寻找概率上最平衡的点下标
    int i = low;
    double dw = sw[high] + sw[low - 1];
    double min = fabs(sw[high] - sw[low]);
    for (int j = low + 1; j <= high; ++j) {
        if (fabs(dw - sw[j] - sw[j - 1]) < min) {
            i = j;
            min = fabs(dw - sw[j] - sw[j - 1]);
        }
    }

    // 分配根结点
    if (!(T = (BiTree)malloc(sizeof(BiTNode)))){
        return ERROR;
    }

    // 赋值
    T->data = R[i];

    // 递归建立左子树
    if (i == low) {
        T->lchild = NULL;
    }
    else {
        SecondOptimal(T->lchild, R, sw, low, i - 1);
    }

    // 递归建立右子树
    if (i == high) {
        T->rchild == NULL;
    }
    else {
        SecondOptimal(T->rchild, R, sw, i + 1, high);
    }

    return OK;
}

void FindSW(int sw[], SSTable ST) {
    sw[0];
    printf("\nsw = 0");

    for (int i = 1; i <= ST.length; ++i) {
        sw[i] = sw[i - 1] + ST.elem[i].weight;
        printf("%5d", sw[i]);
    }
}

// 次优查找树采用二叉链表的存储结构
typedef BiTree SOSTree;

// 根据SSTable 创建一棵 SOSTree
void CreateSOSTree(SOSTree &T, SSTable ST) {
    int sw[N + 1];

    if (ST.length == 0) {
       T = NULL;
    }
    else {
        FindSW(sw, ST);
        SecondOptimal(T, ST.elem, sw, 1, ST.length);
    }
}

Status Search_SOSTree(SOSTree &T, KeyType key) {
    while (T) {
        if (T->data.key == key) {
            return OK;
        }
        else if (T->data.key > key) {
            T = T->lchild;
        }
        else {
            T = T->rchild;
        }
    }
}

int main() {
    SSTable st;
    SOSTree t;

    Create_OrdFromFile(st, "order_sostree.txt");
    printf("         ");
    Traverse(st, visit);
    CreateSOSTree(t, st);

    printf("\n请输入待查找的字符：");
    KeyType s;
    InputKey(s);

    SOSTree p = t;
    int i = Search_SOSTree(p, s);
    if (i) {
        printf("%c的权值是%d\n", s, p->data.weight);
    }
    else {
        printf("表中不存在此字符\n");
    }

    Destroy(st);
    return 0;
}

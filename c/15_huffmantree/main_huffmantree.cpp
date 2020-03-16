#include "c1.h"

// 哈夫曼树
typedef struct {
    unsigned int weight;
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
}HTNode, * HuffmanTree;

// 哈夫曼编码表
typedef char **HuffmanCode;

#define Order

int min(HuffmanTree t, int i) {
    // 返回哈夫曼树t的前i个结点中，权值最小的树的根结点序号
    unsigned int k = UINT_MAX;
    int m = 0;

    for (int j = 1; j <= i; ++j) {
        if (t[j].weight < k && t[j].parent == 0) {
            k = t[j].weight;
            m = j;
        }
    }

    t[m].parent = 1;  // 给选中的根结点的双亲赋非零值，避免第二次查找该结点
    return m;
}

void select(HuffmanTree t, int i, int &s1, int &s2){
    // 在哈夫曼树t的前i个结点中选择两个权值最小的树的根结点序号
    // s1为其中权值较小的序号
    s1 = min(t, i);
    s2 = min(t, i);

    #ifdef Order
        if (s1 > s2) {
            int j = s1;
            s1 = s2;
            s2 = j;
        }
    #endif
}

void HuffmanCoding_bottom_up(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
    // w存放n个字符的权值（均>0）
    // 构造Huffman树HT，并求出n个字符的Huffman编码HC

    // 叶子结点数不大于1
    if (n <= 1) {
        return;
    }

    // n个叶子结点的Huffman树共有 2 * n - 1 个结点
    int m = 2 * n -1;

    // 0号单元未使用
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));

    HuffmanTree p = HT;
    // 从1号单元开始到n号单元，给叶子结点赋值
    for (int i = 1; i <= n; ++i) {
        (*(p + i)).weight = *(w + i - 1);
        (*(p + i)).parent = 0;
        (*(p + i)).lchild = 0;
        (*(p + i)).rchild = 0;
    }

    // 其余结点双亲域初值为0
    for (int i = n + 1; i <= m; ++i) {
        (*(p + i)).parent = 0;
    }

    // 建Huffman树
    for (int i = n + 1; i <= m; ++i) {
        int s1 = 0;
        int s2 = 0;
        select(HT, i - 1, s1, s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    // 分配n个字符编码的头指针向量（[0]不用）
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));

    // 分配求编码的工作空间
    char *cd = (char *)malloc(n * sizeof(char));
    cd[n - 1] = '\0';  // 编码结束符

    // 逐个字符求Huffman编码
    for (int i = 1; i <= n; ++i) {
        int start = n - 1;  // 编码结束符位置

        // 从叶子到根逆向求编码
        unsigned c = i;
        unsigned f = HT[i].parent;
        while (f != 0) {
            if (HT[f].lchild == c) {
                cd[--start] = '0';
            }
            else {
                cd[--start] = '1';
            }
            c = f;
            f = HT[f].parent;
        }

        HC[i] = (char *)malloc((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
}

void HuffmanCoding_up_bottom(HuffmanTree &HT, HuffmanCode &HC, int *w, int n){
    // w存放n个字符的权值（均>0）
    // 构造Huffman树HT，并求出n个字符的Huffman编码HC

    // 叶子结点数不大于1
    if (n <= 1) {
        return;
    }

    // n个叶子结点的Huffman树共有 2 * n - 1 个结点
    int m = 2 * n -1;

    // 0号单元未使用
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));

    HuffmanTree p = HT;
    // 从1号单元开始到n号单元，给叶子结点赋值
    for (int i = 1; i <= n; ++i) {
        (*(p + i)).weight = *(w + i - 1);
        (*(p + i)).parent = 0;
        (*(p + i)).lchild = 0;
        (*(p + i)).rchild = 0;
    }

    // 其余结点双亲域初值为0
    for (int i = n + 1; i <= m; ++i) {
        (*(p + i)).parent = 0;
    }

    // 建Huffman树
    for (int i = n + 1; i <= m; ++i) {
        int s1 = 0;
        int s2 = 0;
        select(HT, i - 1, s1, s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    // 无栈非递归遍历Huffman树，求Huffman编码
    // 分配n个字符编码的头指针向量（[0]不用）
    HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));

    // 分配求编码的工作空间
    char *cd = (char *)malloc(n * sizeof(char));
    unsigned c = m;  // 从最后一个根结点开始
    unsigned cdlen = 0; // 码长的初值为0

    // 求编码不再需要权值域，改作结点状态标志，0表示左右孩子都不曾被访问
    for (int i = 1; i <= m; ++i) {
        HT[i].weight = 0;
    }

    // 未到叶子结点的孩子域
    while (c) {
        if (HT[c].weight == 0) {  // 左右孩子不曾被访问
            HT[c].weight = 1; // 左访问，右未访问
            if (HT[c].lchild != 0) {
                c = HT[c].lchild;
                cd[cdlen++] = '0';
            }
            else if (HT[c].rchild == 0) {
                HC[c] = (char *)malloc((cdlen + 1)*sizeof(char));
                cd[cdlen] = '\0';
                strcpy(HC[c], cd);
            }
        }
        else if (HT[c].weight == 1) {
            HT[c].weight = 2;
            if (HT[c].rchild != 0) {
                c = HT[c].rchild;
                cd[cdlen++] = '1';
            }
        }
        else {
            c = HT[c].parent;
            --cdlen;
        }
    }

    free(cd);
}


int main() {
    HuffmanTree HT;
    HuffmanCode HC;

    int n = 0;
    printf("请输入权值的个数(>1)：");
    scanf("%d", &n);

    // 动态生成存放n个权值的空间
    int *w = (int *)malloc(n * sizeof(int));
    printf("请依次输入%d个权值（整型）：\n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", w + i);
    }

//    HuffmanCoding_bottom_up(HT, HC, w, n);
    HuffmanCoding_up_bottom(HT, HC, w, n);

    for (int i = 1; i <= n; ++i) {
        puts(HC[i]);  // 依次输出Huffman编码，此方法系统自动在末尾添加换行符
    }
    return 0;
}
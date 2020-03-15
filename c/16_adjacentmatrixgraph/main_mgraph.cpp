#include "c1.h"
#include "mgraph.h"
#include "mgraph_bo.h"

typedef MGraph Graph;

int main() {
    char s[4] = "边";
    Graph g;
    VertexType v1, v2;
    printf("请依次选择有向图，有向网，无向图，无向网：\n");

    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0:
                g.kind =  DG;
                break;
            case 1:
                g.kind = DN;
                break;
            case 2:
                g.kind = UDG;
                break;
            case 3:
                g.kind = UDN;
        }
        CreateGraph(g);
        Display(g);
        printf("插入新顶点，请输入新顶点的值：");
        Input(v1);
        InsertVex(g, v1);

        if (g.kind < 2) {
            strcpy(s, "弧");
        }

        printf("插入与新顶点有关的%s，请输入%s数");
        int n = 0;
        scanf("%d", &n);

        for (int k = 0; k < n; ++k) {
            printf("请输入另一顶点的名称：");
            scanf("%s", v2.name);

            if (g.kind <= 1) {  // 有向
                printf("请输入另一顶点的方向（弧头0  弧尾1）：");
                int j;
                scanf("%d", &j);
                if (j) {
                    InsertArc(g, v2, v1);
                }
                else {
                    InsertArc(g, v1, v2);
                }
            }
            else {  // 无向
                InsertArc(g, v1, v2);
            }
        }

        Display(g);
        printf("删除顶点及相关的%s，请输入待删除顶点的名称：", s);
        scanf("%s", v1.name);
        DeleteVex(g, v1);
        Display(g);

        // 对于最后的无向网，测试一下函数
        if (i == 3) {
            printf("修改顶点的值，请输入待修改顶点名称  新值：");
            scanf("%s", v1.name);
            Input(v2);
            PutVex(g, v1, v2);  // 将图中v1顶点的值，修改为v2

            if (g.kind < 2) {
                printf("删除一条%s，请输入待删除%s的弧尾  弧头：", s, s);
            }
            else {
                printf("删除一条%s，请输入待删除%s的顶点1  顶点2：", s, s);
            }

            scanf("%s%s", v1.name, v2.name);
            DeleteArc(g, v1, v2);
        }

        DestroyGraph(g);
    }

    return 0;
}
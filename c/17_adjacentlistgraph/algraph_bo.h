#ifndef _ALGRAPH_BO_H
#define _ALGRAPH_BO_H

#include "../02_linklist/linklist_bo_nohead.h"  // 不设头结点的单链表基本操作

LinkList Point(LinkList L, ElemType e, Status(* equal)(ElemType, ElemType))  {
    LinkList p = L;

    while (p) {
        if (equal(p->data, e)) {
            return p;
        }

        p = p->next;
    }

    return NULL;
}

int LocateVex(ALGraph G, VertexType u) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (strcmp(u.name, G.vertices[i].data.name) == 0) {
            return i;
        }
    }

    return -1;
}

void CreateGraph(ALGraph &G) {

    char s[3] = "边";
    printf("请输入图的类型（有向图0 有向网1 无向图2 无向网3）：");
    scanf("%d", &G.kind);

    if (G.kind < 2) {
        strcpy(s, "弧");
    }

    printf("请输入图的顶点数，边数：");
    scanf("%d,%d", &G.vexnum, &G.arcnum);
    printf("请输入%d个顶点的值（名称<%d个字符）：\n", G.vexnum, MAX_NAME);

    for (int i = 0; i < G.vexnum; ++i) {
        Input(G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }

    printf("请输入%d条%s的", G.arcnum, s);
    switch (G.kind) {
        case DG:
            printf("弧尾 弧头：\n");
            break;
        case DN:
            printf("弧尾 弧头 弧信息：\n");
            break;
        case UDG:
            printf("顶点1 顶点2：\n");
            break;
        case UDN:
            printf("顶点1 顶点2 边信息：\n");
    }

    // 构造弧相关的链表
    for (int k = 0; k < G.arcnum; ++k) {
        VertexType v1;
        VertexType v2;
        scanf("%s%s", v1.name, v2.name);

        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);

        ElemType e;
        e.info = NULL;

        if (G.kind % 2) { // 如果是网，则输入权重
            InputArc(e.info);
        }

        e.adjvex = j;
        ListInsert(G.vertices[i].firstarc, 1, e);

        // 如果是无向图/网，则对称插入弧信息
        if (G.kind >= 2) {
            e.adjvex = i;
            ListInsert(G.vertices[j].firstarc, 1, e);
        }
    }
}

void CreateFromFile(ALGraph &G, char *filename) {
    FILE *f = fopen(filename, "r");
    fscanf(f, "%d", &G.kind);
    fscanf(f, "%d", &G.vexnum);

    for (int i = 0; i < G.vexnum; ++i) {
        InputFromFile(f, G.vertices[i].data);
        G.vertices[i].firstarc = NULL;
    }

    fscanf(f, "%d", &G.arcnum);
    for (int k = 0; k < G.arcnum; ++k) {
        VertexType v1;
        VertexType v2;
        fscanf(f, "%s%s", v1.name, v2.name);
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);

        ElemType e;
        e.info = NULL;

        if (G.kind % 2) {
            InputArcFromFile(f, e.info);
        }

        e.adjvex = j;
        ListInsert(G.vertices[i].firstarc, 1, e);

        if (G.kind >= 2) {
            e.adjvex = i;
            ListInsert(G.vertices[j].firstarc, 1, e);
        }
    }

    fclose(f);
}

VertexType GetVex(ALGraph G, int v) {
    if (v >= G.vexnum || v < 0) {
        exit(OVERFLOW);
    }

    return G.vertices[v].data;
}

Status PutVex(ALGraph &G, VertexType v, VertexType value) {
    int k = LocateVex(G, v);

    if (k != -1) {
        G.vertices[k].data = value;
        return OK;
    }
    return ERROR;
}

int FirstAdjVex(ALGraph G, int v) {
    ArcNode *p = G.vertices[v].firstarc;
    if (p) {
        return p->data.adjvex;
    }
    else {
        return -1;
    }
}

Status equalvex(ElemType a, ElemType b) {
    if (a.adjvex == b.adjvex) {
        return OK;
    }
    else {
        return ERROR;
    }
}

int NextAdjVex(ALGraph G, int v, int w) {
    // v->w 之后的邻接顶点序号
    ElemType e;
    e.adjvex = w;
    LinkList p = Point(G.vertices[v].firstarc, e, equalvex);

    if (!p || !p->next) {
        return -1;
    }
    else {
        return p->next->data.adjvex;
    }
}

void InsertVex(ALGraph &G, VertexType v) {
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    ++G.vexnum;
}

Status InsertArc(ALGraph &G, VertexType v, VertexType w) {
    char s1[3] = "边";
    char s2[3] = "--";

    if (G.kind < 2) {
        strcpy(s1, "弧");
        strcpy(s2, "->");
    }

    int i = LocateVex(G, v);
    int j = LocateVex(G, w);

    if (i < 0 || j < 0) {
        return ERROR;
    }

    ++G.arcnum;

    ElemType e;
    e.adjvex = j;
    e.info = NULL;

    if (G.kind % 2) {
        printf("请输入%s%s%s%s的信息：", s1, v.name, s2, w.name);
        InputArc(e.info);
    }

    ListInsert(G.vertices[i].firstarc, 1, e);

    if (G.kind >= 2) {
        e.adjvex = i;
        ListInsert(G.vertices[j].firstarc, 1, e);
    }

    return OK;
}

Status DeleteArc(ALGraph &G, VertexType v, VertexType w) {
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);

    if (i < 0 || j < 0 || i == j) {
        return ERROR;
    }

    ElemType e;
    e.adjvex = j;

    int n = LocateElem(G.vertices[i].firstarc, e, equalvex);

    if (n) {
        ListDelete(G.vertices[i].firstarc, n, e);
        --G.arcnum;

        if (G.kind%2) {
            free(e.info);
        }

        if (G.kind >= 2) {
            e.adjvex = i;
            n = LocateElem(G.vertices[j].firstarc, e, equalvex);
            ListDelete(G.vertices[j].firstarc, n, e);
        }
        return OK;
    }
    else {
        return ERROR;
    }
}

Status DeleteVex(ALGraph &G, VertexType v) {

    int k = LocateVex(G, v);
    if (k < 0) {
        return ERROR;
    }

    // 删除由顶点v发出的弧
    for (int i = 0; i < G.vexnum; ++i) {
        DeleteArc(G, v, G.vertices[i].data);
    }

    // 删除发向顶点v的弧
    if (G.kind < 2) {
        for (int i = 0; i < G.vexnum; ++i) {
            DeleteArc(G, G.vertices[i].data, v);
        }
    }

    // 更改结点顺序
    for (int i = k + 1; i < G.vexnum; ++i) {
        G.vertices[i - 1] = G.vertices[i];
    }

    for (int i = 0; i < G.vexnum; ++i) {
        LinkList p = G.vertices[i].firstarc;

        while (p) {
            if (p->data.adjvex > k) {
                --p->data.adjvex;
            }

            p = p->next;
        }
    }

    --G.vexnum;
    return OK;
}

void DestroyGraph(ALGraph &G) {
    for (int i = G.vexnum - 1; i >= 0; --i) {
        DeleteVex(G, G.vertices[i].data);
    }
}

void Display(ALGraph G) {
    char s1[3] = "边";
    char s2[3] = "--";

    if (G.kind < 2) {
        strcpy(s1, "弧");
        strcpy(s2, "->");
    }

    switch(G.kind) {
        case DG:
            printf("有向图\n");
            break;
        case DN:
            printf("有向网\n");
            break;
        case UDG:
            printf("无向图\n");
            break;
        case UDN:
            printf("无向网\n");
    }

    printf("%d个顶点，依次是：", G.vexnum);
    for (int i = 0; i < G.vexnum; ++i) {
        visit(GetVex(G, i));
    }

    printf("\n%d条%s:\n", G.arcnum, s1);

    for (int i = 0; i < G.vexnum; ++i) {
        ArcNode *p = G.vertices[i].firstarc;

        while (p) {
            // 有向，或无向两次中的一次
            if (G.kind <= 1 || i < p->data.adjvex) {
                printf("%s%s%s ", G.vertices[i].data.name, s2, G.vertices[p->data.adjvex].data.name);

                if (G.kind % 2) {
                    //网
                    OutputArc(p->data.info);
                }
            }
            p = p->nextarc;
        }
        printf("\n");
    }

//    printf("结束display\n");
}

#endif
#ifndef _ALGRAPH_H
#define _ALGRAPH_H

// 顶点相关类型及对应操作
#define MAX_NAME 9  // 顶点名称字符串最大长度 + 1
struct VertexType {
    char name[MAX_NAME];
};

void visit(VertexType ver) {
    printf("%s ", ver.name);
}

void Input(VertexType &ver) {
    scanf("%s", ver.name);
}

void InputFromFile(FILE *f, VertexType &ver) {
    fscanf(f, "%s", ver.name);
}

// 弧的相关信息类型定义及对应操作
typedef int VRType;  // 定义权值类型为整型
struct InfoType {  // 最简单的弧相关信息类型-只有权值
    VRType weight;
};

void InputArc(InfoType *&arc) {
    arc = (InfoType *)malloc(sizeof(InfoType));
    scanf("%d", &arc->weight);
}

void OutputArc(InfoType *arc) {
    printf(":%d ", arc->weight);
}

void InputArcFromFile(FILE *f, InfoType *&arc) {
    arc = (InfoType *)malloc(sizeof(InfoType));
    fscanf(f, "%d", &arc->weight);
}

// 定义图的邻接表存储结构
#define MAX_VERTEX_NUM  20// 最大顶点数
enum GraphKind{DG, DN, UDG, UDN};  // {有向图，有向网，无向图，无向网}

struct ElemType {
    int adjvex;
    InfoType *info;
};

bool operator==(ElemType &t1,ElemType &t2)
{
   return t1.adjvex==t2.adjvex;
}

struct ArcNode {
    ElemType data;
    ArcNode *nextarc;
};

typedef struct {
    VertexType data;
    ArcNode *firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

struct ALGraph {
    AdjList vertices;
    int vexnum;
    int arcnum;
    GraphKind kind;
};

#define LNode ArcNode
#define next nextarc
#define LinkList ArcNode *

#endif
#ifndef _MGRAPH_H
#define _MGRAPH_H

#define INFINITY INT_MAX  // 用整型最大值代替 无穷
typedef int VRType;  // 定义顶点关系类型为整型，与INFINITY的类型一致
#define MAX_VERTEX_NUM 26  // 最大顶点个数
enum GraphKind{DG, DN, UDG, UDN};  // 0有向图、1有向网、2无向图、3无向网 -- 图：边无权；网：边有权

// 顶点类型
#define MAX_NAME 9
struct VertexType {
    char name[MAX_NAME];
};

// 弧信息结构
#define MAX_INFO 20
typedef char InfoType;
typedef struct {
    VRType adj;  // 顶点关系的值，无权图为0/1；带权图为权值
    InfoType *info;  // 该弧相关信息的指针，可无
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 图的结构
struct MGraph {
    VertexType vexs[MAX_VERTEX_NUM];  // 顶点向量
    AdjMatrix arcs;  // 邻接矩阵 -- 二维数组
    int vexnum, arcnum;  // 点数、边数
    GraphKind kind;  // 图的种类
};

#endif
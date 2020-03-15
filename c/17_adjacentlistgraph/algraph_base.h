#define MAX_VERTEX_NUM 20
enum GraphKind{DG, DN, UDG, UDN};

// 表结点，存弧的信息
struct ArcNode {
    int adjvex; // 该弧所指向顶点的位置序号
    InfoType *info;  // 该弧相关信息，包括网的权值指针
    ArcNode *nextarc;  // 指向下一条弧的指针

};


// 头结点，存顶点的信息
typedef struct {
    VertexType data;  // 顶点信息
    ArcNode *firstarc;  // 第一个表结点的地址，指向第一条依附该结点的弧的指针
}VNode, AdjList[MAX_VERTEX_NUM];

// 邻接表结构
struct ALGraph {
    AdjList vertices;
    int vexnum;
    int arcnum;
    GraphKind kind;
};
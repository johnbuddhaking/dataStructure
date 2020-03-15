#include <iostream>

// 访问顶点
void Visit(VertexType ver) {
    printf("%s", ver.name);
}

// 输入顶点信息
void Input(VertexType &ver) {
    scanf("%s", ver.name);
}

// 从文件中输入顶点信息
void InputFromFile(FILE *f, VertexType &ver) {
    fscanf(f, "%s", ver.name);
}

// 输入弧
void InputArc(InfoType * &arc) {
    char s[MAX_INFO];
    printf("请输入该弧的相关信息(<%d个字符)：", MAX_INFO);
    std::cin.getline(s, MAX_INFO);
    int m = strlen(s);
    if (m) {
        arc = (char *)malloc((m + 1) * sizeof(char));
        strcpy(arc, s);
    }
}

void InputArcFromFile(FILE *f, InfoType * &arc) {
    char s[MAX_INFO];
    fgets(s, MAX_INFO, f);
    arc = (char *)malloc((strlen(s) + 1) * sizeof(char));
    strcpy(arc, s);
}

void OutputArc(InfoType *arc) {
    printf("%s\n", arc);
}

// 如果G中包含顶点u，则返回位置序号
int LocateVex(MGraph G, VertexType u) {
    for (int i = 0; i < G.vexnum; ++i) {
        if (strcmp(u.name, G.vexs[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

// 构造有向图G
void CreateDG(MGraph &G) {
    printf("请输入有向图G的顶点数，弧数，弧是否含相关信息(是:1 否:0)");
    int IncInfo; // 为0则不含相关信息
    scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);

    // 输入顶点信息
    printf("请输入%d个顶点的值(名称<%d个字符)：\n", G.vexnum, MAX_NAME);
    for (int i = 0; i < G.vexnum; ++i) {
        Input(G.vexs[i]);
    }

    // 初始化二维邻接矩阵(弧信息)
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            G.arcs[i][j].adj = 0;
            G.arcs[i][j].info = NULL;
        }
    }

    // 输入弧信息
    VertexType v1;
    VertexType v2;
    printf("请输入%d条弧的弧尾 弧头：\n", G.arcnum);
    for (int i = 0; i < G.arcnum; ++i) {
        scanf("%s%s%*c", v1.name, v2.name); // %*c吃掉回车符
        int t = LocateVex(G, v1);
        int h = LocateVex(G, v2);
        G.arcs[t][h].adj = 1;  // 有向图
        if(IncInfo) {
            InputArc(G.arcs[t][h].info);
        }
    }
    G.kind = DG;
}

// 构造有向网
void CreateDN(MGraph &G) {
        printf("请输入有向网G的顶点数，弧数，弧是否含相关信息(是:1 否:0)");
        int IncInfo; // 为0则不含相关信息
        scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);

        // 输入顶点信息
        printf("请输入%d个顶点的值(名称<%d个字符)：\n", G.vexnum, MAX_NAME);
        for (int i = 0; i < G.vexnum; ++i) {
            Input(G.vexs[i]);
        }

        // 初始化二维邻接矩阵(弧信息)
        for (int i = 0; i < G.vexnum; ++i) {
            for (int j = 0; j < G.vexnum; ++j) {
                G.arcs[i][j].adj = INFINITY;
                G.arcs[i][j].info = NULL;
            }
        }

        // 输入弧信息
        VertexType v1;
        VertexType v2;
        VRType w;
        printf("请输入%d条弧的弧尾 弧头 权值：\n", G.arcnum);
        for (int i = 0; i < G.arcnum; ++i) {
            scanf("%s%s%d%*c", v1.name, v2.name, &w);  // %*c吃掉回车符
            int t = LocateVex(G, v1);
            int h = LocateVex(G, v2);
            G.arcs[t][h].adj = w;  // 有向网
            if(IncInfo) {
                InputArc(G.arcs[t][h].info);
            }
        }
        G.kind = DN;
}

// 构造无向图G
void CreateUDG(MGraph &G) {
    printf("请输入无向图G的顶点数，弧数，弧是否含相关信息(是:1 否:0)");
    int IncInfo; // 为0则不含相关信息
    scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);

    // 输入顶点信息
    printf("请输入%d个顶点的值(名称<%d个字符)：\n", G.vexnum, MAX_NAME);
    for (int i = 0; i < G.vexnum; ++i) {
        Input(G.vexs[i]);
    }

    // 初始化二维邻接矩阵(弧信息)
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            G.arcs[i][j].adj = 0;
            G.arcs[i][j].info = NULL;
        }
    }

    // 输入边信息
    VertexType v1;
    VertexType v2;
    printf("请输入%d条边的顶点1 顶点2：\n", G.arcnum);
    for (int i = 0; i < G.arcnum; ++i) {
        scanf("%s%s%*c", v1.name, v2.name); // %*c吃掉回车符
        int t = LocateVex(G, v1);
        int h = LocateVex(G, v2);
        G.arcs[t][h].adj = 1;  // 有向图
        if(IncInfo) {
            InputArc(G.arcs[t][h].info);
        }

        G.arcs[h][t] = G.arcs[t][h];  // 无向，两个单元信息相同
    }
    G.kind = UDG;
}

// 构造无向网
void CreateUDN(MGraph &G) {
        printf("请输入无向网G的顶点数，弧数，弧是否含相关信息(是:1 否:0)");
        int IncInfo; // 为0则不含相关信息
        scanf("%d,%d,%d", &G.vexnum, &G.arcnum, &IncInfo);

        // 输入顶点信息
        printf("请输入%d个顶点的值(名称<%d个字符)：\n", G.vexnum, MAX_NAME);
        for (int i = 0; i < G.vexnum; ++i) {
            Input(G.vexs[i]);
        }

        // 初始化二维邻接矩阵(弧信息)
        for (int i = 0; i < G.vexnum; ++i) {
            for (int j = 0; j < G.vexnum; ++j) {
                G.arcs[i][j].adj = INFINITY;
                G.arcs[i][j].info = NULL;
            }
        }

        // 输入边信息
        VertexType v1;
        VertexType v2;
        VRType w;
        printf("请输入%d条边的顶点1 顶点2 权值：\n", G.arcnum);
        for (int i = 0; i < G.arcnum; ++i) {
            scanf("%s%s%d%*c", v1.name, v2.name, &w);  // %*c吃掉回车符
            int t = LocateVex(G, v1);
            int h = LocateVex(G, v2);
            G.arcs[t][h].adj = w;  // 网
            if(IncInfo) {
                InputArc(G.arcs[t][h].info);
            }
            G.arcs[h][t] = G.arcs[t][h];
        }
        G.kind = UDN;
}

void CreateGraph(MGraph &G) {
    printf("请输入图G的类型（有向图0 有向网1 无向图2 无向网3）");
    scanf("%d", &G.kind);
    switch(G.kind) {
        case DG:
            CreateDG(G);
            break;
        case DN:
            CreateDN(G);
            break;
        case UDG:
            CreateUDG(G);
            break;
        case UDN:
            CreateUDN(G);
    }
}

// 根据序号返回顶点名称
VertexType GetVex(MGraph G, int v) {
    if (v >= G.vexnum || v < 0) {
        exit(OVERFLOW);
    }
    return G.vexs[v];
}

// 替换顶点名称
Status PutVex(MGraph &G, VertexType v, VertexType value) {
    int k = LocateVex(G, v);
    if (k < 0) {
        return ERROR;
    }
    G.vexs[k] = value;
    return OK;
}

// 返回第v个顶点的第一个邻接点下标
int FirstAdjVex(MGraph G, int v) {
    VRType j = 0;
    if (G.kind % 2) {
        j = INFINITY;  // 网
    }

    // 从第一个邻接点查找
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.arcs[v][j].adj != j) {
            return i;
        }
    }

    return -1;
}

// 返回第v个顶点，w(不含)开始的下一个邻接点下标
int NextAdjVex(MGraph G, int v, int w) {
    VRType j = 0;
    if (G.kind % 2) {  // 网
        j = INFINITY;
    }

    for (int i = w + 1; i < G.vexnum; ++i) {
        if (G.arcs[v][i].adj != j) {
            return i;
        }
    }

    return -1;
}

// 插入顶点
void InsertVex(MGraph &G, VertexType v) {
    VRType j = 0;
    if (G.kind % 2) {
        j = INFINITY;
    }
    G.vexs[G.vexnum] = v;

    // 对新插入顶点对应邻接矩阵的行列初始化
    for (int i = 0; i <= G.vexnum; ++i) {
        G.arcs[G.vexnum][i].adj = G.arcs[i][G.vexnum].adj = j;
        G.arcs[G.vexnum][i].info = G.arcs[i][G.vexnum].info = NULL;
    }
    ++G.vexnum;
}

// 插入边
Status InsertArc(MGraph &G, VertexType v, VertexType w) {
    int v1 = LocateVex(G, v);
    int w1 = LocateVex(G, w);

    if (v1 < 0 || w1 < 0) {
        return ERROR;
    }

    ++G.arcnum;
    if (G.kind % 2) {  // 网
        printf("请输入此弧的权值：");
        scanf("%d", &G.arcs[v1][w1].adj);
    }
    else {
        G.arcs[v1][w1].adj = 1;  // 图
    }

    printf("是否有该弧相关的信息（0无 1有）:");
    int i;
    scanf("%d%*c", &i);
    if (i) {
        InputArc(G.arcs[v1][w1].info);
    }

    if (G.kind > 1) {  // 无向
        G.arcs[w1][v1] = G.arcs[v1][w1];
    }

    return OK;
}

// 删除边
Status DeleteArc(MGraph &G, VertexType v, VertexType w) {
    VRType j = 0;
    if (G.kind % 2) {
        j = INFINITY;
    }

    int v1 = LocateVex(G, v);
    int w1 = LocateVex(G, w);

    if (v1 < 0 || w1 < 0) {
        return ERROR;
    }

    if (G.arcs[v1][w1].adj != j) {
        G.arcs[v1][w1].adj = j;

        if (G.arcs[v1][w1].info) {
            free(G.arcs[v1][w1].info);
            G.arcs[v1][w1].info = NULL;
        }

        if (G.kind > 1) {
            G.arcs[w1][v1] = G.arcs[v1][w1];
        }

        --G.arcnum;
    }
    return OK;
}

// 删除顶点
Status DeleteVex(MGraph &G, VertexType v) {
    int k = LocateVex(G, v);
    if (k < 0) {
        return ERROR;
    }

    // 删除由该顶点出发的所有弧
    for (int i = 0; i < G.vexnum; ++i) {
        DeleteArc(G, v, G.vexs[i]);
    }

    // 有向，删除发向顶点v的所有弧
    if (G.kind < 2) {
        for (int i = 0; i < G.vexnum; ++i) {
            DeleteArc(G, G.vexs[i], v);
        }
    }

    // 序号k后面的顶点依次前移
    for (int j = k + 1; j < G.vexnum; ++j) {
        G.vexs[j - 1] = G.vexs[j];
    }

    // 移动删除点之右的矩阵元素
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = k + 1; j < G.vexnum; ++j) {
            G.arcs[i][j - 1] = G.arcs[i][j];
        }
    }

    // 移动删除点之下的矩阵元素
    for (int i = k + 1; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            G.arcs[i - 1][j] = G.arcs[i][j];
        }
    }

    --G.vexnum;
    return OK;
}

void DestroyGraph(MGraph &G) {
    for (int i = G.vexnum - 1; i >= 0; --i) {
        DeleteVex(G, G.vexs[i]);
    }
}

void Display(MGraph G) {
    char s[12] = "无向网";
    char s1[4] = "边";

    switch (G.kind) {
        case DG:
            strcpy(s, "有向图");
            strcpy(s1, "弧");
            break;
        case DN:
            strcpy(s, "有向网");
            strcpy(s1, "弧");
            break;
        case UDG:
            strcpy(s, "无向图");
        case UDN:
            ;
    }

    // 先打印顶点
    printf("%d个顶点 %d条 %s的 %s，顶点依次是：", G.vexnum, G.arcnum, s1, s);
    for (int i = 0; i < G.vexnum; ++i) {
        Visit(GetVex(G, i));
    }

    // 再打印邻接矩阵
    printf("\nG.arcs.adj:\n");
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            if (G.arcs[i][j].adj == INFINITY) {
                printf(" ∞");
            }
            else {
                printf("%4d", G.arcs[i][j].adj);
            }
        }
        printf("\n");
    }

    // 最后打印邻接矩阵里，边的info
    printf("G.arcs.info\n");
    if (G.kind < 2) {
        printf("弧尾 弧头 该%s的信息：\n", s1);
    }
    else {
        printf("顶点1 顶点2 该%s的信息：\n", s1);
    }

    for (int i = 0; i < G.vexnum; ++i) {
        if (G.kind < 2) {  // 有向
            for (int j = 0; j < G.vexnum; ++j) {
                if (G.arcs[i][j].info){
                    printf("%5s%5s\t", G.vexs[i].name, G.vexs[j].name);
                    OutputArc(G.arcs[i][j].info);
                }
            }
        }
        else {  // 无向
            for (int j = i + 1; j < G.vexnum; ++j) {
                if (G.arcs[i][j].info){
                    printf("%5s%5s\t", G.vexs[i].name, G.vexs[j].name);
                    OutputArc(G.arcs[i][j].info);
                }
            }
        }
    }
}

void CreateFromFile(MGraph &G, char *filename, int IncInfo) {
    FILE *f = fopen(filename, "r");

    fscanf(f, "%d", &G.kind); // 由文件输入G的类型

    VRType w = 0;  // 顶点关系类型 图
    if (G.kind % 2) { // 网
        w = INFINITY;
    }

    fscanf(f, "%d", &G.vexnum);  // 由文件输入G的顶点数
    for (int i = 0; i < G.vexnum; ++i) {
        InputFromFile(f, G.vexs[i]);  // 由文件输入顶点信息
    }

    fscanf(f, "%d", &G.arcnum);  // 由文件输入G的弧数
    // 初始化二维邻接矩阵
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            G.arcs[i][j].adj = w;
            G.arcs[i][j].info = NULL;
        }
    }

    // 图
    if (G.kind % 2 == 0) {
        w = 1;
    }

    for (int k = 0; k < G.arcnum; ++k) {
        VertexType v1;
        VertexType v2;

        fscanf(f, "%s%s", v1.name, v2.name);

        if (G.kind % 2) {  // 网，再输入权值
            fscanf(f, "%d", &w);
        }

        int t = LocateVex(G, v1);
        int h = LocateVex(G, v2);
        G.arcs[t][h].adj = w;

        // 有边的相关信息
        if (IncInfo) {
            InputArcFromFile(f, G.arcs[t][h].info);
        }

        if (G.kind > 1) {
            G.arcs[h][t] = G.arcs[t][h];
        }
    }

    fclose(f);
}


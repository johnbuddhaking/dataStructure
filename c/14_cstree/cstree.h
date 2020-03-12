typedef struct CSNode {
    TElemType data;
    CSNode *firstchild;
    CSNode *nextsibling;
}CSNode, *CSTree;
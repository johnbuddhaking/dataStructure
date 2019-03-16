#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 2

struct SqList{
    ElemType *elem;
    int length;
    int listsize;
};

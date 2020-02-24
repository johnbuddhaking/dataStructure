#ifndef _SQLIST_H
#define _SQLIST_H

#define LIST_INIT_SIZE 10
#define LIST_INCREMENT 2

struct SqList{
    ElemType *elem;
    int length;
    int listsize;
};

#endif

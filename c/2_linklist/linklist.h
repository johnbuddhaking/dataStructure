/*************************************************************************
	> File Name: linklist.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月16日 星期六 14时51分46秒
 ************************************************************************/

#ifndef _LINKLIST_H
#define _LINKLIST_H

struct LNode{
    ElemType data;
    LNode *next;
};

typedef LNode *LinkList;
#endif

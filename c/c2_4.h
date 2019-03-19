/*************************************************************************
	> File Name: c2_4.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月19日 星期二 21时16分40秒
 ************************************************************************/

#ifndef _C2_4_H
#define _C2_4_H

typedef struct DuLNode{
    ElemType data;
    DuLNode *prior, *next;
}DuLNode, *DuLinkList;

#endif

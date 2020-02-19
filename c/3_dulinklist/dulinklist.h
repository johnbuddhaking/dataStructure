/*************************************************************************
	> File Name: dulinklist.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月19日 星期二 21时16分40秒
 ************************************************************************/

#ifndef _DULINKLIST_H
#define _DULINKLIST_H

typedef struct DuLNode{
    ElemType data;
    DuLNode *prior, *next;
}DuLNode, *DuLinkList;

#endif

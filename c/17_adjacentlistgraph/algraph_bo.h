#ifndef _ALGRAPH_BO_H
#define _ALGRAPH_BO_H

#include "../02_linklist/linklist_bo_nohead.h"  // 不设头结点的单链表基本操作

LinkList Point(LinkList L, ElemType e, Status(* equal)(ElemType, ElemType))  {
    LinkList p = L;

    while (p) {
        if (equal(p->data, e)) {
            return p;
        }

        p = p->next;
    }

    return NULL;
}

#endif
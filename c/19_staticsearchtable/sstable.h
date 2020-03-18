#ifndef _SSTABLE_H
#define _SSTABLE_H

struct SSTable {
    ElemType *elem;
    int length;
};

#endif
#ifndef _ORDER_STRUCT_H
#define _ORDER_STRUCT_H

typedef int KeyType;

struct ElemType {
    KeyType key;
};

void visit (ElemType c) {
    printf("%d ", c.key);
}

void InputFromFile (FILE *f, ElemType &c) {
    fscanf(f, "%d", &c.key);
}

void InputKey(KeyType &k) {
    scanf("%d", &k);
}

#endif
#ifndef _SCORE_STRUCT_H
#define _SCORE_STRUCT_H

typedef long KeyType;
#define key number

struct ElemType {
    long number;
    char name[9];
    int politics;
    int Chinese;
    int English;
    int math;
    int physics;
    int chemistry;
    int biology;
    int total;
};

void visit(ElemType c) {
    printf("%-8ld%-8s%5d%5d%5d%5d%5d%5d%5d%5d\n", c.number, c.name, c.politics, c.Chinese, c.English, c.math,
    c.physics, c.chemistry, c.biology, c.total);
}

void InputFromFile(FILE *f, ElemType &c) {
    fscanf(f, "%ld%s%d%d%d%d%d%d%d", &c.number, &c.name, &c.politics, &c.Chinese, &c.English, &c.math,
    &c.physics, &c.chemistry, &c.biology);
}

void InputKey(KeyType &k) {
    scanf("%ld", &k);
}

#endif
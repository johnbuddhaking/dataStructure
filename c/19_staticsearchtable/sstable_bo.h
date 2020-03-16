#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))
#define GT(a, b) ((a) > (b))

void Create_SeqFromFile(SSTable &ST, char *filename) {
    FILE *f = fopen(filename, "r");
    fscanf(f, "%d", &ST.length);

    ST.elem = (ElemType *)calloc(ST.length + 1, sizeof(ElemType));

    if (!ST.elem) {
        exit(OVERFLOW);
    }

    for (int i = 1; i <= ST.length; ++i) {
        InputFromFile(f, ST.elem[i]);
    }

    fclose(f);
}

void Ascend(SSTable &ST) {
    // 选择升序排序
    for (int i = 1; i < ST.length; ++i) {
        int k = i;  // k存当前关键字最小值的序号
        ST.elem[0] = ST.elem[i];  // 待比较值存[0]单元

        for (int j = i + 1; j <= ST.length; ++j) {
            if (LT(ST.elem[j].key, ST.elem[0].key)) {
                k = j;
                ST.elem[0] = ST.elem[j];
            }
        }
        if (k != i) {
            ST.elem[k] = ST.elem[i];
            ST.elem[i] = ST.elem[0];
        }
    }
}

void CreateOrdFromFile(SSTable &ST, char *filename) {
    Create_SeqFromFile(ST, filename);
    Ascend(ST);
}

Status Destroy(SSTable &ST) {
    free(ST.elem);
    ST.elem = NULL;
    ST.length = 0;
    return OK;
}

int Search_Seq(SSTable ST, KeyType key) {
    // 从后向前顺序查找
    ST.elem[0].key = key;
    int i = ST.length;

    while (!EQ(ST.elem[i].key, key)) {
        --i;
    }

    return i;
}

int Search_Bin(SSTable ST, KeyType key) {
    // 折半查找

    int low = 1;
    int high = ST.length;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (EQ(key, ST.elem[mid].key)) {
            return mid;
        }
        else if LT(key, ST.elem[mid].key) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return 0;
}

void Traverse(SSTable ST, void(*visit)(ElemType)) {
    ElemType *p = ST.elem;

    for (int i = 1; i <= ST.length; ++i) {
        visit(*(p + i));
    }
}
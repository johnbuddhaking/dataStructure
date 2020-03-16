#include "c1.h"
#include "order_struct.h"
#include "sstable.h"
#include "sstable_bo.h"

int main() {

    SSTable st;
    Create_OrdFromFile(st, "order.txt");

    printf("有序表为：");
    Traverse(st, visit);
    printf("\n");
    printf("请输入待查找数据的关键字：");

    KeyType s;
    InputKey(s);

    int i = Search_Bin(st, s);
    if (i) {
        printf("%d是第%d个数据的关键字\n", st.elem[i].key, i);
    }
    else {
        printf("未找到\n");
    }

    Destroy(st);
    return 0;
}


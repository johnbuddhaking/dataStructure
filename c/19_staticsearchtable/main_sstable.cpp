#include "c1.h"
#include "score_struct.h"
#include "sstable.h"
#include "sstable_bo.h"

int main() {
    char filename[13];
    printf("请输入数据文件名：");
    scanf("%s", filename);

    SSTable st;
    Create_SeqFromFile(st, filename);

    // 依次计算每项数据元素的总分
    for (int i = 0; i <= st.length; ++i) {
        st.elem[i].total = st.elem[i].politics + st.elem[i].Chinese + st.elem[i].English + st.elem[i].math +
        st.elem[i].physics + st.elem[i].chemistry + st.elem[i].biology;
    }

    printf("准考证号  姓名 政治 语文 外语 数学 物理 化学 生物 总分\n");
    Traverse(st, visit);
    printf("请输入待查找人的考号：");
    long s;
    InputKey(s);
    int i = Search_Seq(st, s);

    if (i) {
        visit(st.elem[i]);
    }
    else {
        printf("未找到\n");
    }

    Destroy(st);
    return 0;
}


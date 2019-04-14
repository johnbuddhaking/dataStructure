/*************************************************************************
	> File Name: main3_1.cpp  
	> Author: 
	> Mail: 
	> Created Time: 2019年04月14日 星期日 20时36分38秒
 ************************************************************************/


#include "c1.h"
typedef int SElemType;
#include "c3_1.h"
#include "bo3_1.h"
#define ElemType SElemType
#include "func2_2.h"

int main(){
    SqStack s;
    
    InitStack(s);

    for(int j = 1; j <= 12; ++j){
        Push(s, j);
    }
    printf("栈中元素依次为");
    StackTraverse(s, print);

    SElemType e;
    Pop(s, e);
    printf("弹出的栈顶元素e = %d\n", e);
    printf("栈空否？%d(1:空  0:否),", StackEmpty(s));
    GetTop(s, e);
    printf("栈顶元素e = %d, 栈的长度为%d\n", e, StackLength(s));

    ClearStack(s);
    printf("清空栈后，栈空否？%d(1:空  0:否)\n", StackEmpty(s));

    DestoryStack(s);
    printf("销毁栈后， s.top = %u, s.base = %u, s.stacksize = %d\n", s.top, s.base, s.stacksize);

    return 0;
}


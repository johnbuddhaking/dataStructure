/*************************************************************************
	> File Name: algo3_3.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年04月14日 星期日 21时22分54秒
 ************************************************************************/

#include<iostream>
using namespace std;

typedef char SElemType;
#include "c1.h"
#include "c3_1.h"
#include "bo3_1.h"
#define ElemType SElemType
#include "func2_2.h"


void LineEdit(){
    SqStack s;
    char ch;
    InitStack(s);
    printf("请输入一个文本文件，^Z结束输入：\n");
    ch = getchar();

    while(ch != EOF){
        while(ch != EOF && ch != '\n'){
            switch(ch){
                case '#':
                    if(!StackEmpty(s)){
                        Pop(s, ch);
                    }
                     break;
                case '@':
                    ClearStack(s);
                    break;
                default:
                    Push(s, ch);
            }

            ch = getchar();
        }

        StackTraverse(s, print2);

        ClearStack(s);

        if(ch != EOF){
            ch = getchar();
        }
    }

    DestoryStack(s);
}

int main(){

     LineEdit();
}

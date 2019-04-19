/*************************************************************************
	> File Name: algo3_1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年04月14日 星期日 21时10分45秒
 ************************************************************************/

#include<iostream>
using namespace std;

#define N 16
typedef int SElemType;
#include "c1.h"
#include "c3_1.h"
#include "bo3_1.h"

void conversion(){
    SqStack s;
    unsigned n;
    SElemType e;
    InitStack(s);
    printf("将十进制整数n转换为%d进制整数，请输入：n(>=0) = ", N);
    scanf("%u", &n);
    
    while(n){
        Push(s, n % N);
        n = n / N;
    }

    while(!StackEmpty(s)){
        Pop(s, e);

        if(e < 10){
            printf("%d", e);
        }
        else{
            printf("%c", e + 55);
        }
    }
    printf("\n");
}

int main(){
    conversion();
    return 0;
}

// File Name: algo_var_arguments.cpp
// Author: 
// Created Time: 2020年02月24日 星期一 21时41分30秒

#include "c1.h"
typedef int ElemType;

ElemType Max(int num, ...) {
    // 返回num个数字中，最大的
    va_list ap; // va_list 是c语言数据类型--变长参数表类型，在stdarg.h中

    if (num < 1) {
        exit(OVERFLOW);
    }

    va_start(ap, num); // ap指向固定参数num后面的实参表
    int m = va_arg(ap, ElemType); //读取参数，并赋值给m
    for (int i = 1; i < num; ++i) {
        int n = va_arg(ap, ElemType);
        if (n > m) {
            m = n;
        }
    }
    va_end(ap);
    return m;
}


int main(){
    printf("1.最大值为%d\n", Max(4, 7, 9, 5, 8));
    printf("2.最大值为%d\n", Max(3, 17, 36, 25)); 
    // printf就是含有变长参数表的c语言库函数
    // 第一个形参是字符串常量或字符型指针
    // 第二个形参是变长参数表

    return 0;
}

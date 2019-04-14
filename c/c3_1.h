/*************************************************************************
	> File Name: c3_1.h
	> Author: 
	> Mail: 
	> Created Time: 2019年04月08日 星期一 21时08分57秒
 ************************************************************************/

#ifndef _C3_1_H
#define _C3_1_H

#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 2

struct SqStack{
    SElemType *base;
    SElemType *top;
    int stacksize;
};

#endif

/*************************************************************************
	> File Name: sqstack.h
	> Author: 
	> Mail: 
	> Created Time: 2019年04月08日 星期一 21时08分57秒
 ************************************************************************/

#ifndef _SQSTACK_H
#define _SQSTACK_H

#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 2

struct SqStack{
    SElemType *base;
    SElemType *top;
    int stacksize;
};

#endif

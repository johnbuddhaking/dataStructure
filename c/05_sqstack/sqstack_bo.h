/*************************************************************************
	> File Name: sqstack_bo.h
	> Author: 
	> Mail: 
	> Created Time: 2019年04月09日 星期二 20时25分03秒
 ************************************************************************/

#ifndef _SQSTACK_BO_H
#define _SQSTACK_BO_H

void InitStack(SqStack &S)
{
    S.base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));

    if(!S.base){
        exit(OVERFLOW);
    }

    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
}

void DestoryStack(SqStack &S){

    free(S.base);
    S.base = S.top = NULL;
    S.stacksize = 0;
}

void ClearStack(SqStack &S){
    S.top = S.base;
}

Status StackEmpty(SqStack S){
    
    if(S.top == S.base){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int StackLength(SqStack S){
    return S.top - S.base;
}

Status GetTop(SqStack S, SElemType &e){

    if(S.top > S.base){
        e = *(S.top - 1);
        return OK;
    }
    return ERROR;
}

void Push(SqStack &S, SElemType e){
    
    if(S.top == S.base + S.stacksize){
        S.base = (SElemType*)realloc(S.base, (S.stacksize + STACK_INCREMENT)*sizeof(SElemType));

        if(!S.base){
            exit(OVERFLOW);
        }

        S.top = S.base + S.stacksize;
        S.stacksize += STACK_INCREMENT;
    }

    *(S.top++) = e;
}


Status Pop(SqStack &S, SElemType &e){
    
    if(S.top == S.base){
        return ERROR;
    }

    e = * --S.top;
    return OK;
}

void StackTraverse(SqStack S, void(*visit)(SElemType)){
    SElemType *p = S.base;

    while(p < S.top){
        visit(*(p++));
    }
    
    printf("\n");
}


#endif

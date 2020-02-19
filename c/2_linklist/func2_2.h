/*************************************************************************
	> File Name: func2-2.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月15日 星期五 20时14分34秒
 ************************************************************************/

#ifndef _FUNC2_2_H
#define _FUNC2_2_H

Status equal(ElemType c1, ElemType c2){
    if(c1 == c2){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int comp(ElemType a, ElemType b){
    if(a == b){
        return 0;
    }
    else{
        return (a - b) / abs(a - b);
    }
}

void print(ElemType c){
    printf("%d ", c);
}

void print1(ElemType &c){
    printf("%d ", c);
}

void print2(ElemType c){
    printf("%c ", c);
}

#endif


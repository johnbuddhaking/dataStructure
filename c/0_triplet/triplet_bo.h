/*************************************************************************
	> File Name: triplet_bo.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月07日 星期四 22时13分42秒
 ************************************************************************/

#ifndef _TRIPLET_BO_H
#define _TRIPLET_BO_H

Status InitTriplet(Triplet &T, ElementType v1, ElementType v2, ElementType v3){
    T = (ElementType *)malloc( 3 * sizeof(ElementType));
    if(!T){
        exit(OVERFLOW);
    }

    T[0] = v1;
    T[1] = v2;
    T[2] = v3;

    return OK;

}

Status DestroyTriplet(Triplet &T){
    if(T){
        delete(T);
        T = NULL;
    }

    return OK;
}

#endif

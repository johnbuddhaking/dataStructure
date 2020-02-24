/************************************************************************
	> File Name: test_triplet.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月07日 星期四 21时39分29秒
 ************************************************************************/
#include<iostream>
#include "c1.h"
typedef double ElementType;
#include "triplet.h"
#include "triplet_bo.h"
using namespace std;


int main(){
    Triplet T;
    InitTriplet(T, 1, 2, 3);
    DestroyTriplet(T);
    cout << "haha" << endl;

    return 0;
}


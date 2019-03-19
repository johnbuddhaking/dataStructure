/*************************************************************************
	> File Name: algo2_4.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年03月17日 星期日 20时22分58秒
 ************************************************************************/

#include<iostream>
using namespace std;
#include "c1.h"
#define N 6
typedef char ElemType[N];
#include "c2_3.h"

int main(){
    SLinkList s = {
        {"",1},
        {"zhao",2},
        {"qian",3},
        {"sun",4},
        {"li",5},
        {"zhou",6},
        {"wu",7},
        {"zheng",8},
        {"wang",0}
    };

    int i = s[0].cur;

    while(i){
        printf("%s ", s[i].data);
        i = s[i].cur;
    }
    printf("\n");

    s[4].cur = 9;
    s[9].cur = 5;
    strcpy(s[9].data, "shi");

    s[6].cur = 8;
    i = s[0].cur;

    while(i){
        printf("%s ", s[i].data);
        i = s[i].cur;
    }

    printf("\n");

    return 0;
}

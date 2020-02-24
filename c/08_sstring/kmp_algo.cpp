// File Name: kmp_algo.cpp
// Author: 
// Created Time: 2020年02月23日 星期日 17时22分29秒

#include "c1.h"
#include "sstring.h"
#include "sstring_bo.h"

void get_next(SString t, int next[]) {
    int i = 1;
    next[1] = 0;

    int j = 0;

    while (i < t[0]) {
        if (j == 0 || t[i] == t[j]) {
            ++i;
            ++j;

            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

void get_next_improve(SString t, int next[]) {
    int i = 1;
    next[1] = 0;

    int j = 0;

    while (i < t[0]) {
        if (j == 0 || t[i] == t[j]) {
            ++i;
            ++j;
            if (t[i] == t[j]) {
                next[i] = next[j];
            }
            else {
                next[i] = j;
            }
        }
        else {
            j = next[j];
        }
    }
}


int Index_KMP(SString s, SString t, int pos, int next[]) {
    int i = pos; 
    int j = 1;

    while(i <= s[0] && j <= t[0]) {
        if (j == 0 || s[i] == t[j]) {
            ++i;
            ++j;
        }
        else {
            j = next[j];
        }
    }

    if (j > t[0]) {
        return i - t[0];
    }
    else {
        return 0;
    }
}

int main(){

    SString s1, s2;

    StrAssign(s1, "aaabaaaab");
    printf("主串为");
    StrPrint(s1);

    StrAssign(s2, "aaaab");
    printf("子串为");
    StrPrint(s2);

    int * p = (int *)malloc((StrLength(s2) + 1) * sizeof(int));
    get_next(s2, p);
    printf("子串的next数组为");
    for (int i = 1; i <= StrLength(s2); ++i) {
        printf("%d", *(p + i));
    }
    printf("\n");

    int i = Index_KMP(s1, s2, 1, p);
    if (i) {
        printf("主串和子串在第%d个字符处首次匹配\n", i);
    }
    else {
        printf("主串和子串匹配不成功\n");
    }

    get_next_improve(s2, p);
    printf("子串next_imporve数组为");
    for (int i = 1; i <= StrLength(s2); ++i) {
        printf("%d", *(p + i));
    }
    printf("\n");

    printf("主串和子串在第%d个字符处首次匹配\n", Index_KMP(s1, s2, 1, p));
    return 0;
}

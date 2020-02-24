// File Name: main_hstring.cpp
// Author: 
// Created Time: 2020年02月22日 星期六 20时00分52秒

#include "c1.h"
#include "hstring.h"
#include "hstring_bo.h"
typedef HString String;
#include "string_func.h"

int main(){
    char *p = "God bye!";
    char *q = "God luck!";

    HString t, s, r;
    InitString(t);
    InitString(s);
    InitString(r);

    StrAssign(t, p);
    printf("串t为");
    StrPrint(t);
    printf("串长为%d，串空否？%d(1:空 0:否)\n", StrLength(t), StrEmpty(t));

    StrAssign(s, q);
    printf("串s为");
    StrPrint(s);

    int i = StrCompare(s, t);
    char c;
    if (i < 0) {
        c = '<';
    }
    else if (i == 0) {
        c = '=';
    }
    else {
        c = '>';
    }
    printf("串s %c 串t\n", c);

    Concat(r, t, s);
    printf("串t连接串s产生的串r为");
    StrPrint(r);

    StrAssign(s, "oo");
    printf("串s为");
    StrPrint(s);

    StrAssign(t, "o");
    printf("串t为");
    StrPrint(t);

    Replace(r, t, s);
    printf("把串r中和串t相同的子串用串s代替后，串r为");
    StrPrint(r);

    ClearString(s);
    printf("串s清空后，串长为%d，串空否？%d(1:空 0:否)\n", StrLength(s), StrEmpty(s));

    SubString(s, r, 6, 4);
    printf("串s为从串r的第6个字符起的4个字符，长度为%d，串s为", s.length);
    StrPrint(s);

    StrCopy(t, r);
    printf("由串r复制得串t，串t为");
    StrPrint(t);

    StrInsert(t, 6, s);
    printf("在串t的第6个字符前插入串s后，串t为");
    StrPrint(t);

    StrDelete(t, 1, 5);
    printf("从串t的第1个字符起，删除5个字符后，串t为");
    StrPrint(t);

    printf("%d是从串的第1个字符起，和串s相同的第1个子串的位置\n", Index(t, s, 1));
    printf("%d是从串的第2个字符起，和串s相同的第1个子串的位置\n", Index(t, s, 2));

    DestroyString(t);

    return 0;
}

#ifndef _STRING_FUNCTION_H
#define _STRING_FUNCTION_H

int Index(String s, String t, int pos){
    // 如果在s的pos下标之后有t子串，返回第一个下标
    String sub;
    InitString(sub);

    if(pos > 0){
        int n = StrLength(s);
        int m = StrLength(t);
        int i = pos;

        while(i <= n - m + 1){
            SubString(sub, s, i, m);

            if(StrCompare(sub, t) == 0){
                return i;
            }

            ++i;
        }
    }

    return 0;
}

Status Replace(String &s, String t, String v){
    // 在主串s中，用v替换t
    
    if(StrEmpty(t)){
        return ERROR;
    }

    int i = 1;

    while(i){
        i = Index(s, t, i);

        if(i){
            StrDelete(s, i, StrLength(t));
            Status k = StrInsert(s, i, v);

            if(!k){
                return ERROR;
            }
            
            i += StrLength(v);
        }
    }

    return OK;
}


#endif

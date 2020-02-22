#ifndef _SSTRING_BO_H
#define _SSTRING_BO_H

#define DestroyString ClearString
#define InitString ClearString

Status StrAssign(SString t, char* chars){
    // 生成一个其值等于chars的串
    if(strlen(chars) > MAX_STRING_LEN){
        return ERROR;
    }

    t[0] = strlen(chars);

    for (int i = 1; i <= t[0]; ++i) {
        t[i] = * (chars + i - 1);   
    }

    return OK;
}

void StrCopy(SString t, SString s) {
    // copy s into t
    for (int i = 0; i <= s[0]; ++i) {
        t[i] = s[i];
    }
}

Status StrEmpty(SString s) {
    if (s[0] == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int StrCompare(SString s, SString t) {
    
    for (int i = 1; i <= s[0] && i <= t[0]; ++i) {
        
        if (s[i] != t[i]) {
            return s[i] - t[i];
        }
    }

    return s[0] - t[0];
}

int StrLength(SString s) {
    return s[0];
}

void ClearString(SString s) {
    s[0] = 0;
}

Status Concat(SString t, SString s1, SString s2) {
    int t_len = 0;

    for (int i = 1; i <= s1[0]; ++i) {
        t[++t_len] = s1[i];
    }

    for (int i = 1; i <= s2[0]; ++i) {
        ++t_len;

        if (t_len > MAX_STRING_LEN) {
            return FALSE;
            break;
        }

        t[t_len] = s2[i];
    }

    t[0] = t_len;

    if (t_len == s1[0] + s2[0]) {
        return TRUE;
    }

    return FALSE;
}

Status SubString(SString sub, SString s, int pos, int len) {
    if ( pos < 1 || pos > s[0] || len < 0 || len > s[0] - pos + 1) {
        return ERROR;
    }

    for (int i = 1; i <= len; ++i) {
        sub[i] = s[pos + i - 1];
    }

    sub[0] = len;
    return OK;
}

int IndexNaive(SString s, SString t, int pos) {
    // s is main string, t is substring
    
    if (pos < 1 || pos > MAX_STRING_LEN) {
        return 0;
    }

    int i = pos;
    int j = 1;

    while (i <= s[0] - t[0] + 1 && j <= t[0]) {
        if (s[i] == t[j]) {
            ++i;
            ++j;
        } 
        else {
            i = i - j + 2;
            j = 1;
        }
    }

    if ( j > t[0]) {
        return i - t[0];
    }

    return 0;
}

Status StrInsert(SString s, int pos, SString t) {
    
    if (pos < 1 || pos > s[0] + 1) {
        return ERROR;
    }

    if (s[0] + t[0] <= MAX_STRING_LEN) {
        
        for (int i = s[0]; i >= pos;  --i) {
            s[i + t[0]] = s[i];
        }

        for (int i = 0; i < t[0]; ++i) {
            s[pos + i] = t[i + 1];
        }

        s[0] += t[0];
        return TRUE;
    }
    else {
        
        for (int i = MAX_STRING_LEN; i >= pos + t[0]; --i) {
            s[i] = s[i - t[0]];
        }

        for (int i = pos; i <= pos + t[0] && i <= MAX_STRING_LEN; ++i) {
            s[i] = t[i - pos + 1];
        }

        s[0] = MAX_STRING_LEN;
        return FALSE;
    }
}

Status StrDelete(SString s, int pos, int len) {
    
    if (pos < 1 || len < 0 || pos > s[0] - len + 1) {
        return ERROR;
    }

    for (int i = pos + len; i <= s[0]; ++i) {
        s[i - len] = s[i];
    }

    s[0] -= len;
    return OK;
}

void StrPrint(SString s) {
    for (int i = 0; i < s[0]; ++i) {
        printf("%c", s[i + 1]);
    }
    printf("\n");
}

#endif

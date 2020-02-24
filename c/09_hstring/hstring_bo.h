#ifndef _HSTRING_BO_H
#define _HSTRING_BO_H

#define DestroyString ClearString

void InitString(HString &s) {
    s.length = 0;
    s.ch = NULL;
}

void ClearString(HString &s) {
    free(s.ch);
    InitString(s);
}

void StrAssign(HString &t, char * chars) {
    if (t.ch) {
        free(t.ch);
    }

    int i = strlen(chars);

    if (i == 0) {
        InitString(t);
    }
    else {
        t.ch = (char *)malloc(i * sizeof(char));
        if (!t.ch) {
            exit(OVERFLOW);
        }

        for (int j = 0; j < i; ++j) {
            t.ch[j] = chars[j];
        }

        t.length = i;
    }
}

void StrCopy(HString &t, HString s) {
    if (t.ch) {
        free(t.ch);
    }

    t.ch = (char *)malloc(s.length * sizeof(char));
    if (!t.ch) {
       exit(OVERFLOW); 
    }

    for (int i = 0; i < s.length; ++i) {
        t.ch[i] = s.ch[i];
    }

    t.length = s.length;
}

Status StrEmpty(HString s) {
    if (s.length == 0 && s.ch == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int StrCompare(HString s, HString t) {
    for (int i = 0; i < s.length && i < t.length; ++i) {
        if (s.ch[i] != t.ch[i]) {
            return s.ch[i] - t.ch[i];
        }
    }

    return s.length - t.length;
}

int StrLength(HString s) {
    return s.length;
}

void Concat(HString &t, HString s1, HString s2) {
    if (t.ch) {
        free(t.ch);
    }

    t.length = s1.length + s2.length;
    t.ch = (char *)malloc(t.length * sizeof(char));

    if (!t.ch) {
        exit(OVERFLOW);
    }

    for (int i = 0; i < s1.length; ++i) {
        t.ch[i] = s1.ch[i];
    }

    for (int i = 0; i < s2.length; ++i) {
        t.ch[s1.length + i] = s2.ch[i];
    }
}

Status SubString(HString &sub, HString s, int pos, int len) {
    if (pos < 1 || pos > s.length || len < 0 || len > s.length -pos + 1) {
        return ERROR;
    }

    if (sub.ch) {
        free(sub.ch); 
    }

    if (len == 0) {
        InitString(sub);
    }
    else {
        sub.ch = (char *)malloc(len * sizeof(char));

        if (!sub.ch) {
            exit(OVERFLOW);
        }

        for(int i = 0; i < len; ++i) {
            sub.ch[i] = s.ch[pos -1 + i];
        }

        sub.length = len;
    }

    return OK;
}

Status StrInsert(HString &s, int pos, HString t) {
    
    if (pos < 1 || pos > s.length + 1) {
        return ERROR;
    }

    if (t.length) {
        s.ch = (char *)realloc(s.ch, (s.length + t.length) * sizeof(char));

        if (!s.ch) {
            exit(OVERFLOW);
        }

        for (int i = s.length - 1; i >= pos - 1; --i) {
            s.ch[i + t.length] = s.ch[i];
        }

        for (int i = 0; i < t.length; ++i) {
            s.ch[pos - 1 + i] = t.ch[i];
        }

        s.length += t.length;
    }

    return OK;
}

Status StrDelete(HString &s, int pos, int len) {
    if (len < 0 || len > s.length || pos < 1 || pos > s.length - len + 1) {
        return ERROR;
    }

    for (int i = pos + len - 1; i < s.length; ++i) {
        s.ch[i - len] = s.ch[i];
    }

    s.length -= len;
    s.ch = (char *)realloc(s.ch, s.length * sizeof(char));
    return OK;
}

void StrPrint(HString s) {
    for (int i = 0; i < s.length; ++i) {
        printf("%c", s.ch[i]);
    }
    printf("\n");
}

#endif

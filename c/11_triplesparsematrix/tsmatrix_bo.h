#ifndef _TSMATRIX_BO_H
#define _TSMATRIX_BO_H

int comp(int c1, int c2) {
    if (c1 < c2) {
        return -1;
    }
    else if (c1 == c2) {
        return 0;
    }
    else {
        return 1;
    }
}

Status CreateSMatrix(TSMatrix &M) {
    
    printf("请输入矩阵的行数，列数，非零元个数：");
    scanf("%d %d %d", &M.mu, &M.nu, &M.tu);

    if (M.tu > MAX_SIZE) {
        return ERROR;
    }

    M.data[0].i = 0;

    for (int i = 1; i <= M.tu; ++i) {
        Status k = 0;
        Triple T;
        do {
            printf("请按行序顺序输入第%d个非零元素所在的行(1~%d),列(1~%d),元素值:", i, M.mu, M.nu);
            scanf("%d %d %d", &T.i, &T.j, &T.e);
        
            k = 0;
            if (T.i < 1 || T.i > M.mu || T.j < 1 || T.j > M.nu) {
                k = 1;
            }
            if (T.i < M.data[i - 1].i || T.i == M.data[i - 1].i && T.j <= M.data[i - 1].j) {
                k = 1;
            }
        } while(k); // 如果不是按从小到大的顺序输入，则重新输入

        M.data[i] = T;
    }

    return OK;
}

Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q) {
    if (M.mu != N.mu || M.nu != N.nu) {
        return ERROR;
    }

    Q.mu = M.mu;
    Q.nu = M.nu;

    int m = 1;
    int n = 1;
    int q = 0;

    while (m <= M.tu && n <= N.tu) {
        switch(comp(M.data[m].i, N.data[n].i)) {
            case -1: 
                Q.data[++q] = M.data[m++];
                break;
            case 1:
                Q.data[++q] = N.data[n++];
                break;
            case 0:
                switch(comp(M.data[m].j, N.data[n].j)) {
                    case -1:
                        Q.data[++q] = M.data[m++];
                        break;
                    case 1:
                        Q.data[++q] = N.data[n++];
                        break;
                    case 0:
                        Q.data[++q] = M.data[m++];
                        Q.data[q].e += N.data[n++].e;
                        if (Q.data[q].e == 0) {
                            --q;
                        }
                }
        }
    }

    while (m <= M.tu) {
        Q.data[++q] = M.data[m++];
    }

    while (n <= N.tu) {
        Q.data[++q] = N.data[n++];
    }

    Q.tu = q;
    return OK;
}

void TransposeSMatrix(TSMatrix M, TSMatrix &T) {
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;

    int q = 0;

    if (T.tu) {
        for (int col = 1; col <= M.nu; ++col) {
            for (int p = 1; p <= T.tu; ++p) {
                if (M.data[p].j == col) {
                    ++q;
                    T.data[q].i = M.data[p].j;
                    T.data[q].j = M.data[p].i;
                    T.data[q].e = M.data[p].e;
                }
            }
        }
    }
}

void PrintSMatrix(TSMatrix M) {
    Triple *p = M.data + 1;
    int k = 1;

    for (int i = 1; i <= M.mu; ++i) {
        for (int j = 1; j <= M.nu; ++j) {
            
            if (k <= M.tu && p->i == i && p->j == j) {
                printf("%3d", (p++)->e);
                ++k;
            }
            else {
                printf("%3d", 0);
            }
        }
        printf("\n");
    }
}

Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q) {
    
    if (M.nu != N.mu) {
        return ERROR;
    }

    Q.mu = M.mu;
    Q.nu = N.nu;
    Q.tu = 0;

    TSMatrix NT;
    TransposeSMatrix(N, NT);

    for (int i = 1; i <= M.mu; ++i) { // 新矩阵行数
        int q = 1;

        for (int j = 1; j <= NT.mu; ++j) { // 新矩阵列数
            int p = 1;

            ElemType Qs = 0; // 记录乘积

            while (M.data[q].i < i) {
                ++q;
            }

            while (NT.data[p].i < j) {
                ++p;
            }

            while (q <= M.tu && p <= NT.tu && M.data[q].i == i && NT.data[p].i == j) {
                switch(comp(M.data[q].j, NT.data[p].j)) {
                    case -1:
                        ++q;
                        break;
                    case 1:
                        ++p;
                        break;
                    case 0:
                        Qs += M.data[q++].e * NT.data[p++].e;
                }
            }

            if (Qs) {
                if (++Q.tu > MAX_SIZE) {
                    return ERROR;
                }

                Q.data[Q.tu].i = i;
                Q.data[Q.tu].j = j;
                Q.data[Q.tu].e = Qs;
            }
        }
    }

    return OK;
}

void DestroySMatrix(TSMatrix &M) {
    M.mu = M.nu = M.tu = 0;
}


void CopySMatrix(TSMatrix M, TSMatrix &T) {
    T = M;
}

Status SubtSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q) {
    if (M.mu != N.mu || M.nu != N.nu) {
        return ERROR;
    }

    for (int i = 1; i <= N.tu; ++i) {
        N.data[i].e *= -1;
    }

    AddSMatrix(M, N, Q);
    return OK;
}

void FastTransposeSMatrix(TSMatrix M, TSMatrix &T) {
    
    int *num = (int *)malloc((M.nu + 1) * sizeof(int)); // non-zero numbers for each column of M

    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;

    if (T.tu) {
        
        for (int i = 0; i < M.nu + 1; ++i) {
            num[i] = 0;
        }

        for (int i = 1; i <= M.tu; ++i) {
           int col = M.data[i].j;
           ++num[col];
        }

        for (int i = 1; i < M.nu; ++i) {
            num[i + 1] += num[i];
        }

        for (int i = M.tu; i >= 1; --i) {
            int col = M.data[i].j;
            int idx = num[col];
            --num[col];

            T.data[idx].e = M.data[i].e;
            T.data[idx].j = M.data[i].i;
            T.data[idx].i = M.data[i].j;
        }
    }

    free(num);
}
#endif

#ifndef _RLSMATRIX_BO_H
#define _RLSMATRIX_BO_H

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

Status CreateSMatrix(RLSMatrix &M) {
    
    printf("请输入行数、列数、非零元个数:");
    scanf("%d %d %d", &M.mu, &M.nu, &M.tu);

    if (M.tu > MAX_SIZE || M.mu > MAX_RC) {
        return ERROR;
    }

    for (int i = 1; i <= M.mu; ++i) {
        M.rpos[i] = 0;
    }


    int rowth = 0;
    int elemNum = 0;

    for (int i = 1; i <= M.tu; ++i) {
        Status k = 1;
        Triple T;

        while (k) {

            printf("请按行序顺序输入第%d个非零元素所在的行(1~%d),列(1~%d),元素值:\n", i, M.mu, M.nu);
            scanf("%d %d %d", &T.i, &T.j, &T.e);

            k = 0;
            if (T.i < 1 || T.i > M.mu || T.j < 1 || T.j > M.nu) {
                k = 1;
            }
            if (T.i < M.data[i - 1].i || T.i == M.data[i - 1].i && T.j <= M.data[i - 1].j){
                k = 1;
            }
        }

        ++elemNum;
        if (rowth != T.i) {
            rowth = T.i;
            M.rpos[rowth] = elemNum;
        }
        
        M.data[i] = T;
    }

}


void PrintSMatrix(RLSMatrix M) {
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

Status AddSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q) {
    
    if (M.mu != N.mu || M.nu != N.nu) {
        return ERROR;
    }

    Q.mu = M.mu;
    Q.nu = M.nu;
    Q.tu = 0;

    for (int i = 1; i <= Q.mu; ++i) {
        Q.rpos[i] = 0;
    }

    for (int k = 1; k <= M.mu; ++k) {

        int mk = M.rpos[k];
        int nk = N.rpos[k];
        bool mflag = false;
        bool nflag = true;


        if (mk == 0) {
            mk = M.tu + 1;
            mflag = true;
        }

        if (nk == 0) {
            nk = N.tu + 1;
            nflag = true;
        }

        int elems = 0;
        while (M.data[mk].i == k && N.data[nk].i == k && mk <= M.tu && nk <= N.tu) {
            switch(comp(M.data[mk].j, N.data[nk].j)) {
                case -1:
                    ++elems;
                    M.data[++Q.tu] = M.data[mk++];
                    break;
                case 1:
                    ++elems;
                    M.data[++Q.tu] = N.data[nk++];
                    break;
                case 0:
                    int sum = M.data[mk].e + N.data[nk].e;
                    if (sum == 0) {
                        ++mk;
                        ++nk;
                        break;
                    }
                    else {
                        Q.data[++Q.tu].e = sum;
                        Q.data[Q.tu].i = M.data[mk].i;
                        Q.data[Q.tu].j = M.data[mk].j;
                        ++mk;
                        ++nk;
                        ++elems;
                    }

            }       
        }

        while (M.data[mk].i == k && mk <= M.tu ) {
            ++elems;
            Q.data[++Q.tu] = M.data[mk++];
        }

        while (N.data[nk].i == k && nk <= N.tu) {
            ++elems;
            Q.data[++Q.tu] = N.data[nk++];
        }

        if (!(mflag && nflag)) {
            Q.rpos[k] = Q.tu - elems + 1;
        }
    }

    return OK;
}

void TransposeSMatrix(RLSMatrix M, RLSMatrix &T) {
    
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;

    if (T.tu) {
        for (int k = 1; k <= T.mu; ++k) {
            T.rpos[k] = 0;
        }

        for (int k = 1; k <= M.tu; ++k) {
            T.rpos[M.data[k].j] += 1;
        }

        int idx = 1;
        for (int k = 1; k <= T.mu; ++k) {
            if (T.rpos[k] != 0) {
                idx += T.rpos[k];
                T.rpos[k] = idx;
            } 
            else {
                T.rpos[k] = 0;
            }
        }

        for (int k = M.tu; k >= 1; --k) {
            int rth = M.data[k].j;
            int idx = --T.rpos[rth];
            T.data[idx].i = M.data[k].j;
            T.data[idx].j = M.data[k].i;
            T.data[idx].e = M.data[k].e;
        }

    }
}

Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q) {
    
    if (M.nu != N.mu) {
        return ERROR;
    }

    Q.mu = M.mu;
    Q.nu = N.nu;
    Q.tu = 0;

    if (M.tu * N.tu == 0) {
        return OK;
    }

    for (int i = 1; i <= Q.mu; ++i) {
        Q.rpos[i] = 0;
    }

    int pos = 0;
    int rth = 0;
    
    RLSMatrix T;
    TransposeSMatrix(N, T);
    
    for (int r = 1; r <= Q.mu; ++r) {
        for (int c = 1; c <= Q.nu; ++c) {
            
            int m = M.rpos[r];
            int n = T.rpos[c];

            if (m == 0) {
                m = M.tu + 1;
            }

            if (n == 0) {
                n = N.tu + 1;
            }

            ElemType e = 0;

            while (M.data[m].i == r && T.data[n].i == c && m <= M.tu && n <= T.tu) {
                switch(comp(M.data[m].j, T.data[n].j)) {
                    case -1:
                        ++m;
                        break;
                    case 1:
                        ++n;
                        break;
                    case 0:
                        e += M.data[m].e * T.data[n].e;
                        ++m;
                        ++n;
                }
            }

            if (e) {
                ++pos;
                Q.data[pos].i = r;
                Q.data[pos].j = c;
                Q.data[pos].e = e;

                if (rth != r) {
                    rth = r;
                    Q.rpos[r] = pos;
                }
            }
        }
    }

    Q.tu = pos;
    return OK;
}

void DestroySMatrix(RLSMatrix &M) {
    M.mu = M.nu = M.tu = 0;
}


void CopySMatrix(RLSMatrix M, RLSMatrix &T) {
    T = M;
}

Status SubtSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix &Q) {
    if (M.mu != N.mu || M.nu != N.nu) {
        return ERROR;
    }

    for (int i = 1; i <= N.tu; ++i) {
        N.data[i].e *= -1;
    }

    AddSMatrix(M, N, Q);
    return OK;
}

#endif

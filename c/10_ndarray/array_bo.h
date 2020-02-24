#ifndef _ARRAY_BO_H
#define _ARRAY_BO_H

Status InitArray(Array &A, int dim, ...) {

    if (dim < 1 || dim > MAX_ARRAY_DIM) {
        return ERROR;
    }

    A.dim = dim;

    A.bounds = (int *)malloc(dim * sizeof(int));
    if (!A.bounds) {
        exit(OVERFLOW);
    }

    int elemtotal = 1;

    va_list ap; // 变长参数表类型，在stdarg.h中
    va_start(ap, dim); // 边长参数"..."从形参dim之后开始
    for (int i = 0; i < dim; ++i) {
        A.bounds[i] = va_arg(ap, int); // 逐一将边长参数赋值给a.bounds[i]
        if (A.bounds[i] < 0) {
            return UNDERFLOW; // 在math.h中定义为4
        }
        elemtotal *= A.bounds[i];
    }
    va_end(ap); // 结束提取变长参数

    A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
    if (!A.base) {
        exit(OVERFLOW);
    }

    A.constants = (int *)malloc(dim * sizeof(int));
    if (!A.constants) {
        exit(OVERFLOW);
    }
    A.constants[dim - 1] = 1; // 最后一维的偏移量为1
    for (int i = dim - 2; i >= 0; --i) {
        A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];
    }

    return OK;
}

void DestroyArray(Array &A) {
    if (A.base) {
        free(A.base);
    }

    if (A.bounds) {
        free(A.bounds);
    }

    if (A.constants) {
        free(A.constants);
    }

    A.base = A.bounds = A.constants = NULL;
    A.dim = 0;
}

Status Locate(Array A, va_list ap, int &off) {
    // 求相对地址
    for (int i = 0; i < A.dim; ++i) {
        int ind = va_arg(ap, int);
        if (ind < 0 || ind >= A.bounds[i]) {
            // 下标值不合法
            return OVERFLOW;
        }
        off += ind * A.constants[i];
    }

    return OK;
}

Status Value(ElemType &e, Array A, ...) { // 在 vc++ 中， "..." 之前的形参不能是引用类型
    int off = 0;
    
    va_list ap;
    va_start(ap, A);
    if (Locate(A, ap, off) == OVERFLOW) {
        return ERROR;
    }

    e = *(A.base + off);
    return OK;
}

Status Assign(Array A, ElemType e, ...) {

    int off = 0;

    va_list ap;
    va_start(ap, e);
    if (Locate(A, ap, off) == OVERFLOW) {
        return ERROR;
    }

    * (A.base + off) = e;
    return OK;
}
#endif

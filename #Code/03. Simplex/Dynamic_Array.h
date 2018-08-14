/*
* Copyright (c) 2018, Liu Peng, School of Mathematics and Statistics, YNU
* Apache License.
*
* 文件名称：Dynamic_Array.h
* 文件标识：
* 摘 要：对动态数组类型进行创建，操作
*
* 当前版本：1.0
* 作 者：刘鹏
* 完成日期：2018年5月5日
*
* 预期版本：可以加入矩阵求逆等新的方法
*/

#pragma once

#define INIT_SIZE       8

#include "Shell_Reader.h"

typedef struct Dynamic_Array {
    double *A;                  // low level pointe
    int capacity;               // whole capacity
    int n;                      // used capacity
} Dynamic_Array;

// Create a new empty dynamic array.
Dynamic_Array *Dynamic_Array_init(void) {
    Dynamic_Array *ans = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    if (ans == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }

    double *tmp = (double *)calloc(8, sizeof(double));
    ans->A = tmp;
    ans->capacity = INIT_SIZE;
    ans->n = 0;
    return ans;
}

// Get the element located in n.
// Take care, n is the natural location, so it need to minus 
// one during the locating process.
double Dynamic_Array_get_Element(Dynamic_Array *d, int n) {
    return *(d->A + n - 1);
}

void Dynamic_Array_print(Dynamic_Array *d) {
    int i = 1;
    for (; i <= d->n; i++) {
        printf("%8.2f\t", Dynamic_Array_get_Element(d, i));
    }
    printf("\n");
}

void Dynamic_Array_resize(Dynamic_Array *D) {
    int i = 0;
    double *tmp = (double *)calloc(2 * D->capacity, sizeof(double));
    if (tmp == NULL) {
        printf("Cannot get memory, crash!\n");
        return;
    }
    for (i = 0; i < D->capacity; i++) {
        *(tmp + i) = *(D->A + i);
    }
    D->A = tmp;
    D->capacity *= 2;
}

void Dynamic_Array_append(Dynamic_Array *D, double e) {
    if (D->n == D->capacity) {
        Dynamic_Array_resize(D);
    }
    *(D->A + D->n) = e;
    D->n += 1;
}

// Generate a new dynamic array to contain the answer, the source dynamic array
// won't be changed.
// The index of dynamic array begins from 1 rather zero.
Dynamic_Array *Dynamic_Array_quick_Sort(Dynamic_Array *a) {
    Dynamic_Array *less = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    less->A = (double *)calloc(1, sizeof(double));
    if (!less) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    less->capacity = 1;
    less->n = 0;

    Dynamic_Array *more = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    more->A = (double *)calloc(1, sizeof(double));
    if (!more) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    more->capacity = 1;
    more->n = 0;

    Dynamic_Array *eq = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    eq->A = (double *)calloc(1, sizeof(double));
    if (!eq) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    eq->capacity = 1;
    eq->n = 0;

    int i;
    if (a->n <= 1) {
        return a;
    }
    else {
        // double pivot = 1 / 3. * (*(a->A) + ;

        for (i = 0; i < a->n; i++) {
            double pivot = *(a->A);
            if (*(a->A + i) > pivot) {
                Dynamic_Array_append(more, *(a->A + i));
            }
            else {
                if (*(a->A + i) < pivot) {
                    Dynamic_Array_append(less, *(a->A + i));
                }
                else {
                    Dynamic_Array_append(eq, *(a->A + i));
                }
            }
        }
    }
    less = Dynamic_Array_quick_Sort(less);
    more = Dynamic_Array_quick_Sort(more);
    for (i = 0; i < eq->n; i++) {
        Dynamic_Array_append(less, *(eq->A + i));
    }
    for (i = 0; i < more->n; i++) {
        Dynamic_Array_append(less, *(more->A + i));
    }
    return less;
}

// This function is created for find the maximal value's index in objective function.
int Dynamic_Array_find_Maximal(Dynamic_Array *d) {
    double pivot = Dynamic_Array_get_Element(Dynamic_Array_quick_Sort(d), d->n);
    int i = 0;
    for (; i < d->n; i++) {
        if (*(d->A + i) == pivot) {
            return i + 1;
        }
    }
}

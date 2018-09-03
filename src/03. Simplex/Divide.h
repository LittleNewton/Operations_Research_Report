/*
* Copyright (c) 2018, Liu Peng, School of Mathematics and Statistics, YNU
* Apache License.
*
* 文件名称：Divide.h
* 文件标识：见配置管理计划书
* 摘 要：对于单纯形算法的最小比值试算提供支持。
*
* 当前版本：1.0
* 作 者：刘鹏
* 创建日期：2018年5月4日
* 完成日期：2018年5月
*
* 取代版本：
* 原作者 ：刘鹏
* 完成日期：
*/

#pragma once

#include <string.h>
#include "Dynamic_Array.h"


#define NEGATIVE            "Negative"
#define NOT_A_NUMBER        "NAN"
#define NORMAL              "Normal"
#define INIT_SIZE_DIV       8

// This is a new division supporting structure.
// If up/down can be done, value will maintain this value.
// If down is equal to zero, obviously this cannot be done,
// state will maintain its state ad "NaN", which means the 
// answer is Not a Number.
typedef struct Div {
    double up;
    double down;
    double value;
    char state[10];
} Div;

// In order to maintain this data structure, I have to write 
// this container. It is too bad.
typedef struct Div_Dynamic_Array {

    Div *A;
    int capacity;
    int n;
} Div_Dynamic_Array;

void Div_Dynamic_Array_resize(Div_Dynamic_Array *D) {
    int i = 0;
    Div *tmp = (Div *)calloc(2 * D->capacity, sizeof(Div));
    if (tmp == NULL) {
        printf("Cannot get memory, crash!\n");
        return;
    }
    for (i = 0; i < D->capacity; i++) {
        (tmp + i)->up = (D->A + i)->up;
        (tmp + i)->down = (D->A + i)->down;
        (tmp + i)->value = (D->A + i)->value;
        strcpy((tmp + i)->state, (D->A + i)->state);
    }
    free(D->A);
    D->A = tmp;
    tmp = NULL;

    D->capacity *= 2;
}

// Add a new element to this array.
void Div_Dynamic_Array_append(Div_Dynamic_Array *D, Div e) {
    if (D->n == D->capacity) {
        Div_Dynamic_Array_resize(D);
    }
    (D->A + D->n)->up = e.up;
    (D->A + D->n)->down = e.down;
    (D->A + D->n)->value = e.value;
    strcpy((D->A + D->n)->state, e.state);
    D->n += 1;
}

// Generate a new empty div dynamic array.
Div_Dynamic_Array *Div_Dynamic_Array_init(Dynamic_Array *a, Dynamic_Array *b) {
    Div_Dynamic_Array *ans = (Div_Dynamic_Array *)calloc(1, sizeof(Div_Dynamic_Array));
    if (ans == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    ans->A = (Div *)calloc(a->n, sizeof(Div));
    ans->capacity = a->n;
    ans->n = 0;

    if (a->n != b->n) {
        printf("length should be the same.");
        return NULL;
    }

    int i;
    for (i = 0; i < a->n; i++) {
        if (*(b->A + i) == 0) {
            Div tmp;
            tmp.up = NULL;
            tmp.down = NULL;
            tmp.value = NULL;
            char c[] = "NaN";
            strcpy(tmp.state, c);
            Div_Dynamic_Array_append(ans, tmp);
        }
        else {
            if (*(b->A + i) < 0.) {
                Div tmp;
                tmp.up = *(a->A + i);
                tmp.down = *(b->A + i);
                tmp.value = tmp.up / tmp.down;
                char c[] = "Negative";
                strcpy(tmp.state, c);
                Div_Dynamic_Array_append(ans, tmp);
            }
            else {
                Div tmp;
                tmp.up = *(a->A + i);
                tmp.down = *(b->A + i);
                tmp.value = tmp.up / tmp.down;
                char c[] = "Normal";
                strcpy(tmp.state, c);
                Div_Dynamic_Array_append(ans, tmp);
            }
        }
    }
    return ans;
}

void Div_Dynamic_Array_print(Div_Dynamic_Array *d) {
    int i;
    printf("The answer C = (");
    for (i = 0; i < d->n; i++) {
        if (!strcmp((d->A + i)->state, "NaN")) {
            printf("%s ", "NaN");
        }
        else {
            double value = (d->A + i)->value;
            printf("%2.2f ", value);
        }
        if (i == d->n - 1) {
            printf("");
        }
        else {
            printf(", ");
        }
    }
    printf(")\n");
}

// find the minimal value in this array and return its location.
int Div_Dynamic_Array_find_Minimal(Div_Dynamic_Array *a) {
    Dynamic_Array *c = Dynamic_Array_init();
    Dynamic_Array *d = Dynamic_Array_init();
    int k = a->n;
    if (c == NULL || d == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    c->capacity = a->n;

    int i = 0;
    for (i = 0; i < a->n; i++) {
        if (!strcmp((a->A + i)->state, "Normal")) {
            Dynamic_Array_append(c, (a->A + i)->value);
        }
    }
    d = Dynamic_Array_quick_Sort(c);

    double pivot = *(d->A + 0);
    Dynamic_Array *tmp = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    tmp->A = (double *)calloc(1, sizeof(double));
    if (tmp == NULL || tmp->A == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }

    tmp->capacity = 1;
    tmp->n = 0;
    for (i = 0; i < a->n; i++) {
        if (!strcmp((a->A + i)->state, "Normal") && (a->A + i)->value == pivot) {
            Dynamic_Array_append(tmp, ++i);
        }
    }
    if (tmp->n == 0) {
        printf("Sorry, no minimal value.\n");
        return NULL;
    }
    return int(*(tmp->A));  // Selecting the first one is modest.
}

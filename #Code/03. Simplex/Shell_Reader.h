/*
* Copyright (c) 2018, Liu Peng, School of Mathematics and Statistics, YNU
* Apache License.
*
* 文件名称：Shell_Reader.h
* 文件标识：见配置管理计划书
* 摘 要：控制输入，使得当从键盘读入字符串时，字符串可以被准确解释成浮点型数据
*
* 当前版本：1.0
* 作 者：刘鹏
* 完成日期：2018年5月3日
*
* 取代版本：
* 原作者 ：刘鹏
* 完成日期：
*/


#pragma once

#include "Matrix_Operation.h"
#include "Dynamic_Array.h"
#include "Divide.h"

// This is a container for creating a stack data structure.
typedef struct char_LinkedList {
    char_LinkedList *head;
    char elements;
    int times;
    char_LinkedList *next;
} char_LinkedList;

// Used to modify the string get from the keyboard.
// Get rid of the spaces and other "(", ")".
char *clean(char *string) {
    char *head = string;

    int count_space = 0;
    // STEP 1: Count the spaces in this string.
    while (*string == ' ' && *string != '\0') {
        count_space += 1;
        string += 1;
    }

    string = head;
    int len = 1;
    // STEP 2: Count the characters in this string.
    while (*string != '\0') {
        len += 1;
        string++;
    }

    string = head;
    char *ans = (char *)calloc(len - count_space, sizeof(char));
    // STEP 3: Generate a new string.

    if (ans == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }

    char *ans_head = ans;
    while (*string != '\0') {
        if (*string != ' ') {
            *ans = *string;
            ans++;
        }
        string++;
    }
    *ans = *string;
    // Add '\0' to the tail of ans.
    ans = ans_head;
    // Get rid of "(".
    string = head;

    for (; *ans != '\0'; ans++) {
        if (*(ans + 1) == '\0') {
            *ans = ';';
        }
    }
    if (*ans_head == '(') {
        return ++ans_head;
    }
    else {
        return ans_head;
    }
}

// Cut a part of the string containing the vector or matrix.
// This function is created for supporting the get_Number funciton.
char *cut(char *string) {
    while (*string != ',' && *string != ';') {
        if (*string == '\0') {
            return NULL;
        }
        string++;
    }
    return ++string;
}

// Need a string has been cleand.
double get_Number(char *string) {
    if (*string == '\0') {
        return 0;
    }

    double ans = 0.;

    if (*string != '-') {
        char_LinkedList *work = (char_LinkedList *)calloc(1, sizeof(char_LinkedList));
        if (work == NULL) {
            printf("fatal error: FUNCTION calloc can't get memory.\n");
            return 0;
        }

        char_LinkedList *head = work;
        int i = 1;
        while (*string != ',' && *string != ';') {
            work->elements = *string;
            work->times = i;
            work->next = (char_LinkedList *)calloc(1, sizeof(char_LinkedList));
            if (work->next == NULL) {
                printf("fatal error: FUNCTION calloc can't get memory.\n");
                return 0.;
            }
            work = work->next;
            work->elements = NULL;
            work->times = NULL;
            string++;
            i++;        // i will be used later
        }

        work->elements = *string;       // "," and ";" should be added, too.
        work->times = NULL;             // index of comma is meaningful

        string++;
        // string will be used in the next get number step but won't be used later.

        work = head;
        int dot = 1;
        int comma = 1;
        int dot_index = NULL;
        while (work->elements != ',' && work->elements != ';') {
            if (work->elements == '.') {
                dot_index = dot;
                break;
            }
            work = work->next;
            dot++;
        }

        if (dot_index == NULL) {
            dot_index = i;
        }

        work = head;

        while (work->times != NULL) {
            work->times = -1 * (work->times - dot_index);
            work = work->next;
        }

        work = head;

        while (work->elements != ',' && work->elements != ';') {
            if (work->elements == '.') {
                work = work->next;
                continue;
            }
            if (work->times > 0) {
                ans += pow(10, work->times - 1) * double(int(work->elements) - int('0'));
                work = work->next;
            }
            else {
                ans += pow(10, work->times) * double(int(work->elements) - int('0'));
                work = work->next;
            }
        }
    }
    else {
        string = string + 1;
        ans = -1 * get_Number(string);
    }
    return ans;
}

// Input a string, output a vector consists of double elements.
double *get_Vector(char *string) {
    char *src = clean(string);
    char *src_head = src;
    int i = 0;
    int count_comma = 0;
    while (*src != '\0') {
        if (*src == ',' || *src == ';') {
            count_comma += 1;
        }
        src++;
    }
    src = src_head;
    
    double *ans = (double *)calloc(count_comma, sizeof(double));
    if (ans == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    for (i = 0; i < count_comma; i++) {
        *(ans + i) = get_Number(src);
        src = cut(src);
    }
    return ans;
}

// Input a string, output its length of the vector consists of double elements.
int get_vector_Length(char *string) {
    char *src = clean(string);
    char *src_head = src;
    int i = 0;
    int count_comma = 0;
    while (*src != '\0') {
        if (*src == ',' || *src == ';') {
            count_comma += 1;
        }
        src++;
    }
    return count_comma;
}

// Input a string, output a vector consists of double elements.
int *get_INT_vector(char *string) {
    char *src = clean(string);
    char *src_head = src;
    int i = 0;
    int count_comma = 0;
    while (*src != '\0') {
        if (*src == ',' || *src == ';') {
            count_comma += 1;
        }
        src++;
    }
    src = src_head;

    int *ans = (int *)calloc(count_comma, sizeof(int));
    if (ans == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    for (i = 0; i < count_comma; i++) {
        *(ans + i) = int(get_Number(src));
        src = cut(src);
    }
    return ans;
}

// Another constuctor. take care.
Matrix *get_Matrix(char *string) {
    Matrix *ans = (Matrix *)calloc(1, sizeof(Matrix));
    if (ans == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    char *src = clean(string);
    char *src_head = src;

    int count_semicolon = 0;
    int column = 0;
    while (*src != '\0') {
        if (*src == ';') {
            count_semicolon += 1;
        }
        src++;
    }
    src = src_head;
    while (*src != ';') {
        if (*src == ',') {
            column += 1;
        }
        src++;
    }
    src = src_head;
    ans->low_level_array = get_Vector(src);
    ans->n_row = count_semicolon;
    ans->n_column = column + 1;
    return ans;
}

Dynamic_Array *get_Dynamic_Array(char *string) {
    // get a dynamic array from keyboard input.
    Dynamic_Array *ans = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    if (ans == NULL) {
        printf("fatal error: FUNCTION calloc can't get memory.\n");
        return NULL;
    }
    Matrix *tmp = get_Matrix(string);
    ans->A = tmp->low_level_array;
    ans->n = tmp->n_column  * tmp->n_row;
    ans->capacity = 2 * ans->n;
    return ans;
}

/*
* Copyright (c) 2018, Liu Peng, School of Mathematics and Statistics, YNU
* Apache License.
*
* 文件名称：Source.cpp
* 文件标识：见配置管理计划书
* 摘 要：Prim算法
*
* 当前版本：1.0
* 作 者：刘鹏
* 创建日期：2018年3月14日
* 完成日期：2018年6月25日
*
* 取代版本：
* 原作者 ：刘鹏
* 完成日期：
*/

/*
* A function like division which can execuate with some conditions.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// The following type is a container for creating a stack.
typedef struct char_LinkedList {
    char_LinkedList *head;
    char elements;          // partition must be integer less than 10
    int times;              // container
    char_LinkedList *next;
}char_LinkedList;

typedef struct Dynamic_Array {
    double *A;              // low-level array
    int capacity;           // the capacity
    int n;                  // used room
}Dynamic_Array;

typedef struct Div {
    double up;
    double down;
    double value;
    char state[10];         // NaN or Negative or Normal
}Div;

typedef struct Div_Dynamic_Array {
    Div *A;                 // 底层结构体数组的头指针，不能动！
    int capacity;           // 底层结构体数组的容量
    int n;                  // 底层数组的占用量
}Div_Dynamic_Array;

void Div_Resize(Div_Dynamic_Array *D) {
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

void Div_Append(Div_Dynamic_Array *D, Div e) {
    if (D->n == D->capacity) {
        Div_Resize(D);
    }
    (D->A + D->n)->up = e.up;
    (D->A + D->n)->down = e.down;
    (D->A + D->n)->value = e.value;
    strcpy((D->A + D->n)->state, e.state);
    D->n += 1;
    //int i;
    //for (i = 0; i <= D->n; i++) {
    //  printf("%s\t", (D->A + i)->state);
    //}
    //printf("\n");
}

void Div_print(Div_Dynamic_Array *d) {
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

void Div_onArray(Dynamic_Array *a, Dynamic_Array *b, Div_Dynamic_Array *ans) {
    if (a->n != b->n) {
        printf("length should be the same.");
        return;
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
            Div_Append(ans, tmp);
        }
        else {
            if (*(b->A + i) < 0.) {
                Div tmp;
                tmp.up = *(a->A + i);
                tmp.down = *(b->A + i);
                tmp.value = tmp.up / tmp.down;
                char c[] = "Negative";
                strcpy(tmp.state, c);
                Div_Append(ans, tmp);
            }
            else {
                Div tmp;
                tmp.up = *(a->A + i);
                tmp.down = *(b->A + i);
                tmp.value = tmp.up / tmp.down;
                char c[] = "Normal";
                strcpy(tmp.state, c);
                Div_Append(ans, tmp);
            }
        }
    }
}

// output a Double array
void print(int n, Dynamic_Array *d) {
    printf(/* "argument %d is \n*/"(");
    int i;
    for (i = 0; i < d->n - 1; i++) {
        printf("%2.2f, ", *(d->A + i));
    }
    printf("%2.2f", *(d->A + i));
    printf(")\n\n");
}

// Output a double-array with integer format
void print_int(int n, Dynamic_Array *d) {
    printf(/* "argument %d is \n*/"(");
    int i;
    for (i = 0; i < d->n - 1; i++) {
        printf("%2.0f, ", *(d->A + i));
    }
    printf("%2.0f", *(d->A + i));
    printf(")\n\n");
}

void Resize(Dynamic_Array *D) {
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

void Append(Dynamic_Array *D, double e) {
    if (D->n == D->capacity) {
        Resize(D);
    }
    *(D->A + D->n) = e;
    D->n += 1;
}

Dynamic_Array *Quick_sort(Dynamic_Array *a) {

    Dynamic_Array *less = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    less->A = (double *)calloc(1, sizeof(double));
    if (!less) {
        printf("Can't get memory!");
        return NULL;
    }
    less->capacity = 1;
    less->n = 0;

    Dynamic_Array *more = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    more->A = (double *)calloc(1, sizeof(double));
    if (!more) {
        printf("Can't get memory!");
        return NULL;
    }
    more->capacity = 1;
    more->n = 0;

    Dynamic_Array *eq = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    eq->A = (double *)calloc(1, sizeof(double));
    if (!eq) {
        printf("Can't get memory!");
        return NULL;
    }
    eq->capacity = 1;
    eq->n = 0;

    int i;
    if (a->n <= 1) {
        return a;
    }
    else {
        for (i = 0; i < a->n; i++) {
            double pivot = *(a->A);
            if (*(a->A + i) > pivot) {
                Append(more, *(a->A + i));
            }
            else {
                if (*(a->A + i) < pivot) {
                    Append(less, *(a->A + i));
                }
                else {
                    Append(eq, *(a->A + i));
                }
            }
        }
    }
    less = Quick_sort(less);
    more = Quick_sort(more);
    for (i = 0; i < eq->n; i++) {
        Append(less, *(eq->A + i));
    }
    for (i = 0; i < more->n; i++) {
        Append(less, *(more->A + i));
    }
    return less;
}

void find(Div_Dynamic_Array *a) {

    Dynamic_Array *c = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    Dynamic_Array *d = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    c->A = (double *)calloc(a->n, sizeof(double));
    if (c == NULL || d == NULL || c->A == NULL) {
        printf("Can't get memory!\n");
        return;
    }
    c->capacity = a->n;
    c->n = 0;

    int i = 0;
    for (i = 0; i < a->n; i++) {

        // denominator is legal
        if (!strcmp((a->A + i)->state, "Normal")) {
            Append(c, (a->A + i)->value);
        }
    }
    d = Quick_sort(c);

    double pivot = *(d->A + 0);
    Dynamic_Array *tmp = (Dynamic_Array *)calloc(1, sizeof(Dynamic_Array));
    tmp->A = (double *)calloc(1, sizeof(double));
    if (tmp == NULL || tmp->A == NULL) {
        printf("Can't get memory!\n");
        return;
    }
    tmp->capacity = 1;
    tmp->n = 0;
    for (i = 0; i < a->n; i++) {
        if (!strcmp((a->A + i)->state, "Normal") && (a->A + i)->value == pivot) {
            Append(tmp, ++i);
        }
    }
    if (tmp->n == 0) {
        printf("Sorry, no minimal value.\n");
        return;
    }
    printf("Minimal Value is %2.2f , position is ", pivot);
    print_int(tmp->n, tmp);
}

// Get rid of the useless blank characters.
char *clean(char *string) {
    char *head = string;
    int count_space = 0;
    while (*string == ' ' && *string != '\0') {
        count_space += 1;
        string += 1;
    }
    string = head;

    int len = 1;
    while (*string != '\0') {
        len += 1;
        string++;
    }
    string = head;

    char *ans = (char *)calloc(len - count_space, sizeof(char));
    if (ans == NULL) {
        printf("Can't get memory!\n");
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
    ans = ans_head;
    string = head;

    ans = ans + 1;
    char *tmp;
    for (tmp = ans; *tmp != '\0'; tmp++) {
        if (*(tmp + 1) == '\0') {
            *tmp = ',';
        }
    }
    return ans;
}

char *cut(char *string) {
    while (*string != ',') {
        if (*string == '\0') {
            return NULL;
        }
        string++;
    }
    return ++string;
}

// Put an new element into the stack
double get_Number(char *string) {
    if (*string == '\0') {
        return NULL;
    }
    double ans = 0.;
    if (*string == '\0') {
        return NULL;
    }
    if (*string != '-') {
        char_LinkedList *work = (char_LinkedList *)malloc(sizeof(char_LinkedList));
        if (work == NULL) {
            printf("Can't get memory!\n");
            return 0;
        }
        // container

        char_LinkedList *head = work;
        int i = 1;
        while (*string != ',') {
            work->elements = *string;
            work->times = i;
            work->next = (char_LinkedList *)malloc(sizeof(char_LinkedList));    // malloc
            if (work->next == NULL) {
                printf("Can't get memory!\n");
                return 0.;
            }
            work = work->next;                                                  // move
            work->elements = NULL;
            work->times = NULL;
            string++;
            i++;
        }

        work->elements = *string;
        work->times = NULL;

        string++;

        work = head;
        int dot = 1;
        int comma = 1;
        int dot_index = NULL;
        while (work->elements != ',') {
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

        while (work->elements != ',') {
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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("This function needs and only needs 2 arguments.\n");
        return 0;
    }

    char *string_1 = *(argv + 1);
    char *string_2 = *(argv + 2);

    //char string_1_tmp[] = "( -3.14,20 ,-256, 0 ,6,5,12121,4588, 89)";
    //char *string_1 = string_1_tmp;

    //char string_2_tmp[] = "(3.14, -1, 256,3.2222,2,0,5633.2,168,78)";
    //char *string_2 = string_2_tmp;

    string_1 = clean(string_1);
    string_2 = clean(string_2);

    Dynamic_Array c_1, c_2;
    c_1.A = (double *)malloc(sizeof(double));
    if (c_1.A == NULL) {
        printf("Can't get memory!\n");
        return 0;
    }
    c_1.capacity = 1;
    c_1.n = 0;

    c_2.A = (double *)malloc(sizeof(double));
    if (c_2.A == NULL) {
        printf("Can't get memory!\n");
        return 0;
    }
    c_2.capacity = 1;
    c_2.n = 0;

    while (*string_1 != '\0') {
        Append(&c_1, get_Number(string_1));
        string_1 = cut(string_1);
    }

    while (*string_2 != '\0') {
        Append(&c_2, get_Number(string_2));
        string_2 = cut(string_2);
    }
    c_1.n -= 1;
    c_2.n -= 1;

    Div_Dynamic_Array ans;
    ans.A = (Div *)malloc(sizeof(Div));
    if (ans.A == NULL) {
        printf("Can't get memory!\n");
        return 0;
    }
    ans.capacity = 1;
    ans.n = 0;

    printf("argument 1 is\n");
    print(1, &c_1);
    printf("argument 2 is\n");
    print(2, &c_2);
    Div_onArray(&c_1, &c_2, &ans);
    Div_print(&ans);
    find(&ans);

    //system("pause");
    return 0;
}
/*
* Copyright (c) 2018, Liu Peng, School of Mathematics and Statistics, YNU
* Apache License.
*
* 文件名称：Source.cpp
* 文件标识：见配置管理计划书
* 摘 要：对一个仅有一个约束的线性规划问题用遍历法求解。
*
* 当前版本：1.0
* 作 者：刘鹏
* 创建日期：2018年6月25日
* 完成日期：2018年7月07日
*
* 取代版本：
* 原作者 ：刘鹏
* 完成日期：
*/

/*
* A function can solve a simple LP problem with only one
* condition.
*/

#include<stdio.h>
#include<stdlib.h>

#define INFINITY -1

int main(int argc, char *argv[]) {

    double A[] = { 1, 2 };   // x + 2y = b
    double b = 3;
    double c[] = { 1, 1 };

    int i;
    for (i = 0; i < 2; i++) {
        if (A[i] == 0 && c[i] != 0) {
            return INFINITY;
        }
    }

    double d[] = { (b * c[0]) / (A[0]), (b * c[1]) / (A[1]) };     
    // generate divisions

    if (d[0] > d[1]) {      // sort
        printf("x = (%2.0f, 0)\nMAX z = %2.0f\n", d[0] / c[0], d[0]);
    }
    else {
        printf("x = (0, %2.0f)\n, MAX z = %2.0f\n", d[1] / c[1], d[1]);
    }
    return 0;
}

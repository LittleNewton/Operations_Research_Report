/*
* Copyright (c) 2018, Liu Peng, School of Mathematics and Statistics, YNU
* Apache License.
*
* 文件名称：Source.cpp
* 文件标识：见配置管理计划书
* 摘 要：测试Prim算法
*
* 当前版本：1.0
* 作 者：刘鹏，littleNewton6@outlook.com
* 创建日期：Thu Apr 26 22 : 07 : 06 2018
* 完成日期：2018年6月日
*
* 取代版本：0.9
* 原作者 ：刘鹏
* 完成日期：
*/

/*
* A unit test and example of how to use the dual-simplex method
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Shell_Reader.h"
#include "Matrix_Operation.h"
#include "Dynamic_Array.h"
#include "Divide.h"
#include "Simplex.h"
#include "ASCII_Table.h"

int main(int argc, char *argv[]) {

    //if (argc != 5) {
    //    printf("This function needs and only needs 4 arguments.\n");
    //    return 0;
    //}

    //char *c1 = *(argv + 1);
    //char *c2 = *(argv + 2);
    //char  *A = *(argv + 3);
    //char  *b = *(argv + 4);
    //Simplex_Tableau *S = Simplex_Tableau_init(c1, A, b);
    //dual_Simplex(S, c2);

    char c1[] = "(0, 0, 0, -1, 0, -1)";
    char c2[] = "(-0.4, -0.5, 0, 0, 0, 0)";
    char  A[] = "(0.3,0.1,1,0,0,0;0.5,0.5,0,1,0,0;0.6,0.4,0,0,-1,1)";
    char  b[] = "(2.7, 6, 6)";
    Simplex_Tableau *S = Simplex_Tableau_init(c1, A, b);
    dual_Simplex(S, c2);

    //char c1[] = "(3,1,0,0,0)";
    //char  A[] = "(2,1,-1,1,0; 1,1,0,0,1)";
    //char  b[] = "(2, 2)";
    //Simplex_Tableau *S = Simplex_Tableau_init(c1, A, b);
    //Simplex(S);

    system("pause");
    return 0;
}

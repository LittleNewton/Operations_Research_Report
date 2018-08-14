# 实验No.02 ```2018-03-28```

## 1. Introduction

实现一个简单的线性规划问题的求解。

求 MAX(z), z = **Cx**, **x** = (x1, x2, ..., xn)

s.t. a1\*x1 + a2\*x2 + ... + an\*xn = b

其中**x**为正。

作为**单纯形算法**的一个简单应用，我将本实验的主要部分放在证明与理解上，如果还有时间，会把这个程序在尽可能靠前的提交里写得尽可能复杂一点。

## 2. 单纯形方法介绍

单纯形算法解决此问题比较简单。现在分析一下单纯形算法的使用方法。

### 2.1 约束变量与目标函数

目标函数是一个很正常的线性函数z = **Cx**，dim(**x**) = m <= n，在这里我们需要明确地知道，目标函数里面有m个变量。而这个时候，约束条件中至少有这m个变量，因为一旦目标函数中出现我们不能在约束方程（或约束不等式）中找到的变量，那么就相当于有未知信息存在，整个规划问题根本就不能解决，设计人员需要进一步收集信息。

> 举个简单的例子，如果一个数据采集者需要采集化疗的放射量，放射口有两处，每个口的放射强度分别为x1和x2，目标函数为有关x1和x2的线性函数，如果求目标函数的最大值，而约束中根本没有提及x2，只说了x1需要的约束，这个时候就不能进行规划，因为我们缺乏x2处的信息。反之，如果两处的信息约束都知道了，那么这个线性规划才有可能进行下去。

### 2.2 所有类型约束的化归

```
- 1) 所有的变量都取正值
:如果变量可以取非正值，那也可以在界定了下界之后通过平移变换获得一个正的变量；全部为正与全为负是对称的

- 2) 所有的<=约束都不用动
:此举是为了可以从0开始取值

- 3) <=约束的右端项都为正值
:此举是为了可以从0开始取值

- 4) 遇到了=约束要添加一个松弛变量
:此举是为了可以从0开始取值，因为等式约束直接取0必然不可以，这与3)矛盾。添加了人工变量之后就可以令原来的变量都为0，非零部分由松弛变量支撑

- 5) 遇到了>=约束要先减去一个剩余变量
:此举是为了使之变成=类型的约束，然后再用4)的操作

- 6) 价值向量可以有负元素
:经过了前面的操作，目标函数中的变量都可以从0开始取，搜索时，从原点这个可行解开始，只选参数大于零的变量并令其增长。
```

> 单纯形法的前提条件非常重要，这个前提直接关系到了能不能解除答案。比如说**C**被认为是所有的系数都比0大，这样一来就简单了很多，比如可以直接进行最大增量参数选择（也就是找到最大的**C**使得增长速度最快）。这里有个很简单的问题，是否是说，增长率最大的那个方向一定是最优的方向呢？

这个问题必须解答。不过在知道答案之前，**这个是不可能透过任何方法提前知道到底这一步怎么走。所以直觉就是选择系数最大的那一个。**

## 3. 代码使用说明

打开PowerShell，切换到可执行文件所在的目录，输入下面的demo

```PowerShell
Power Shell> Simplex.exe "(c1, c2, c3)" "(a11, a12, a13, a14; a21, a22, a23, a24)" "(b1, b2)"
Power Shell> Optimal solution found.
             x = 3 * 1
                x1
                x2
                x3
```

如此就可以调用该函数。
# LED流水灯

## 原理


![syled](/doc/image/sy_led1.png)

## c语言知识

- define的使用

```c
#define A P0

//注意后面不用加分号
```

- 循环左移右移函数

```c
//注意要引入这个头文件
#include <instrins.h>

//循环左移函数，a是移动的值，b是移动的位数
_crol_(a,b);

//循环右移函数
_cror_(a,b);

```


## 实验图
![syled2](/src/实验3：LED流水灯/接线图.JPG)

## 实验代码

[Jump](/src/实验3：LED流水灯/程序/main.c)
# LED闪烁

## 原理

一段时间给LED输出高电平，一段时间给LED输出低电平

![syled](image/sy_led1.png)

## c语言知识

- typedef的使用

```c
#typedef usigned char u8;

#typedef usigned char u16;

//这样使用u8和u16就更加方便地定义一个或者两个字节
```

- 延时函数

```c
void delay(u16 i){ 
    while(i--); //每次循环大约10us
}
```


## 试验图
![syled2](/src/实验2：LED闪烁/接线图.JPG)

## 试验代码

[jump](/src/实验2：LED闪烁/程序/main.c)
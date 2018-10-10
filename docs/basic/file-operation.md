## 文件的概念

文件是根据特定的目的而收集在一起的有关数据的集合。C/C++ 把每一个文件都看成是一个有序的字节流，每个文件都是以**文件结束标志**（EOF）结束，如果要操作某个文件，程序应该首先打开该文件，每当一个文件被打开后（请记得关闭打开的文件），该文件就和一个流关联起来，这里的流实际上是一个字节序列。  
C/C++ 将文件分为文本文件和二进制文件。文本文件就是简单的文本文件（重点），另外二进制文件就是特殊格式的文件或者可执行代码文件等。

## 文件的操作步骤  
 1、打开文件，将文件指针指向文件，决定打开文件类型；  
 2、对文件进行读、写操作（比赛中主要用到的操作，其他一些操作暂时不写）；  
 3、在使用完文件后，关闭文件。  

## `freopen` 函数

 [命令格式]  

    FILE * freopen(const char * filename, const char * mode,
      FILE * stream);

[参数说明]
`filename`: 要打开的文件名  
`mode`: 文件打开的模式
`stream`: 文件指针，通常使用标准文件流（`stdin/stdout/stderr`)  
[使用方法]
读入文件内容：

    freopen("data.in","r",stdin); //data.in 就是读取的文件名，要和可执行文件放在同一目录下

输出到文件：

    freopen("data.out","w",stdout); //data.out 就是输出文件的文件名，和可执行文件在同一目录下

关闭标准输入 \\ 输出流  

    fclose(stdin);
    fclose(stdout);

## 模板

    #include <cstdio>
    #include <iostream>
    int main(void)
    {
      freopen("data.in","r",stdin);
      freopen("data.out","w",stdout);
      /*
      中间的代码不需要改变，直接使用 cin 和 cout 即可
      */
      fclose(stdin);
      fclose(stdout);
      return 0;
    }

参考书目：信息学奥赛一本通

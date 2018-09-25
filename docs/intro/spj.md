一道题如果有多组解，我们就需要一个程序来判断答案合法性，这便是 Special Judge (spj)，又常被称作 checker，下面介绍部分评测工具 /OJ 的 spj 编写方法。

???+ warning
    spj 还应当判断文件尾是否有多余内容，及输出格式是否正确（如题目要求数字间用一个空格隔开，而选手却使用了换行）。但是，目前前者几乎只有 Testlib 做到了这一点，而后者恐怕无人做到。

    浮点数时应注意 nan，不合理的判断方式会导致输出 nan 即可 AC。

以下均使用 C++，以 “要求标准答案与选手答案差值小于 1e-3，文件名为 num” 为例。

## Testlib

[Testlib](https://codeforces.com/testlib) 是一个强大的算法竞赛题目辅助系统，只需要在程序中引入 [testlib.h](https://github.com/MikeMirzayanov/testlib/blob/master/testlib.h) 头文件即可使用。用法详见 [Testlib](/intro/testlib) 页面。

使用 Testlib 编写 spj 的好处为我们不再需要判断文件尾的多余内容，其会帮助我们自动判断，也无需担忧 nan。

可以 / 必须使用 Testlib 做 spj 的 OJ：洛谷、UOJ、LibreOJ(SYZOJ 2)（需要修改版的 Testlib）......

SYZOJ 2 所需的修改版 Testlib 可以在[这里](https://pastebin.com/3GANXMG7)获取到，感谢 [cyand1317](https://loj.ac/article/124)。

本地评测器都可以使用 Testlib，但需要按照其格式修改 Testlib。

```cpp
#include <testlib.h>
#include <cmath>
int main(int argc, char *argv[]){
    /*
     * inf：输入
     * ouf：选手输出
     * ans：标准输出
     */
    registerTestlibCmd(argc, argv);
    double pans=ouf.readDouble(), jans=ans.readDouble();
    if(abs(pans - jans) < 1e-3) quitf(_wa, "Too big or too small, expected %f, found %f", jans, pans);
    else quitf(_ok, "Good job");
}
```

## Lemon

```cpp
#include <cstdio>
#include <cmath>
int main(int argc,char *argv[]){
    /*
     * argv[1]：输入
     * argv[2]：选手输出
     * argv[3]：标准输出
     * argv[4]：单个测试点分值
     * argv[5]：输出最终得分
     * argv[6]：输出错误报告
     */
    FILE* fin = fopen(argv[1], "r");
	FILE* fout = fopen(argv[2], "r");
	FILE* fstd = fopen(argv[3], "r");
	FILE* fscore = fopen(argv[5], "w");
	FILE* freport = fopen(argv[6], "w");
	double pans, jans;
	fscanf(fout, "%lf", &pans);
	fscanf(fstd, "%lf", &jans);
	if(abs(pans - jans) < 1e-3){
		fprintf(fscore, "%s", argv[4]);
		fprintf(freport, "Too big or too small, expected %f, found %f", jans, pans);
	}else{
		fprintf(fscore, "%d", 0);
		fprintf(freport, "Good job");
	}
}
```

## Cena

```cpp
#include <cstdio>
#include <cmath>
int main(int argc,char *argv[]){
    /*
     * FILENAME.in：输入
     * FILENAME.out：选手输出
     * argv[2]：标准输出
     * argv[1]：单个测试点分值
     * score.log：输出最终得分
     * report.log：输出错误报告
     */
    FILE* fin = fopen("num.in", "r");
	FILE* fout = fopen("num.out", "r");
	FILE* fstd = fopen(argv[2], "r");
	FILE* fscore = fopen("score.log", "w");
	FILE* freport = fopen("report.log", "w");
	double pans, jans;
	fscanf(fout, "%lf", &pans);
	fscanf(fstd, "%lf", &jans);
	if(abs(pans - jans) < 1e-3){
		fprintf(fscore, "%s", argv[1]);
		fprintf(freport, "Too big or too small, expected %f, found %f", jans, pans);
	}else{
		fprintf(fscore, "%d", 0);
		fprintf(freport, "Good job");
	}
}
```

## CCR

```cpp
#include <cstdio>
#include <cmath>
int main(int argc,char *argv[]){
    /*
     * stdin：输入
     * argv[3]：选手输出
     * argv[2]：标准输出
     * stdout:L1：输出最终得分比率
     * stdout:L2：输出错误报告
     */
	FILE* fout = fopen(argv[3], "r");
	FILE* fstd = fopen(argv[2], "r");
	double pans, jans;
	fscanf(fout, "%lf", &pans);
	fscanf(fstd, "%lf", &jans);
	if(abs(pans - jans) < 1e-3){
		printf("%d\n", 1);
		printf("Too big or too small, expected %f, found %f", jans, pans);
	}else{
		printf("%d\n", 0);
		printf("Good job");
	}
}
```

## Arbiter

## HUSTOJ

```cpp
#include <cstdio>
#include <cmath>
#define AC 0
#define WA 1
int main(int argc,char *argv[]){
    /*
     * argv[1]：输入
     * argv[3]：选手输出
     * argv[2]：标准输出
     * exit code：返回判断结果
     */
	FILE* fout = fopen(argv[3], "r");
	FILE* fstd = fopen(argv[2], "r");
	double pans, jans;
	fscanf(fout, "%lf", &pans);
	fscanf(fstd, "%lf", &jans);
	if(abs(pans - jans) < 1e-3) return AC;
	else return WA;
}
```

## QDUOJ

QDUOJ 就麻烦一点，因为它的带 spj 的题目没有标准输出，只能把 std 写进 spj 跑出标准输出再判断。

```cpp
#include <cstdio>
#include <cmath>
#define AC 0
#define WA 1
#define ERROR -1
double solve(...){
	// std
}
int main(int argc,char *argv[]){
    /*
     * argv[1]：输入
     * argv[2]：选手输出
     * exit code：返回判断结果
     */
	FILE* fin = fopen(argv[1], "r");
	FILE* fout = fopen(argv[2], "r");
	//读入
	double pans, jans;
	fscanf(fout, "%lf", &pans);
	jans = solve(...);
	if(abs(pans - jans) < 1e-3) return AC;
	else return WA;
}
```

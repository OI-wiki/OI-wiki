author: johnvp22, lr1d

##  `string` 是什么

 `std::string` 是在标准库 `<string>` （注意不是 C 语言中的 `<string.h>` 库）中提供的一个类，本质上是 `std::basic_string<char>` 的别称。

## 为什么要使用 `string` 

在 C 语言中，提供了字符串的操作，但只能通过字符数组的方式来实现字符串。而 `string` 则是一个简单的类，使用简单，在 OI 竞赛中被广泛使用。并且相较于其他 STL 容器， `string` 的常数可以算是非常优秀的，基本与字符数组不相上下。

###  `string` 可以动态分配空间

和许多 STL 容器相同， `string` 能动态分配空间，这使得我们可以直接使用 `std::cin` 来输入，但其速度则同样较慢。这一点也同样让我们不必为内存而烦恼。

###  `string` 重载了加法运算符和比较运算符

 `string` 的加法运算符可以直接拼接两个字符串或一个字符串和一个字符。和 `std::vector` 类似， `string` 重载了比较运算符，同样是按字典序比较的，所以我们可以直接调用 `std::sort` 对若干字符串进行排序。

## 使用方法

下面介绍 `string` 的基本操作，具体可看 [C++ 文档](https://zh.cppreference.com/w/cpp/string/basic_string) 。

### 声明

```cpp
std::string s;
```

### 转 char 数组

在 C 语言里，也有很多字符串的函数，但是它们的参数都是 char 指针类型的，为了方便使用， `string` 有两个成员函数能够将自己转换为 char 指针—— `data()` / `c_str()` （它们几乎是一样的，但最好使用 `c_str()` ，因为 `c_str()` 保证末尾有空字符，而 `data()` 则不保证），如：

```cpp
printf("%s", s);          // 编译错误
printf("%s", s.data());   // 编译通过，但是是 undefined behavior
printf("%s", s.c_str());  // 一定能够正确输出
```

### 获取长度

很多函数都可以返回 string 的长度：

```cpp
printf("s 的长度为 %d", s.size());
printf("s 的长度为 %d", s.length());
printf("s 的长度为 %d", strlen(s.c_str()));
```

???+note "这些函数的复杂度"
     `strlen()` 的复杂度一定是与字符串长度线性相关的。

     `size()` 和 `length()` 的复杂度在 C++98 中没有指定，在 C++11 中被指定为常数复杂度。但在常见的编译器上，即便是 C++98，这两个函数的复杂度也是常数。

### 寻找某字符（串）第一次出现的位置

```cpp
printf("字符 a 在 s 的 %d 位置第一次出现", s.find('a'));
printf("字符串 t 在 s 的 %d 位置第一次出现", s.find(t));
printf("在 s 中自 pos 位置起字符串 t 第一次出现在 %d 位置", s.find(t, pos));
```

### 截取子串

 `substr(pos, len)` ，这个函数的参数是从 `pos` 位置开始截取最多 `len` 个字符（如果从 `pos` 开始的后缀长度不足 `len` 则截取这个后缀）。

```cpp
printf("从这个字符串的第二位开始的最多三个字符构成的子串是 %s",
       s.substr(1, 3).c_str());
```

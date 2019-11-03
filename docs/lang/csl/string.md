author: johnvp22, lr1d

##  `string` 

 `std::string` 是在标准库 `<string>` （注意不是 C 语言中的 `<string.h>` 库）中提供的一个类，在库中的定义为 `basic_string<char>` 。

## 为什么要使用 `string` 

在 C 语言中，提供了字符串的操作，但只能通过字符数组的方式来实现字符串。而 `string` 则是一个简单的类，使用简单，在 OI 竞赛中被广泛使用。并且相较于其他 STL 容器， `string` 的常数可以算是非常优秀的，基本与字符数组不相上下。

####  `string` 可以动态开放空间

和许多 STL 容器相同， `string` 能动态开放空间，这使得我们可以直接使用 `std::cin` 来输入，但其速度则同样较慢。这一点也同样让我们不必为内存而忧愁。

####  `string` 重载了加法运算符和比较运算符

和 `std::vector` 类似， `string` 重载了比较运算符，同样是按字典序比较的，所以我们可以直接调用 `std::sort` 对很多字符串进行排序。 `string` 的加法运算符可以直接拼接两个字符串或一个字符串和一个字符。

###  `string` 操作

下面介绍 `string` 的基本操作，具体可看 [C++ 文档](https://zh.cppreference.com/w/cpp/string/basic_string) 

#### 定义

```cpp
string s;
```

#### 转 char 数组

在 C 语言里，也有很多字符串的函数，但是它们的参数都是 char 指针类型的，所以在 C++ 里有两个函数能够转换 string 为 char 指针——data()/c_str()（它们是一样的）如：

```cpp
printf("%s", s);  //编译错误
```

```cpp
printf("%s", s.data())  //通过
```

#### 大小

好多函数可以返回 string 的长度：

```cpp
printf("string的长度为%d", s.size());
printf("string的长度为%d", strlen(s.data()));
printf("string的长度为%d", s.length());
```

#### 寻找某字符第一次出现的位置

```cpp
printf("字符a在%d位置出现", s.find('a'));
```

#### 截取子串

注意这个函数的参数是从哪个位置后面截几个。

```cpp
printf("这个字符串第1位开始的2个字符构成的子串是%s", s.substr(0, 2).data());
```

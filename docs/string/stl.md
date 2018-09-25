# C / C++ 标准库中的字符串

## C 标准库

C 标准库是在对字符数组进行操作

### strlen

`strlen(str)` ：返回从 `str[0]` 开始直到 `'\0'` 的字符数。注意，未开启 O2 优化时，该操作写在循环条件中复杂度是 $\Theta(N)$ 的。

### printf

`printf("%s", s)`：用 `%s` 来输出一个字符串（字符数组）。

### scanf

`scanf("%s", s)`：用 `%s` 来读入一个字符串（字符数组）。

### sscanf

### sprintf

### strcmp

`strcmp(str1, str2)`：按照字典序比较 `str1 str2` 若 `str1` 字典序小返回负值， 一样返回 0 ，大返回正值 请注意，不要简单的认为只有 `0, 1, -1`  三种，在不同平台下的返回值都遵循正负，但并非都是 `0, 1, -1`

### strcpy

`strcpy(str, src)` : 把 `src` 中的字符复制到 `str` 中， `str` `src` 均为字符数组头指针， 返回值为 `str` 包含空终止符号 `'\0'` 。

### strncpy

`strncpy(str, src, cnt)` ：复制至多 `cnt` 个字符到 `str` 中，若 `src` 终止而数量未达 `cnt` 则写入空字符到 `str` 直至写入总共 `cnt` 个字符。

### strcat

`strcat(str1, str2)` : 将 `str2` 接到 `str1` 的结尾，用 `*str2` 替换 `str1` 末尾的 `'\0'`  返回 `str1` 。

### strstr

## C++ 标准库

C++ 标准库是在对字符串对象进行操作，同时也提供对字符数组的兼容。

### std::string

- 赋值运算符 `=` 右侧可以是 `const string / string / const char*/ char*`
- 访问运算符 `[cur]` 返回 `cur` 位置的引用  
- 访问函数 `data()` 返回一个 `char` 数组的头指针，内容与该 `string` 相同
- 访问函数 `c_str()` 返回一个不可修改的 `char` 数组。
- 容量函数 `size()` 返回字符串字符个数
- 还有一些其他的函数如 `find()` 找到并返回某字符位置。
- `std :: string` 重载了比较逻辑运算符，复杂度是 $\Theta(N)$ 的

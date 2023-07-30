**联合体**（union）在某种程度上是类似 [结构体](./struct.md)（struct）的一种数据结构。

联合体在 2023 年正式被加入 NOI 大纲入门级中。

## 定义联合体

```cpp
union Union {
  int x;
  long long y;
} x;
```

联合体的定义与结构体类似。按照上述定义，`Union` 同样可以当作一种自定义类型使用。名称 `Union` 可以省略。

## 访问/修改成员元素

与结构体类似，同样可以使用 `变量名.成员元素名` 进行访问。

联合体中所有成员 **共用一份空间**，一个联合体所占用的空间大小为其成员中占用空间 **最大的元素** 的大小。当一个元素被赋值，上一次赋值将被覆盖。

## 联合体的妙用

联合体有很多巧妙的用法，下面给出一些例子。

### 联合体查看二进制表示

```cpp
union {
  int n;
  unsigned char bits[4];
} a;

int main() {
  int x;
  scanf("%d", &x);
  a.n = x;
  for (int i = 0; i < 4; i++) cout << bitset<8>(a.bits[i]) << " ";
  return 0;
}
```

使用上面的程序，可以便捷地查看一个 `int` 类型的二进制表示。值得注意的是，输出的结果的字节顺序可能与系统大小端有关。

### 联合体优化短字符串

我们常常使用 [哈希算法](./../string/hash.md) 来判断两个字符串是否相等。

类似地，我们可以使用如下代码来优化短字符串的哈希。

```cpp
union {
  unsigned long long value;
  char str[8];
} a;

int main() {
  scanf("%s", a.str);
  printf("%llu\n", a.value);
  return 0;
}
```

author: shuzhouliu

## 常见的未定义行为

### 局部变量未初始化

???+ warning "示例"
    ```cpp
    int main() {
      int a;
      a++;
      cout << a << endl;
      return 0;
    }
    ```

???+ success "正确的写法"
    ```cpp
    int main() {
      int a = 0;
      a++;
      cout << a << endl;
      return 0;
    }
    ```

此时，$a$ 的值没有被初始化，所以理论上来说可能是任何数。

### 除以 0


???+ warning "示例"
    ```cpp
    int main() {
      int x = rand();
      cout << x / 0 << endl;
      return 0;
    }
    ```

正确的做法：不要除以 0.

### 数组（下标）越界

???+ warning "示例"
    ```cpp
    int h[4];
    
    int main() {
      for (int i = 0; i <= 4; i++) cin >> h[i];
      for (int i = 1; i <= 4; i++) cout << h[i] << endl;
      return 0;
    }
    ```

正确的做法：检查一下自己哪些地方越界了。

???+ success "正确的写法"
    ```cpp
    int h[4];
    
    int main() {
      for (int i = 0; i < 4; i++) cin >> h[i];
      for (int i = 1; i < 4; i++) cout << h[i] << endl;
      return 0;
    }
    ```

### 除 main 外有返回值函数执行至结尾未执行任何 return 语句

???+ warning "示例"
    ```cpp
    bool ok(int x) {
      if (x == 23) return true;
    }
    ```

虽然有一个分支有 `return true`，但是其他分支却没有，这是未定义的。

???+ success "正确的写法"
    ```cpp
    bool ok(int x) {
      if (x == 23) return true;
      return false;
    }
    ```

### 尝试修改字符串字面量

???+ warning "示例"
    ```cpp
    int main() {
      char *p = "OI-wiki";
      p[0] = 'o';
      p[1] = 'i';
      return 0;
    }
    ```

???+ success "正确的写法"
    您可以用 `std::string` 以实现字符串功能：
    
    ```cpp
    int main() {
      string p = "OI-wiki";
      p[0] = 'o';
      p[1] = 'i';
      return 0;
    }
    ```
    
    您也可以使用 `char[]` 以实现字符串功能：
    
    ```cpp
    int main() {
      char p[] = "OI-wiki";
      p[0] = 'o';
      p[1] = 'i';
      return 0;
    }
    ```

### 多次释放同一片内存

???+ warning "示例"
    ```cpp
    int main() {
      int *p = new int;
      delete p;
      delete p;
      return 0;
    }
    ```

解决方法：`erase` 或 `delete` 或 `free` 操作不要多次使用。

???+ success "正确的写法"
    ```cpp
    int main() {
      int *p = new int;
      delete p;
      return 0;
    }
    ```

### 访问空指针

???+ warning "示例"
    ```cpp
    int main() {
      int *p = nullptr;
      printf("%d", *p);
      return 0;
    }
    ```

解决方法：先判断空指针，可以用 `p == nullptr` 或 `!p`。

???+ success "正确的写法"
    ```cpp
    int main() {
      int *p = ...;  // 非空值
      printf("%d", *p);
      return 0;
    }
    ```

### 有符号数溢出

???+ warning "示例"
    ```cpp
    bool dummy(int x) { return x + 1 > x; }
    
    int main() {
      cout << boolalpha << dummy(INT_MAX) << endl;
      return 0;
    }
    ```

正常输出应当是 `true`，但是在 `INT_MAX` 作为参数时输出 `false`，这时称为 `integer overflow`。

解决方案：使用更大的数据类型（例如 `long long` 或 `__int128`），或判断溢出。

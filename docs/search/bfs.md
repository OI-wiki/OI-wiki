bfs 全称是 Breadth First Search。

是一种图的遍历算法。

所谓宽度优先。就是每次都尝试访问同一层的节点。
如果同一层都访问完了，再访问下一层。

## 实现

伪代码：

```
bfs(s) {
  q = new queue()
  q.push(s)), visited[s] = true
  while (!q.empty()) {
    u = q.pop()
    for each edge(u, v) {
      if (!visited[v]) {
        q.push(v)
        visited[v] = true
      }
    }
  }
}
```

C++：

```c++
void bfs(int u) {
  while (!Q.empty()) Q.pop();
  Q.push(u); vis[u] = 1;
  while (!Q.empty()) {
    u = Q.pop() {
      for (int i = head[u]; i; i = e[i].x) {
        if (!vis[ e[i].t ]) {
          Q.push(e[i].t);
          vis[ e[i].t ] = 1;
        }
      }
    }
  }
}
```


时间复杂度 $O(n + m)$

空间复杂度 $O(n)$ （vis 数组和队列）

## open-closed 表

在实现 bfs 的时候，我们把未被访问过的节点放在一个称为 open 的容器中，而把已经访问过了的节点放在 closed 容器中。

## [在树 / 图上 bfs](/graph/traverse)
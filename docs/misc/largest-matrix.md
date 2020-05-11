author: mwsht

## 适用问题

给定一个 $n\times m$ 的 01 矩阵 $a$ ，求其面积最大的子矩阵，使得这个子矩阵中的每一位的值都为 $0$ 。

## 悬线法

悬线法可以在 $O(nm)$ 的时间复杂度内解决以上问题。

### 悬线的定义

在讲解中，我们将值为 $1$ 的点称为“障碍点”。

悬线，就是一条竖线，这条竖线要满足其上端点在矩形的上边界或其上端点的上面是障碍点。

我们枚举每个点的悬线，求出其最多能向左和向右扩展到何处，取最大值，就能求出最大子矩阵了。

### 一些定义

定义 $up[i][j]$ 为矩阵上的点 $(i,j)$ 向上的悬线长度；

定义 $lft[i][j]$ 为点 $(i,j)$ 向左最多扩展而不会碰到障碍点的长度；

对应的，定义 $rgt[i][j]$ 为点 $(i,j)$ 向右最多扩展而不会碰到障碍点的长度。

### 用悬线法解决最大子矩阵问题

我们可以在 $O(nm)$ 的时间复杂度内预处理出 $up,lft,rgt$ 数组的值。

但是，仅仅做出预处理是不够的。我们发现，一条悬线向左扩展的最长距离还取决于 $lft[i-up[i][j]+1][j],lft[i-up[i][j]+2][j],...,lft[i-1][j]$ ，向右同理。所以，我们在枚举时对 $lft[i][j]$ 和 $rgt[i][j]$ 进行更新，使 $lft[i][j]=\max\{lft[i][j],lft[i-1][j]\},rgt[i][j]=\min\{rgt[i][j],rgt[i-1][j]\}$ 。

注意，我们在遇到障碍点的时候，不对 $lft$ 和 $rgt$ 值进行更新，因为障碍点使悬线的起点有所不同。

### 代码展示

以 LeetCode 85/221 为例

```cpp
int maximalRectangle(vector<vector<char>>& matrix) {
  int ans = 0;
  int n = matrix.size();
  if (n == 0) return 0;
  int m = matrix[0].size();
  if (m == 0) return 0;
  vector<vector<int>> lft(n, vector<int>(m, 0));
  vector<vector<int>> rgt(n, vector<int>(m, 0));
  vector<vector<int>> up(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < m; j++) {
      if (matrix[i][j] == '1' && matrix[i][j - 1] == '1')
        lft[i][j] = lft[i][j - 1] + 1;
    }
    for (int j = m - 1; j > 0; j--) {
      if (matrix[i][j - 1] == '1' && matrix[i][j] == '1')
        rgt[i][j - 1] = rgt[i][j] + 1;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (matrix[i][j] == '1') {
        if (i >= 1 && matrix[i - 1][j] == '1') {
          lft[i][j] = min(lft[i][j], lft[i - 1][j]);
          rgt[i][j] = min(rgt[i][j], rgt[i - 1][j]);
          up[i][j] = up[i - 1][j] + 1;
        } else {
          up[i][j] = 1;
        }
      }
      ans = max(ans, (rgt[i][j] + lft[i][j] + 1) * up[i][j]);
    }
  }
  return ans;
}
```

如果是最大正方形，改成

```cpp
ans = max(ans, min((rgt[i][j] + lft[i][j] + 1), up[i][j]));
return ans * ans;
```

最后的返回值即为所求面积。

## 习题

 [luogu P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147) 

 [luogu P1578 奶牛浴场](https://www.luogu.com.cn/problem/P1578) 

 [「ZJOI2007」棋盘制作](https://www.luogu.com.cn/problem/P1169) 

 [LeetCode 85. 最大矩形](https://leetcode-cn.com/problems/maximal-rectangle/) 

 [LeetCode 221. 最大正方形](https://leetcode-cn.com/problems/maximal-square/) 

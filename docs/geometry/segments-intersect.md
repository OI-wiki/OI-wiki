给定两个线段 $(a,b)$ ， $(c,d)$ 。判断它们是否相交。显然我们可以通过直接找交点来判断它们是否相交，但是这个方法对于具有整数坐标的线段，无法以整数形式完成。而下面所讲的方法可以以整数形式完成。

## 算法

首先，考虑线段在同一直线上的情况。在这种情况下，只需要检查它们在 $Ox$ 和 $Oy$ 上的投影是否相交即可。而线段不在同一直线上时， $a$ 和 $b$ 不得位于线 $(c,d)$ 同一侧， $c$ 和 $d$ 不得位于线 $(a,b)$ 的同一侧。我们可以通过几对坐标的叉乘进行上述检查。

## 算法实现

一下给的算法是整点的实现。当然，它也很容易修改为 `double` 类型的实现。

```c
struct pt {
    long long x, y;
    pt() {}
    pt(long long _x, long long _y) : x(_x), y(_y) {}
    pt operator-(const pt& p) const { return pt(x - p.x, y - p.y); }
    long long cross(const pt& p) const { return x * p.y - y * p.x; }
    long long cross(const pt& a, const pt& b) const { return (a - *this).cross(b - *this); }
};

int sgn(const long long& x) { return x >= 0 ? x ? 1 : 0 : -1; }

bool inter1(long long a, long long b, long long c, long long d) {
    if (a > b)
        swap(a, b);
    if (c > d)
        swap(c, d);
    return max(a, c) <= min(b, d);
}

bool check_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0)
        return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) &&
           sgn(c.cross(d, a)) != sgn(c.cross(d, b));
```

* * *

 **本页面部分内容译自博文 [Проверить, пересекаются ли два сегмента](https://github.com/e-maxx-eng/e-maxx-eng/blob/a080066d3aefbb0176e36eb5c9b280e9e916a98b/src/geometry/check-segments-intersection.md) 与其英文翻译版 [Check if two segments intersect](https://cp-algorithms.com/geometry/check-segments-intersection.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 

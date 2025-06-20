class Edge:
    def __init__(self, u, v, w):
        self.u = u
        self.v = v
        self.w = w


fa = [0] * 1010  # 定义父亲
g = []


def add(u, v, w):
    g.append(Edge(u, v, w))


# 标准并查集
def findroot(x):
    if fa[x] == x:
        return x
    fa[x] = findroot(fa[x])
    return fa[x]


def Merge(x, y):
    x = findroot(x)
    y = findroot(y)
    fa[x] = y


# Kruskal 算法
def kruskal():
    tot = 0  # 存已选了的边数
    ans = 0  # 存总的代价
    for e in g:
        x = findroot(e.u)
        y = findroot(e.v)
        if x != y:  # 如果父亲不一样
            fa[x] = y  # 合并
            tot += 1  # 边数增加
            ans += e.w  # 代价增加
        if tot >= (n - k):  # 检查选的边数是否满足 k 个棉花糖
            print(ans)
            return
    print("No Answer")  # 无法连成


if __name__ == "__main__":
    n, m, k = map(int, input().split())
    for i in range(1, n + 1):  # 初始化
        fa[i] = i
    for i in range(1, m + 1):
        u, v, w = map(int, input().split())
        add(u, v, w)  # 添加边
    g.sort(key=lambda edge: edge.w)  # 先按边权排序
    kruskal()

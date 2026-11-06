# Sample provenance: https://www.luogu.com.cn/problem/P3371 and the same regression fixtures as the C++ version.
n, m, source = map(int, input().split())


# --8<-- [start:core]
class Edge:
    def __init__(self, u=0, v=0, w=0):
        self.u = u
        self.v = v
        self.w = w


INF = float("inf")
edge = []


def bellmanford(n, s):
    global dis
    dis = [INF] * (n + 1)
    dis[s] = 0
    for i in range(1, n + 1):
        flag = False
        for e in edge:
            u, v, w = e.u, e.v, e.w
            if dis[u] == INF:
                continue
            # 无穷大与常数加减仍然为无穷大
            # 因此最短路长度为 INF 的点引出的边不可能发生松弛操作
            if dis[v] > dis[u] + w:
                dis[v] = dis[u] + w
                flag = True
        # 没有可以松弛的边时就停止算法
        if not flag:
            break
    # 第 n 轮循环仍然可以松弛时说明 s 点可以抵达一个负环
    return flag


# --8<-- [end:core]

for _ in range(m):
    u, v, w = map(int, input().split())
    edge.append(Edge(u, v, w))
negative = bellmanford(n, source)
if negative:
    print("NEGATIVE CYCLE")
else:
    print(*(dis[u] if dis[u] != float("inf") else 2147483647 for u in range(1, n + 1)))

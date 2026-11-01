import sys
import copy
import copy

# --8<-- [start:core]
# 定义一个足够大的值表示无穷大
INF = sys.maxsize


def get_path(i, j, pos, path, cnt):
    """
    递归地获取从节点 i 到节点 j 的最短路径上的中间节点．

    Args:
        i (int): 起始节点 (0-based index).
        j (int): 结束节点 (0-based index).
        pos (list[list[int]]): 记录最短路径中间节点的矩阵. pos[i][j] = k 表示从 i 到 j 的最短路径经过 k.
        path (list[int]): 存储路径节点的列表 (使用 0-based index).
        cnt (int): 当前路径节点的数量.

    Returns:
        int: 更新后的路径节点数量.
    """
    # 如果 pos[i][j] 为 -1，表示 i 到 j 没有中间节点
    if pos[i][j] == -1:
        return cnt

    # 获取中间节点 k
    k = pos[i][j]
    # 递归获取 i 到 k 的路径
    cnt = get_path(i, k, pos, path, cnt)
    # 将中间节点 k 加入路径
    path[cnt] = k
    cnt += 1
    # 递归获取 k 到 j 的路径
    cnt = get_path(k, j, pos, path, cnt)
    return cnt


def find_minimum_cycle_undirected(n, edges):
    """
    使用 Floyd-Warshall 算法查找无向图中的最小环．

    Args:
        n (int): 图的节点数 (1 到 n).
        edges (list[tuple]): 边的列表，每个元素是 (u, v, w)，表示节点 u 和 v 之间有一条权重为 w 的边．
                             节点索引是 1 到 n．

    Returns:
        tuple: 包含最小环的长度和路径．
               如果不存在环，返回 (INF, []).
               路径是一个节点索引列表 (1-based index)．
    """
    # 内部使用 0-based indexing
    N = n
    # 初始化邻接矩阵 g，表示原始边的权重
    g = [[INF for _ in range(N)] for _ in range(N)]
    # 初始化最短路矩阵 dis，开始时与 g 相同
    dis = [[INF for _ in range(N)] for _ in range(N)]
    # 初始化 pos 矩阵，记录最短路径的中间节点
    pos = [[-1 for _ in range(N)] for _ in range(N)]

    # 初始化对角线为 0 (节点到自身的距离)
    for i in range(N):
        g[i][i] = 0
        dis[i][i] = 0

    # 根据输入的边构建邻接矩阵 (无向图)
    for u, v, w in edges:
        # 将 1-based 索引转换为 0-based
        u -= 1
        v -= 1
        # 对于无向图，边是双向的
        g[u][v] = min(g[u][v], w)
        g[v][u] = min(g[v][u], w)
        dis[u][v] = min(dis[u][v], w)
        dis[v][u] = min(dis[v][u], w)

    # 初始化最小环长度为无穷大
    min_cycle_len = INF
    # 初始化最小环路径
    min_cycle_path = []

    # Floyd-Warshall 算法核心部分
    # k 作为中间节点 (0-based index)
    for k in range(N):
        # 在更新 dis[i][j] 之前，检查通过节点 k 是否能形成更小的环
        # 环由 i -> k -> j -> ... -> i 组成
        # 这里的 dis[i][j] 是在考虑节点 0 到 k-1 作为中间节点时的最短路径
        # C++ 代码中使用 i < k 和 j < i 的循环顺序，这里也遵循这个逻辑 (0-based)
        for i in range(k):  # 0 <= i < k
            for j in range(i):  # 0 <= j < i
                # 检查 i, k, j 是否构成一个环，并且通过 dis[i][j] 连接
                # 确保原始边 g[i][k] 和 g[k][j] 存在 (不为 INF)
                # 并且 i 到 j 的最短路径 dis[i][j] 存在 (不为 INF)
                if g[i][k] != INF and g[k][j] != INF and dis[i][j] != INF:
                    current_cycle_len = g[i][k] + g[k][j] + dis[i][j]
                    if current_cycle_len < min_cycle_len:
                        min_cycle_len = current_cycle_len
                        # 重构路径
                        path = [0] * (N + 5)  # 临时存储路径的数组，长度足够大
                        cnt = 0
                        # 按照 i, k, j 的顺序加入路径
                        path[cnt] = i
                        cnt += 1
                        path[cnt] = k
                        cnt += 1
                        path[cnt] = j
                        cnt += 1
                        # 获取 j 到 i 的最短路径上的中间节点 (使用之前计算的 dis 和 pos)
                        cnt = get_path(j, i, pos, path, cnt)
                        # 提取实际路径节点 (去除未使用的部分)
                        # 将 0-based 索引转换为 1-based
                        min_cycle_path = [node + 1 for node in path[:cnt]]

        # 标准 Floyd-Warshall 更新最短路径
        for i in range(N):
            for j in range(N):
                if (
                    dis[i][k] != INF
                    and dis[k][j] != INF
                    and dis[i][j] > dis[i][k] + dis[k][j]
                ):
                    dis[i][j] = dis[i][k] + dis[k][j]
                    # 记录从 i 到 j 的最短路径经过 k
                    pos[i][j] = k

    return min_cycle_len, min_cycle_path


# --8<-- [end:core]

# --- 主程序入口 ---
if __name__ == "__main__":
    # 读取节点数 n 和边数 m
    n, m = map(int, sys.stdin.readline().split())

    # 读取边信息
    edges = []
    for _ in range(m):
        u, v, w = map(int, sys.stdin.readline().split())
        edges.append((u, v, w))

    # 查找最小环
    min_len, path = find_minimum_cycle_undirected(n, edges)

    # 输出结果
    if min_len == INF:
        print("No solution.")
    else:
        # 打印路径节点 (1-based index)，用空格分隔
        start = path.index(min(path))
        path = path[start:] + path[:start]
        print(" ".join(map(str, path)))

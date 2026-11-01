# --8<-- [start:core]
# adj : List[List[int]] 邻接表
# vis : List[bool] 记录节点是否已经遍历


def dfs(s: int) -> None:
    stack = [s]  # 用列表来模拟栈，把起点加入栈中
    vis[s] = True  # 起点被遍历

    while stack:  # 当栈非空时继续执行
        u = (
            stack.pop()
        )  # 拿取并丢弃掉最后一个元素（栈顶的元素），可以理解为走到u这个元素

        for v in adj[u]:  # 对于与u相邻的每个元素v
            if not vis[v]:  # 如果v在此前没有走过
                vis[v] = True  # 确保栈里没有重复元素
                stack.append(v)  # 把v加入栈中


# --8<-- [end:core]

n, m = map(int, input().split())
adj = [[] for _ in range(n + 1)]
vis = [False] * (n + 1)
for _ in range(m):
    u, v = map(int, input().split())
    adj[u].append(v)
start, target = map(int, input().split())
dfs(start)
print(*(i for i in range(1, n + 1) if vis[i]))

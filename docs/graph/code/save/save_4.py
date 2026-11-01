n, m = map(int, input().split())
head = [-1] * (n + 1)
nxt = [0] * m
to = [0] * m
vis = [False] * (n + 1)
cnt = -1


# --8<-- [start:add]
# head[u] 和 cnt 的初始值都为 -1
def add(u, v):
    global cnt
    cnt = cnt + 1
    nxt[cnt] = head[u]  # 当前边的后继
    head[u] = cnt  # 起点 u 的第一条边
    to[cnt] = v  # 当前边的终点


# --8<-- [end:add]
def find_edge(u, target):
    # --8<-- [start:walk]
    # 遍历 u 的出边
    i = head[u]
    while ~i:  # ~i 表示 i != -1
        v = to[i]
        # --8<-- [end:walk]
        if v == target:
            return True
        # --8<-- [start:walk_end]
        i = nxt[i]
    # --8<-- [end:walk_end]
    return False


def dfs(u):
    if vis[u]:
        return
    vis[u] = True
    i = head[u]
    while i != -1:
        dfs(to[i])
        i = nxt[i]


for _ in range(m):
    u, v = map(int, input().split())
    add(u, v)

start, target = map(int, input().split())
print(int(find_edge(start, target)))
dfs(start)
print(*(i for i in range(1, n + 1) if vis[i]))

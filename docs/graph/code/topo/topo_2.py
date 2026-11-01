# --8<-- [start:core]
from enum import Enum, auto


class Status(Enum):
    to_visit = auto()
    visiting = auto()
    visited = auto()


def topo_sort(graph: list[list[int]]) -> list[int] | None:
    n = len(graph)
    status = [Status.to_visit] * n
    order = []

    def dfs(u: int) -> bool:
        status[u] = Status.visiting
        for v in graph[u]:
            if status[v] == Status.visiting:
                return False
            if status[v] == Status.to_visit and not dfs(v):
                return False
        status[u] = Status.visited
        order.append(u)
        return True

    for i in range(n):
        if status[i] == Status.to_visit and not dfs(i):
            return None

    return order[::-1]


# --8<-- [end:core]

n, m = map(int, input().split())
graph = [[] for _ in range(n)]
for _ in range(m):
    u, v = map(int, input().split())
    graph[u - 1].append(v - 1)
order = topo_sort(graph)
if order is None:
    print("cycle")
else:
    print(*(u + 1 for u in order))

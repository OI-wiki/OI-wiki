from collections import deque

tr = [[0] * 26]
fail = [0]
e = [0]
q = deque()


def insert(s):
    u = 0
    for c in s:
        c = ord(c) - ord("a")
        if not tr[u][c]:
            tr[u][c] = len(tr)
            tr.append([0] * 26)
            fail.append(0)
            e.append(0)
        u = tr[u][c]
    e[u] += 1


# --8<-- [start:build]
def build():
    for i in range(0, 26):
        if tr[0][i] != 0:
            q.append(tr[0][i])
    while q:
        u = q.popleft()
        for i in range(0, 26):
            if tr[u][i] != 0:
                fail[tr[u][i]] = tr[fail[u]][i]
                q.append(tr[u][i])
            else:
                tr[u][i] = tr[fail[u]][i]


# --8<-- [end:build]


# --8<-- [start:query]
def query(t: str) -> int:
    u, res = 0, 0
    for c in t:
        u = tr[u][ord(c) - ord("a")]
        j = u
        while j and e[j] != -1:
            res += e[j]
            e[j] = -1
            j = fail[j]
    return res


# --8<-- [end:query]

if __name__ == "__main__":
    for _ in range(int(input())):
        insert(input())
    build()
    print(query(input()))

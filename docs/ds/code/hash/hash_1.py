# --8<-- [start:example67]
M = 999997
SIZE = 1000000


class Node:
    def __init__(self, next=None, value=None, key=None):
        self.next = next
        self.value = value
        self.key = key


data = [Node() for _ in range(SIZE)]
head = [0] * M
size = 0


def f(key):
    return key % M


def get(key):
    p = head[f(key)]
    while p:
        if data[p].key == key:
            return data[p].value
        p = data[p].next
    return -1


def modify(key, value):
    p = head[f(key)]
    while p:
        if data[p].key == key:
            data[p].value = value
            return data[p].value
        p = data[p].next
    return -1


def add(key, value):
    global size
    if get(key) != -1:
        return -1
    size = size + 1
    data[size] = Node(head[f(key)], value, key)
    head[f(key)] = size
    return value


# --8<-- [end:example67]

q = int(input())
for _ in range(q):
    args = list(map(int, input().split()))
    op, key = args[:2]
    print(
        add(key, args[2]) if op == 1 else modify(key, args[2]) if op == 2 else get(key)
    )

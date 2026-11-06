class Node:
    def __init__(self, value=None, next=None):
        self.value = value
        self.next = next


# --8<-- [start:example110]
def insertNode(i, p):
    node = Node()
    node.value = i
    node.next = None
    if p == None:
        p = node
        node.next = node
    else:
        node.next = p.next
        p.next = node
    return p


# --8<-- [end:example110]

import sys

data = list(map(int, sys.stdin.buffer.read().split()))
p = None
tail = None
for x in data[1 : data[0] + 1]:
    if p is None:
        p = insertNode(x, p)
        tail = p
    else:
        insertNode(x, tail)
        tail = tail.next
values = []
if p is not None:
    start = p
    while True:
        values.append(p.value)
        p = p.next
        if p is start:
            break
print(*values)

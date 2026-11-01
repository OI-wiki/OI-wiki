# --8<-- [start:example106]
class Node:
    def __init__(self, value=None, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right


# --8<-- [end:example106]


# --8<-- [start:example112]
def insertNode(i, p):
    node = Node()
    node.value = i
    if p == None:
        p = node
        node.left = node
        node.right = node
    else:
        node.left = p
        node.right = p.right
        p.right.left = node
        p.right = node
    return p


# --8<-- [end:example112]


# --8<-- [start:example116]
def deleteNode(p):
    if p.right is p:
        return None
    p.left.right = p.right
    p.right.left = p.left
    return p.right


# --8<-- [end:example116]

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
        tail = tail.right
if p is not None:
    p = deleteNode(p)
values = []
if p is not None:
    start = p
    while True:
        values.append(p.value)
        p = p.right
        if p is start:
            break
print(*values)

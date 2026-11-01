# --8<-- [start:example104]
class Node:
    def __init__(self, value=None, next=None):
        self.value = value
        self.next = next


# --8<-- [end:example104]


# --8<-- [start:example108]
def insertNode(i, p):
    node = Node()
    node.value = i
    node.next = p.next
    p.next = node


# --8<-- [end:example108]


# --8<-- [start:example114]
def deleteNode(p):
    p.value = p.next.value
    p.next = p.next.next


# --8<-- [end:example114]

import sys

data = list(map(int, sys.stdin.buffer.read().split()))
head = Node()
tail = head
for x in data[1 : data[0] + 1]:
    insertNode(x, tail)
    tail = tail.next
if head.next and head.next.next:
    deleteNode(head.next)
values = []
p = head.next
while p:
    values.append(p.value)
    p = p.next
print(*values)

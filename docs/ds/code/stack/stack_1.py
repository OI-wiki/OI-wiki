N = 8
var1 = int(input())
# --8<-- [start:example161]
st = [0] * N
# 这里使用 st[0] 代表栈中元素数量，同时也是栈顶下标

# 压栈 ：
st[st[0] + 1] = var1
st[0] = st[0] + 1
# 取栈顶：
u = st[st[0]]
# 弹栈：注意越界问题, *st == 0 时不能继续弹出
if st[0]:
    st[0] = st[0] - 1
# 清空栈
st[0] = 0
# --8<-- [end:example161]
print(u, st[0])

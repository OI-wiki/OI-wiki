# --8<-- [start:example164]
st = [5, 1, 4]

# 使用 append() 向栈顶添加元素
st.append(2)
st.append(3)
# >>> st
# [5, 1, 4, 2, 3]

# 使用 pop 取出栈顶元素
st.pop()
# >>> st
# [5, 1, 4, 2]

# 使用 clear 清空栈
st.clear()
# --8<-- [end:example164]

print(st)

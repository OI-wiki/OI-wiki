from heapq import heappush, heapreplace

a = [tuple(map(int, input().split())) for _ in range(int(input()))]
a.sort(key=lambda job: job[0])  # 按截止时间升序排列

ans = 0  # 记录总收益
q = []  # 小根堆维护最小值
for d, p in a:
    if d <= len(q):  # 超过截止时间
        if q[0] < p:  # 后悔
            ans += p - heapreplace(q, p)
    else:  # 直接加入队列
        ans += p
        heappush(q, p)
print(ans)

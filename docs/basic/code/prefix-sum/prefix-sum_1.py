N = int(input())
A = [int(input()) for _ in range(N)]
B = [0] * N

B[0] = A[0]
for i in range(1, N):
    B[i] = B[i - 1] + A[i]

for i in range(N):
    print(B[i], end=" ")

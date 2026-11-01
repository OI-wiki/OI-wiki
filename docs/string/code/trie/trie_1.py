# --8<-- [start:core]
class trie:
    def __init__(self):
        self.nex = [[0 for i in range(26)] for j in range(100000)]
        self.cnt = 0
        self.exist = [False] * 100000  # 该结点结尾的字符串是否存在

    def insert(self, s):  # 插入字符串
        p = 0
        for i in s:
            c = ord(i) - ord("a")
            if not self.nex[p][c]:
                self.cnt += 1
                self.nex[p][c] = self.cnt  # 如果没有，就添加结点
            p = self.nex[p][c]
        self.exist[p] = True

    def find(self, s):  # 查找字符串
        p = 0
        for i in s:
            c = ord(i) - ord("a")
            if not self.nex[p][c]:
                return False
            p = self.nex[p][c]
        return self.exist[p]


# --8<-- [end:core]

if __name__ == "__main__":
    dictionary = trie()
    for _ in range(int(input())):
        dictionary.insert(input())
    called = set()
    for _ in range(int(input())):
        s = input()
        if not dictionary.find(s):
            print("WRONG")
        elif s in called:
            print("REPEAT")
        else:
            called.add(s)
            print("OK")

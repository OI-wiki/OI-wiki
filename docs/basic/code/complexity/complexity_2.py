from contextlib import redirect_stdout


class LineCounter:
    def __init__(self):
        self.lines = 0

    def write(self, text):
        self.lines += text.count("\n")
        return len(text)


output = LineCounter()
with redirect_stdout(output):
    # --8<-- [start:core]
    N = 100000
    for i in range(0, N):
        print("hello world")
    # --8<-- [end:core]

print(output.lines)

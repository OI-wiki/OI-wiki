import matplotlib.pyplot as plt

# 点的坐标
points = [(0, 1), (1, 4), (2.5, 6), (3, 0), (4, 3), (4, 4), (6, 6)]
labels = ["1", "2", "3", "4", "5", "6", "7"]

tot = 0
fig, ax = plt.subplots(figsize=(4, 4))

scale_y = 0.7


def save(id=-1):
    """保存图片（递增编号）"""
    global tot
    if id == -1:
        tot += 1
        id = tot

    if id < 10:
        ax.text(
            0.025,
            1.0,
            str(id),
            transform=ax.transAxes,
            fontsize=15,
            fontproperties="SimHei",
            color="black",
            ha="right",
            va="bottom",
        )
    else:
        ax.text(
            0.055,
            1.0,
            str(id),
            transform=ax.transAxes,
            fontsize=15,
            fontproperties="SimHei",
            color="black",
            ha="right",
            va="bottom",
        )

    plt.savefig(f"png/Andrew{id}.png", dpi=150, bbox_inches="tight")

    plt.savefig(f"svg/Andrew{id}.svg", dpi=150, bbox_inches="tight")


def draw_points():
    """绘制点和标签"""
    x = [p[0] for p in points]
    y = [p[1] for p in points]
    ax.scatter(x, y, color="blue", s=50)

    for xi, yi, label in zip(x, y, labels):
        dx, dy = 0.1, 0.1
        if label == "5":
            dx, dy = -0.4, -0.4
        elif label == "1":
            dx, dy = -0.4, -0.4
        elif label == "6":
            dx, dy = -0.1, 0.3
        elif label == "2":
            dx, dy = -0.3, 0.1
        elif label == "4":
            dx, dy = 0.2, 0.1
        ax.text(xi + dx, yi + dy, label, fontsize=12, color="blue")


def draw_lines(stk, x, y, highlight=None):
    """绘制凸壳边界线，highlight=(i,j) 可高亮当前连线"""
    for j in range(len(stk) - 1):
        ax.plot([x[stk[j]], x[stk[j + 1]]], [y[stk[j]], y[stk[j + 1]]], color="black")
    if highlight:
        i, j = highlight
        ax.plot([x[i], x[j]], [y[i], y[j]], color="red")


def add_text(str, fontsize=12,k=0):
    """在右下角添加多行文字"""
    ax.text(
        1.0,
        0.1 * k,
        str,
        transform=ax.transAxes,
        fontsize=fontsize,
        fontproperties="SimHei",
        color="black",
        ha="right",
        va="bottom",
    )


def cross(p1, p2):
    return p1[0] * p2[1] - p2[0] * p1[1]


def sub(p1, p2):
    return (p1[0] - p2[0], p1[1] - p2[1])


def init():
    """清空并重绘坐标系和点"""
    ax.cla()
    draw_points()
    ax.axis("off")
    ax.set_aspect("equal")


def Andrew():
    global points
    stk = []
    used = [False] * len(points)
    x = [p[0] for p in points]
    y = [p[1] for p in points]

    stk.append(0)

    # 下凸壳
    for i in range(1, len(points)):
        init()
        add_text("下凸壳", fontsize=15)
        draw_lines(stk, x, y, highlight=(stk[-1], i))
        save()

        while (
            len(stk) >= 2
            and cross(
                sub(points[stk[-1]], points[stk[-2]]), sub(points[i], points[stk[-1]])
            )
            <= 0
        ):
            used[stk.pop()] = False
            init()
            add_text("下凸壳", fontsize=15)
            draw_lines(stk, x, y, highlight=(stk[-1], i))
            save()

        used[i] = True
        stk.append(i)

    # 上凸壳
    for i in range(len(points) - 1, -1, -1):
        if not used[i]:
            init()
            if labels[stk[-1]] == "5":
                add_text("上凸壳", fontsize=15)
                add_text("4 已经在凸壳中",fontsize = 10,k=1)
            else:
                add_text("上凸壳", fontsize=15)

            draw_lines(stk, x, y, highlight=(stk[-1], i))
            save()

            while (
                len(stk) >= 2
                and cross(
                    sub(points[stk[-1]], points[stk[-2]]),
                    sub(points[i], points[stk[-1]]),
                )
                <= 0
            ):
                used[stk.pop()] = False
                init()
                add_text("上凸壳", fontsize=15)
                draw_lines(stk, x, y, highlight=(stk[-1], i))
                save()

            used[i] = True
            stk.append(i)

    # 完成
    init()
    add_text("完成", fontsize=15)
    draw_lines(stk, x, y)
    save()

    init()
    add_text("完成", fontsize=15)
    draw_lines(stk, x, y)
    save(0)


if __name__ == "__main__":
    points = [(x, y * scale_y) for (x, y) in points]

    init()
    save()
    Andrew()

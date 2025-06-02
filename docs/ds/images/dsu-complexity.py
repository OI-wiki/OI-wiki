import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib as mpl

mpl.rcParams["mathtext.fontset"] = "cm"
mpl.rcParams["mathtext.rm"] = "serif"

fig, ax = plt.subplots(figsize=(6, 6))
ax.set_aspect("equal")
ax.axis("off")

triangle1_top = (1, 5)
triangle1_base_left = (0.5, 3)
triangle1_base_right = (1.5, 3)

triangle2_top = (3, 4)
triangle2_base_left = (2.5, 2)
triangle2_base_right = (3.5, 2)

tri1 = patches.Polygon(
    [triangle1_top, triangle1_base_left, triangle1_base_right],
    closed=True,
    edgecolor="darkseagreen",
    facecolor="darkseagreen",
    alpha=0.3,
    linewidth=2,
)
tri2 = patches.Polygon(
    [triangle2_top, triangle2_base_left, triangle2_base_right],
    closed=True,
    edgecolor="darkseagreen",
    facecolor="darkseagreen",
    alpha=0.3,
    linewidth=2,
)
ax.add_patch(tri1)
ax.add_patch(tri2)

ax.plot(*triangle1_top, "o", color="darkseagreen", markersize=10)
ax.plot(*triangle2_top, "o", color="darkseagreen", markersize=10)
ax.plot(
    [triangle1_top[0], triangle2_top[0]],
    [triangle1_top[1], triangle2_top[1]],
    color="darkseagreen",
    linewidth=2,
)

ax.text(1.0, 3.4, r"$T_{k-1}$", fontsize=36, ha="center", va="top")
ax.text(3.0, 2.4, r"$T_{k-j}$", fontsize=36, ha="center", va="top")

fig.savefig("dsu-complexity.svg", format="svg")

import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib as mpl
import numpy as np

mpl.rcParams["mathtext.fontset"] = "cm"
mpl.rcParams["mathtext.rm"] = "serif"
plt.rcParams["text.usetex"] = True

plt.figure(figsize=(6, 6))

ax = plt.gca()
ax.set_xlim(-0.1, 11.5)
ax.set_ylim(-0.1, 11.5)
plt.xticks(range(1, 12))
plt.yticks(range(1, 12))

ax.xaxis.set_minor_locator(plt.MultipleLocator(1))
ax.yaxis.set_minor_locator(plt.MultipleLocator(1))
ax.grid(True, which="both", linestyle="-", linewidth=0.4, color="grey")

ax.spines["left"].set_position("zero")
ax.spines["right"].set_color("none")
ax.spines["bottom"].set_position("zero")
ax.spines["top"].set_color("none")
plt.subplots_adjust(left=0.05, right=0.95, top=0.95, bottom=0.05)

ax.tick_params(axis="both", which="major", labelsize=14)

x = np.arange(0.01, 11.51, 0.01)
y = 11 / x
plt.plot(x, y, color="#80225f", linewidth=1, zorder=3)
plt.text(
    8.3,
    1.7,
    r"$xy=11$",
    fontsize=20,
    ha="left",
    color="black",
    zorder=5,
)

plt.plot(
    [2.5, 2.5, 0.0],
    [0.0, 4.4, 4.4],
    linestyle="--",
    linewidth=1,
    color="#80225f",
    zorder=3,
)

plt.text(2.6, 4.5, r"$(x_0,y_0)$", fontsize=20, ha="left", color="black", zorder=5)

for xi in range(1, 2 + 1):
    plt.bar(xi, 11 / xi + 0.2, 0.4, color="lightgreen", align="center", alpha=0.5)

for yi in range(1, 4 + 1):
    plt.barh(yi, 11 / yi + 0.2, 0.4, color="orange", align="center", alpha=0.5)

for x, y in (
    [(1, j) for j in range(1, 12)]
    + [(2, j) for j in range(1, 6)]
    + [(3, j) for j in range(1, 4)]
    + [(4, j) for j in range(1, 3)]
    + [(5, j) for j in range(1, 3)]
    + [(j, 1) for j in range(6, 12)]
):
    plt.plot(x, y, "o", color="#c5033e", markersize=5, zorder=4)

plt.savefig("dirichlet-hyperbola.svg", format="svg")

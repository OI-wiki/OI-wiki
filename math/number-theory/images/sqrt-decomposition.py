import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib as mpl
import numpy as np

mpl.rcParams["mathtext.fontset"] = "cm"
mpl.rcParams["mathtext.rm"] = "serif"

plt.figure(figsize=(6, 6))

ax = plt.gca()
ax.set_xlim(-1.5, 11.5)
ax.set_ylim(-1.5, 11.5)
plt.xticks([2, 4, 6, 8, 10])
plt.yticks([2, 4, 6, 8, 10])

ax.xaxis.set_minor_locator(plt.MultipleLocator(1))
ax.yaxis.set_minor_locator(plt.MultipleLocator(1))
ax.grid(True, which="both", linestyle="-", linewidth=0.4, color="grey")

ax.spines["left"].set_position("zero")
ax.spines["right"].set_color("none")
ax.spines["bottom"].set_position("zero")
ax.spines["top"].set_color("none")
plt.subplots_adjust(left=0.05, right=0.95, top=0.95, bottom=0.05)

x = np.arange(0.01, 11.51, 0.01)
y = 11 / x
plt.plot(x, y, color="#80225f", linewidth=1, zorder=3)
plt.text(6, 6, "$f(x)=\\frac{11}{x}$", fontsize=20, ha="left", color="black", zorder=5)

plt.plot([4, 5], [2, 2], color="#0047ba", linewidth=2.5, zorder=3)
plt.plot([5, 11], [1, 1], color="#0047ba", linewidth=2.5, zorder=3)

for x, y in (
    [(0, 0)]
    + [(1, j) for j in range(0, 11)]
    + [(2, j) for j in range(1, 5)]
    + [(3, j) for j in range(1, 3)]
    + [(4, j) for j in range(1, 3)]
    + [(j, 1) for j in range(5, 11)]
):
    plt.plot(x, y, "o", color="#c5033e", markersize=5, zorder=4)
for x, y in [(1, 11), (2, 5), (3, 3), (5, 2), (11, 1)]:
    plt.plot(x, y, "o", color="#00843d", markersize=5, zorder=4)

plt.savefig("sqrt-decomposition.svg", format="svg")

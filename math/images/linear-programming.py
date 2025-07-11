import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib as mpl
import numpy as np

mpl.rcParams["mathtext.fontset"] = "cm"
mpl.rcParams["mathtext.rm"] = "serif"

plt.figure(figsize=(6, 6))

ax = plt.gca()
ax.set_xlim(-4.4, 8.8)
ax.set_ylim(-2.2, 11)
plt.xticks([-4, -2, 2, 4, 6, 8])
plt.yticks([-2, 2, 4, 6, 8, 10])

ax.xaxis.set_minor_locator(plt.MultipleLocator(2))
ax.yaxis.set_minor_locator(plt.MultipleLocator(2))

ax.grid(True, which="major", linestyle="-", linewidth=0.4, color="grey")

ax.spines["left"].set_position("zero")
ax.spines["right"].set_color("none")
ax.spines["bottom"].set_position("zero")
ax.spines["top"].set_color("none")
plt.subplots_adjust(left=0, right=1, top=1, bottom=0)

ALPHA = 0.4

ax.stackplot([-5, 4], np.vstack([[11, 11]]), alpha=ALPHA, colors=["#00629b"], zorder=-5)
ax.stackplot([-5, 4], np.vstack([[-3, -3]]), alpha=ALPHA, colors=["#00629b"], zorder=-5)
plt.text(-0.15, -1.7, "$x \\leq 4$", fontsize=16, ha="right", color="black", zorder=5)

plt.savefig("linear-programming-1.svg", format="svg")

plt.fill_between((-5, 9), 3, 11, alpha=ALPHA, color="#c5003e", zorder=-4)
plt.text(7.85, 3.3, "$y \\geq 3$", fontsize=16, ha="right", color="black", zorder=5)

plt.savefig("linear-programming-2.svg", format="svg")

plt.plot([-5, 4], [24, -3], color="#00843d", zorder=4, linewidth=2)
plt.text(2.65, 1.55, "$3x+y = 9$", fontsize=16, ha="left", color="black", zorder=5)
plt.fill_between([-1, 2, 4], [12, 3, 3], 12, color="#f3d03e", zorder=-1)
plt.plot(2, 3, "o", color="#c5033e", zorder=3)
plt.text(2.05, 3.25, "$(2, 3)$", fontsize=16, ha="left", color="black", zorder=5)

plt.savefig("linear-programming-3.svg", format="svg")

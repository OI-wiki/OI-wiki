import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib as mpl
import numpy as np

mpl.rcParams["mathtext.fontset"] = "cm"
mpl.rcParams["mathtext.rm"] = "serif"

plt.figure(figsize=(6, 6))

ax = plt.gca()
ax.set_xlim(-2.1, 14.3)
ax.set_ylim(-2.1, 14.3)
plt.xticks([-2, 2, 4, 6, 8, 10, 12, 14])
plt.yticks([-2, 2, 4, 6, 8, 10, 12, 14])

ax.axhline(0, color="black", linewidth=0.1)
ax.axvline(0, color="black", linewidth=0.1)

ax.xaxis.set_major_locator(plt.MultipleLocator(2))
ax.yaxis.set_major_locator(plt.MultipleLocator(2))
ax.xaxis.set_minor_locator(plt.MultipleLocator(1))
ax.yaxis.set_minor_locator(plt.MultipleLocator(1))

ax.axline((-6, 24), (12, -12), linewidth=2, color="#00629b")
ax.axline((-9, 9), (27, -9), linewidth=2, color="#00629b")

plt.text(2, 8.5, "$2x_1+x_2=12$", fontsize=18, ha="left", color="#00629b")
plt.text(7, 1.5, "$x_1+2x_2=9$", fontsize=18, ha="left", color="#00629b")

for x, y in [(0, 0), (0, 12), (6, 0), (0, 4.5), (9, 0), (5, 2)]:
    ax.plot(x, y, "o", color="#c5033e", zorder=3)

ax.spines["left"].set_position("zero")
ax.spines["right"].set_color("none")
ax.spines["bottom"].set_position("zero")
ax.spines["top"].set_color("none")
plt.subplots_adjust(left=0, right=1, top=1, bottom=0)

plt.savefig("feasible-region-1.svg", format="svg")

ax.stackplot([0, 5, 6], np.vstack([[4.5, 2, 0]]), colors=["#71cc98"])

plt.savefig("feasible-region-2.svg", format="svg")

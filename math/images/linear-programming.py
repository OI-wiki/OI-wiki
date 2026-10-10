import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib as mpl
import numpy as np

mpl.rcParams["mathtext.fontset"] = "cm"
mpl.rcParams["mathtext.rm"] = "serif"

plt.figure(figsize=(6, 6))

ax = plt.gca()
ax.set_xlim(-0.9, 21.3)
ax.set_ylim(-0.9, 21.3)

ax.axhline(0, color="black", linewidth=0.1)
ax.axvline(0, color="black", linewidth=0.1)

ax.xaxis.set_major_locator(plt.MultipleLocator(2))
ax.yaxis.set_major_locator(plt.MultipleLocator(2))
ax.xaxis.set_minor_locator(plt.MultipleLocator(1))
ax.yaxis.set_minor_locator(plt.MultipleLocator(1))

ax.axline((-1, 10), (20, -2), linewidth=2, color="#00629b")
ax.axline((-3, 27), (9, -1), linewidth=2, color="#00629b")
ax.axline((0, 16), (12, 0), linewidth=2, color="#00629b")
ax.axline((6, 6), (12, 1), linewidth=2, color="#c5033e")

plt.text(2, 16, "$7x_1+3x_2=60$", fontsize=18, ha="left", color="#00629b")
plt.text(14, 2, "$4x_1+7x_2=66$", fontsize=18, ha="left", color="#00629b")
plt.text(7, 7, "$8x_1+6x_2=96$", fontsize=18, ha="left", color="#00629b")

for x, y in [(6, 6)]:
    ax.plot(x, y, "o", color="#c5033e", zorder=3)

plt.text(6, 5, "$(6,6)$", fontsize=18, ha="right", color="#c5033e")

ax.spines["left"].set_position("zero")
ax.spines["right"].set_color("none")
ax.spines["bottom"].set_position("zero")
ax.spines["top"].set_color("none")
plt.subplots_adjust(left=0, right=1, top=1, bottom=0)

ax.stackplot([0, 6, 60 / 7], np.vstack([[66 / 7, 6, 0]]), colors=["#71cc98"])

plt.savefig("linear-programming.svg", format="svg")

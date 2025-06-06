import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib as mpl
import numpy as np

mpl.rcParams["mathtext.fontset"] = "cm"
mpl.rcParams["mathtext.rm"] = "serif"


def main(n):
    plt.figure(figsize=(6, 6))

    ax = plt.gca()
    ax.set_xlim(-1.15, 1.15)
    ax.set_ylim(-1.15, 1.15)

    ax.axhline(0, color="black", linewidth=0.1)
    ax.axvline(0, color="black", linewidth=0.1)
    ax.set_xticks([-1, -0.5, 0.5, 1])
    ax.set_yticks([-1, -0.5, 0.5, 1])

    ax.grid(True, which="both", linestyle="--", linewidth=0.5)
    ax.xaxis.set_minor_locator(plt.MultipleLocator(0.1))
    ax.yaxis.set_minor_locator(plt.MultipleLocator(0.1))
    ax.grid(which="major", linestyle="-", linewidth=0.5, color="gray")
    ax.grid(which="minor", linestyle=":", linewidth=0.2, color="lightgray")
    plt.text(-0.05, -0.1, "$O$", fontsize=12, ha="center")

    x1, y1, x2, y2 = [0, 1, 1, 1], [1, 1, -0.5, 1], [1, -1, -1, -1], [0, 0.5, 0.5, 0.5]
    ax.arrow(
        0,
        0,
        x1[n - 1],
        y1[n - 1],
        width=0.01,
        head_width=0.03,
        head_length=0.03,
        zorder=3,
        color="#00629b",
    )
    ax.arrow(
        0,
        0,
        x2[n - 1],
        y2[n - 1],
        width=0.01,
        head_width=0.03,
        head_length=0.03,
        zorder=3,
        color="#c5003e",
    )
    if n == 4:
        ax.arrow(
            0,
            0,
            0.5,
            -0.5,
            width=0.01,
            head_width=0.03,
            head_length=0.03,
            zorder=3,
            color="#00843d",
        )
    plt.text(
        x1[n - 1] + 0.08,
        y1[n - 1] + 0.08,
        "$u$",
        fontsize=16,
        ha="center",
        color="#00629b",
    )
    plt.text(
        x2[n - 1] + 0.08,
        y2[n - 1] + 0.08,
        "$v$",
        fontsize=16,
        ha="center",
        color="#c5003e",
    )
    if n == 4:
        plt.text(0.58, -0.42, "$w$", fontsize=16, ha="center", color="#00843d")

    ax.spines["left"].set_position("zero")
    ax.spines["right"].set_color("none")
    ax.spines["bottom"].set_position("zero")
    ax.spines["top"].set_color("none")
    plt.subplots_adjust(left=0, right=1, top=1, bottom=0)

    plt.savefig(f"basis-{n}.svg", format="svg")


if __name__ == "__main__":
    for i in range(1, 5):
        main(i)

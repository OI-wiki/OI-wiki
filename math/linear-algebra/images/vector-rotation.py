import matplotlib.pyplot as plt
import numpy as np

plt.rcParams["mathtext.fontset"] = "cm"
plt.rcParams["font.family"] = "STIXGeneral"


def draw_vector(ax, origin, vec, color, label):
    ax.arrow(
        *origin,
        *vec,
        head_width=0.05,
        head_length=0.05,
        fc=color,
        ec=color,
        linewidth=2,
        length_includes_head=True,
    )
    ax.text(
        origin[0] + vec[0] + 0.1,
        origin[1] + vec[1] + 0.12,
        label,
        fontsize=16,
        ha="center",
        va="center",
    )


def draw_dashed_line(ax, p1, p2):
    ax.plot([p1[0], p2[0]], [p1[1], p2[1]], "--", color="gold", linewidth=2)


def draw_angle_arc(ax, center, radius, theta1, theta2, label, offset):
    theta = np.linspace(np.radians(theta1), np.radians(theta2), 100)
    x = center[0] + radius * np.cos(theta)
    y = center[1] + radius * np.sin(theta)
    ax.plot(x, y, color="blue")
    mid_theta = (theta1 + theta2) / 2
    ax.text(
        center[0] + radius * np.cos(np.radians(mid_theta)) + offset[0],
        center[1] + radius * np.sin(np.radians(mid_theta)) + offset[1],
        label,
        color="blue",
        fontsize=16,
    )


fig, axs = plt.subplots(1, 2, figsize=(10, 4))

origin = np.array([0, 0])
a, b = np.array([1.5, 1.5]), np.array([np.sqrt(0.5), 2])
theta, alpha = np.arctan2(a[1], a[0]), np.arctan2(b[1], b[0]) - np.arctan2(a[1], a[0])

ax = axs[0]
draw_vector(ax, origin, a, "royalblue", r"$\vec{a}=(x,y)$")
draw_dashed_line(ax, a, [a[0], 0])
draw_dashed_line(ax, origin, [a[0], 0])
draw_angle_arc(ax, origin, 0.3, 0, np.degrees(theta), r"$\theta$", (0.04, 0.01))
ax.set_xlim(-0.2, 2.2)
ax.set_ylim(-0.2, 2.2)
ax.axis("off")

ax = axs[1]
draw_vector(ax, origin, a, "royalblue", r"$\vec{a}=(l\cos\theta, l\sin\theta)$")
draw_vector(
    ax, origin, b, "purple", r"$\vec{b}=(l\cos(\theta+\alpha), l\sin(\theta+\alpha))$"
)
draw_dashed_line(ax, a, [a[0], 0])
draw_dashed_line(ax, origin, [a[0], 0])
draw_angle_arc(ax, origin, 0.3, 0, np.degrees(theta), r"$\theta$", (0.04, 0.01))
draw_angle_arc(
    ax,
    origin,
    0.5,
    np.degrees(theta),
    np.degrees(theta + alpha),
    r"$\alpha$",
    (0.01, 0.06),
)
ax.set_xlim(-0.2, 2.2)
ax.set_ylim(-0.2, 2.2)
ax.axis("off")

plt.tight_layout()
plt.savefig("vector-rotation.svg", format="svg")

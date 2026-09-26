import matplotlib.pyplot as plt
import xml.etree.ElementTree as ET
import os
import shutil

tmp_dir = "./svg/"

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

    plt.savefig(f"{tmp_dir}/andrew{id:02d}.svg", dpi=150, bbox_inches="tight")


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


def add_text(str, fontsize=12, k=0):
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
                add_text("4 已经在凸壳中", fontsize=10, k=1)
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


def combine(svg_dir="./svg/", output_file="andrew.svg"):
    frames = [svg_dir + file for file in sorted(os.listdir(svg_dir))]

    groups = []
    viewBox = None

    for i, f in enumerate(frames):
        tree = ET.parse(f)
        root = tree.getroot()

        # grab viewBox (same for all)
        if viewBox is None and "viewBox" in root.attrib:
            viewBox = root.attrib["viewBox"]

        # wrap all children of <svg> into a <g>
        g = ET.Element("g", id=f"frame{i}", display="none")
        for child in list(root):
            g.append(child)
        groups.append(g)

    # Build master SVG
    svg_attrs = {
        "xmlns": "http://www.w3.org/2000/svg",
        "version": "1.1",
    }
    if viewBox is not None:
        svg_attrs["viewBox"] = viewBox

    svg = ET.Element("svg", svg_attrs)

    total_dur = len(frames)  # total cycle duration

    for i, g in enumerate(groups):
        # Calculate keyTimes - each frame gets equal time slice
        frame_start = i / len(frames)
        frame_end = (i + 1) / len(frames)

        # Build keyTimes and values like the example
        # Format: "start_time;end_time;1" with values "none;inline;none"
        keyTimes = f"0;{frame_start:.6f};{frame_end:.6f};1"

        if i == 0:
            # First frame: visible at start, then hidden
            values = "inline;inline;none;none"
        else:
            # Other frames: hidden, then visible, then hidden
            values = "none;inline;none;none"

        animate = ET.Element(
            "animate",
            {
                "attributeName": "display",
                "repeatCount": "indefinite",
                "dur": f"{total_dur}s",
                "keyTimes": keyTimes,
                "values": values,
                "calcMode": "discrete",  # This ensures instant transitions like the example
            },
        )

        g.append(animate)
        svg.append(g)

    ET.ElementTree(svg).write(output_file)


def generate_table(
    svg_dir="./svg/",
    output_file="andrew.printable.svg",
    cols=5,
    rows=4,
    line_width=1,
    line_color="#000000",
):
    # Get all SVG files and sort them
    frames = [os.path.join(svg_dir, file) for file in sorted(os.listdir(svg_dir))]
    frames = frames[1:]

    if not frames:
        raise ValueError(f"No SVG files found in {svg_dir}")

    # Parse first frame to get dimensions and viewBox
    first_tree = ET.parse(frames[0])
    first_root = first_tree.getroot()

    # Get original viewBox or calculate from width/height
    original_viewbox = None
    if "viewBox" in first_root.attrib:
        original_viewbox = first_root.attrib["viewBox"]
        vb_parts = original_viewbox.split()
        frame_width = float(vb_parts[2]) - float(vb_parts[0])
        frame_height = float(vb_parts[3]) - float(vb_parts[1])
        vb_x = float(vb_parts[0])
        vb_y = float(vb_parts[1])
    else:
        # Fallback to width/height attributes
        frame_width = float(first_root.attrib.get("width", 100))
        frame_height = float(first_root.attrib.get("height", 100))
        vb_x = 0
        vb_y = 0

    # Calculate total dimensions including separating lines
    total_width = cols * frame_width + (cols + 1) * line_width
    total_height = rows * frame_height + (rows + 1) * line_width

    # Create master SVG
    master_attrs = {
        "xmlns": "http://www.w3.org/2000/svg",
        "version": "1.1",
        "width": str(total_width),
        "height": str(total_height),
        "viewBox": f"0 0 {total_width} {total_height}",
    }

    svg = ET.Element("svg", master_attrs)

    # Add frames to the grid
    for idx, frame_path in enumerate(frames[: rows * cols]):  # Limit to grid size
        row = idx // cols
        col = idx % cols

        # Calculate position with separating lines
        x = col * (frame_width + line_width) + line_width
        y = row * (frame_height + line_width) + line_width

        try:
            # Parse the frame
            tree = ET.parse(frame_path)
            root = tree.getroot()

            # Create group for this frame
            g = ET.Element(
                "g", {"id": f"frame_{row}_{col}", "transform": f"translate({x}, {y})"}
            )

            # If the original had a viewBox, we need to add a nested SVG to maintain scaling
            if original_viewbox:
                nested_svg = ET.Element(
                    "svg",
                    {
                        "width": str(frame_width),
                        "height": str(frame_height),
                        "viewBox": original_viewbox,
                        "preserveAspectRatio": "xMidYMid meet",
                    },
                )

                # Copy all children from original SVG
                for child in list(root):
                    nested_svg.append(child)

                g.append(nested_svg)
            else:
                # Copy children directly
                for child in list(root):
                    g.append(child)

            svg.append(g)

        except ET.ParseError as e:
            print(f"Warning: Could not parse {frame_path}: {e}")
            continue

    # Add horizontal separating lines
    for i in range(rows + 1):
        y = i * (frame_height + line_width) + line_width / 2
        line = ET.Element(
            "line",
            {
                "x1": "0",
                "y1": str(y),
                "x2": str(total_width),
                "y2": str(y),
                "stroke": line_color,
                "stroke-width": str(line_width),
            },
        )
        svg.append(line)

    # Add vertical separating lines
    for j in range(cols + 1):
        x = j * (frame_width + line_width) + line_width / 2
        line = ET.Element(
            "line",
            {
                "x1": str(x),
                "y1": "0",
                "x2": str(x),
                "y2": str(total_height),
                "stroke": line_color,
                "stroke-width": str(line_width),
            },
        )
        svg.append(line)

    # Write the result
    tree = ET.ElementTree(svg)
    try:
        ET.indent(tree, space="  ")  # Pretty print (Python 3.9+)
    except AttributeError:
        pass  # Skip pretty printing for older Python versions

    tree.write(output_file, encoding="utf-8", xml_declaration=True)


if __name__ == "__main__":
    points = [(x, y * scale_y) for (x, y) in points]

    shutil.rmtree(tmp_dir, ignore_errors=True)
    os.mkdir(tmp_dir)

    init()
    save()
    Andrew()
    combine(tmp_dir)
    generate_table(tmp_dir)

    shutil.rmtree(tmp_dir, ignore_errors=True)

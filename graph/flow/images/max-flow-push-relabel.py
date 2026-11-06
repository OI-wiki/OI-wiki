"""Rebuild the four push-relabel/HLPP SVGs used by max-flow.md.

Run from any directory with Python 3, latex (TikZ, standalone, lmodern), and
dvisvgm on PATH:

    python docs/graph/flow/images/max-flow-push-relabel.py

Intermediate TeX, DVI, and per-frame SVGs go in _build/flow-vectors.
All labels are outlined.
The push-relabel animation uses SVG/SMIL without JavaScript, raster images,
or web fonts. The HLPP walkthrough is a static 24-panel grid.
Edit the network, operations, or max-flow-network.tex, then rerun this source.
"""

import argparse
from collections import deque
from copy import deepcopy
from pathlib import Path
import re
import subprocess
import xml.etree.ElementTree as ET


SOURCE = Path(__file__).resolve().parent
VERTICES = range(7)
S, T = 0, 6
CAPACITIES = {
    (0, 1): 4,
    (0, 3): 5,
    (1, 2): 5,
    (1, 3): 1,
    (3, 2): 2,
    (3, 4): 5,
    (4, 2): 6,
    (4, 5): 3,
    (2, 6): 5,
    (5, 6): 2,
}
NEIGHBORS = {
    0: [3, 1],
    1: [3, 2, 0],
    2: [6, 4, 3, 1],
    3: [4, 2, 1, 0],
    4: [5, 2, 3],
    5: [6, 4],
    6: [5, 2],
}
POSITIONS = {
    0: (10, 48),
    1: (65, 12),
    2: (120, 36),
    3: (65, 76),
    4: (120, 101),
    5: (180, 101),
    6: (180, 42),
}
SVG = "http://www.w3.org/2000/svg"
ET.register_namespace("", SVG)
ET.register_namespace("xlink", "http://www.w3.org/1999/xlink")


class Network:
    def __init__(self, source_height=len(VERTICES)):
        self.flow = {edge: 0 for edge in CAPACITIES}
        self.height = [0] * len(VERTICES)
        self.excess = [0] * len(VERTICES)
        self.source_height = source_height

    def residual(self, u, v):
        if (u, v) in self.flow:
            return CAPACITIES[u, v] - self.flow[u, v]
        return self.flow[v, u]

    def active(self):
        return [u for u in VERTICES if u not in (S, T) and self.excess[u] > 0]

    def initialize(self, bfs=False):
        if bfs:
            self.height = [len(VERTICES)] * len(VERTICES)
            self.height[T] = 0
            queue = deque([T])
            seen = {T}
            while queue:
                v = queue.popleft()
                for u in NEIGHBORS[v]:
                    if u not in seen and self.residual(u, v) > 0:
                        self.height[u] = self.height[v] + 1
                        seen.add(u)
                        queue.append(u)
        self.height[S] = self.source_height
        for v in NEIGHBORS[S]:
            amount = self.residual(S, v)
            self.flow[S, v] = amount
            self.excess[S] -= amount
            self.excess[v] += amount

    def push(self, u):
        pushed = False
        for v in NEIGHBORS[u]:
            amount = min(self.excess[u], self.residual(u, v))
            if amount and self.height[u] == self.height[v] + 1:
                if (u, v) in self.flow:
                    self.flow[u, v] += amount
                else:
                    self.flow[v, u] -= amount
                self.excess[u] -= amount
                self.excess[v] += amount
                pushed = True
        return pushed

    def relabel(self, u, gap=False):
        old = self.height[u]
        if gap and self.height.count(old) == 1:
            for v in VERTICES:
                if v not in (S, T) and old < self.height[v] < self.source_height:
                    self.height[v] = self.source_height + 1
        self.height[u] = 1 + min(
            self.height[v] for v in NEIGHBORS[u] if self.residual(u, v)
        )


def snapshot(network, caption=""):
    return deepcopy(network), caption


def plain_trace():
    # Preserve h(s)=6 and the node labels from 2149.gif / 2150.png verbatim.
    network = Network(source_height=6)
    frames = [snapshot(network)]
    network.initialize()
    # Scan for the smallest active vertex, as in the original example.
    # Save a frame at each relabel.
    while network.active():
        u = min(network.active())
        if not network.push(u):
            network.relabel(u)
            frames.append(snapshot(network))
    frames.append(snapshot(network))
    return frames


def hlpp_trace():
    # Match h(s)=6 and the subsequent GAP heights in the original 1152.png.
    network = Network(source_height=6)
    frames = [snapshot(network, "origin")]
    network.initialize(bfs=True)
    frames.append(snapshot(network, "Initialize"))
    # Preserve the 24 numbered steps of the original walkthrough, including
    # GAP at pic13 -> pic14. Ties between highest vertices follow this order.
    operations = [
        ("push", 3),
        ("relabel", 3),
        ("push", 3),
        ("push", 1),
        ("push", 4),
        ("push", 2),
        ("relabel", 2),
        ("push", 2),
        ("relabel", 1),
        ("push", 1),
        ("push", 3),
        ("gap", 4),
        ("push", 4),
        ("relabel", 2),
        ("push", 2),
        ("push", 3),
        ("push", 5),
        ("relabel", 5),
        ("push", 5),
        ("push", 4),
        ("push", 3),
    ]
    for action, u in operations:
        if action == "push":
            network.push(u)
            caption = f"Push({u})"
        else:
            network.relabel(u, gap=action == "gap")
            caption = f"Relabel({u})"
        frames.append(snapshot(network, caption))
    frames.append(snapshot(network, "Final"))
    return frames


def picture(network, caption, number, plain):
    lines = [rf"\NetworkStart{{{120 if plain else 128}}}"]
    for u, (x, y) in POSITIONS.items():
        shade = min(95, network.height[u] * 10)
        text = "white" if shade >= 60 else "black"
        lines.append(
            rf"\node[vertex,fill=heightcolor!{shade},text={text}] (v{u})"
            rf" at ({x},{y}) {{$ {u} $\\$ {network.height[u]}\mid {network.excess[u]} $}};"
        )
    for u in VERTICES:
        for v in NEIGHBORS[u]:
            residual = network.residual(u, v)
            if not residual:
                continue
            color = (
                "admissible" if network.height[u] == network.height[v] + 1 else "black"
            )
            bend = 13 if network.residual(v, u) else 0
            if not bend and {u, v} == {1, 2}:
                bend = 20 if u == 1 else -20
            if not bend and {u, v} == {3, 4}:
                bend = -20 if u == 3 else 20
            lines.append(
                rf"\draw[edge,draw={color}] (v{u}) to[bend left={bend}]"
                rf" node[capacity,text=black] {{$ {residual} $}} (v{v});"
            )
    if plain:
        # Keep the original pic1 ... pic29 captions without added explanations.
        lines.append(rf"\PlainNetworkEnd{{pic{number}}}")
    else:
        lines.append(rf"\NetworkEnd{{pic{number}-{caption}}}")
    return "\n".join(lines)


def run(command, cwd):
    result = subprocess.run(
        command,
        cwd=cwd,
        text=True,
        encoding="utf-8",
        errors="replace",
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )
    if result.returncode:
        raise RuntimeError(result.stdout)


def render_frames(frames, name, build):
    template = (SOURCE / "max-flow-network.tex").read_text(encoding="utf-8")
    document = template + "\n\\begin{document}\n"
    document += "\n".join(
        picture(network, caption, i + 1, name == "push-relabel")
        for i, (network, caption) in enumerate(frames)
    )
    document += "\n\\end{document}\n"
    (build / f"{name}.tex").write_text(document, encoding="utf-8")
    run(["latex", "-interaction=nonstopmode", "-halt-on-error", f"{name}.tex"], build)
    run(
        [
            "dvisvgm",
            "--no-fonts",
            "--exact",
            "--bbox=papersize",
            "--page=1-",
            f"--output={name}-%p.svg",
            f"{name}.dvi",
        ],
        build,
    )
    # dvisvgm pads %p to the number of digits in the total page count.
    digits = len(str(len(frames)))
    return [
        ET.parse(build / f"{name}-{i + 1:0{digits}d}.svg").getroot()
        for i in range(len(frames))
    ]


def svg_root(width, height, title, description):
    root = ET.Element(
        f"{{{SVG}}}svg",
        {
            "version": "1.1",
            "width": f"{width:g}pt",
            "height": f"{height:g}pt",
            "viewBox": f"0 0 {width:g} {height:g}",
        },
    )
    ET.SubElement(root, f"{{{SVG}}}title").text = title
    ET.SubElement(root, f"{{{SVG}}}desc").text = description
    ET.SubElement(
        root, f"{{{SVG}}}rect", {"width": "100%", "height": "100%", "fill": "white"}
    )
    return root


def frame_group(frame, prefix, x=0, y=0):
    # dvisvgm reuses glyph/page IDs across pages. Namespace every ID and href
    # before combining pages, otherwise labels would point to the wrong glyphs.
    frame = deepcopy(frame)
    identifiers = {
        node.attrib["id"]: prefix + node.attrib["id"]
        for node in frame.iter()
        if "id" in node.attrib
    }
    for node in frame.iter():
        for key, value in list(node.attrib.items()):
            if key == "id":
                node.set(key, identifiers[value])
            elif key.endswith("href") and value.startswith("#"):
                node.set(key, "#" + identifiers[value[1:]])
            else:
                node.set(
                    key,
                    re.sub(
                        r"url\(#([^)]+)\)",
                        lambda match: f"url(#{identifiers[match[1]]})",
                        value,
                    ),
                )
    left, top, _, _ = map(float, frame.attrib["viewBox"].split())
    group = ET.Element(
        f"{{{SVG}}}g", {"transform": f"translate({x - left:g} {y - top:g})"}
    )
    group.extend(frame)
    return group


def save_svg(root, path):
    ET.ElementTree(root).write(path, encoding="utf-8", xml_declaration=True)
    with path.open("ab") as output:
        output.write(b"\n")


def export_animation(
    frames,
    path,
    *,
    title="Push-relabel walkthrough",
    description="Residual capacities, node heights and excesses at every relabel. "
    "Source 0, sink 6, seven vertices, maximum flow 7.",
):
    _, _, width, height = map(float, frames[0].attrib["viewBox"].split())
    root = svg_root(width, height, title, description)
    count = len(frames)
    # One second per step, with two extra seconds on the final state. Without
    # animation support the first frame remains visible (e.g. in PDF output).
    duration = count + 2
    for i, frame in enumerate(frames):
        group = frame_group(frame, f"f{i}-")
        group.set("visibility", "visible" if i == 0 else "hidden")
        if i == 0:
            times, values = [0, 1 / duration, 1], ["visible", "hidden", "hidden"]
        elif i == count - 1:
            times, values = [0, i / duration, 1], ["hidden", "visible", "visible"]
        else:
            times = [0, i / duration, (i + 1) / duration, 1]
            values = ["hidden", "visible", "hidden", "hidden"]
        ET.SubElement(
            group,
            f"{{{SVG}}}animate",
            {
                "attributeName": "visibility",
                "values": ";".join(values),
                "keyTimes": ";".join(f"{time:.12g}" for time in times),
                "calcMode": "discrete",
                "dur": f"{duration}s",
                "repeatCount": "indefinite",
            },
        )
        root.append(group)
    save_svg(root, path)


def export_grid(frames, path):
    _, _, width, height = map(float, frames[0].attrib["viewBox"].split())
    root = svg_root(
        4 * width,
        6 * height,
        "Highest-label push-relabel walkthrough",
        "24 steps; pic13 to pic14 applies Relabel(4) and GAP. Maximum flow 7.",
    )
    for i, frame in enumerate(frames):
        root.append(
            frame_group(frame, f"p{i + 1}-", (i % 4) * width, (i // 4) * height)
        )
    save_svg(root, path)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--build-dir", type=Path, default=SOURCE.parents[3] / "_build/flow-vectors"
    )
    parser.add_argument("--output-dir", type=Path, default=SOURCE)
    args = parser.parse_args()
    plain, hlpp = plain_trace(), hlpp_trace()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    args.output_dir.mkdir(parents=True, exist_ok=True)
    plain_svg = render_frames(plain, "push-relabel", build)
    hlpp_svg = render_frames(hlpp, "hlpp", build)
    save_svg(plain_svg[0], args.output_dir / "push-relabel-initial.svg")
    save_svg(plain_svg[-1], args.output_dir / "push-relabel-final.svg")
    export_animation(plain_svg, args.output_dir / "push-relabel.svg")
    export_grid(hlpp_svg, args.output_dir / "hlpp.svg")
    print(
        "Rebuilt push-relabel-initial.svg, push-relabel.svg, push-relabel-final.svg, and hlpp.svg."
    )


if __name__ == "__main__":
    main()

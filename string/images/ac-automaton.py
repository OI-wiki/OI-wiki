#!/usr/bin/env python3
"""Editable source for the AC automaton figures, including the three animations.

Run `python docs/string/images/ac-automaton.py` from the repository root.
Only the Python standard library is needed. SVG 1.1 SMIL animations are used,
without JavaScript or embedded raster images. Each animation has a useful static
fallback (the complete automaton); its frame sequence starts at time zero.

For frame-by-frame review, run with `--frames OUTPUT_DIRECTORY`. The algorithm
computes the failure function, completed transitions, and matching trace; only
the drawing coordinates and the curve routing are specified by hand.
"""

from __future__ import annotations

import argparse
from collections import deque
from dataclasses import dataclass, field, replace
from html import escape
from math import hypot
from pathlib import Path


WIDTH, HEIGHT = 1450, 1070
GRAPH_TOP = 50
RADIUS = 34
EDGE_TEXT_SIZE = 36
TRIE_TEXT_SIZE = 40
STATE_TEXT_SIZE = 48
INPUT_TEXT_SIZE = 42
MATCH_TEXT_SIZE = 38
POINTS = {
    0: (130, 470),
    1: (365, 300),
    2: (665, 150),
    3: (985, 150),
    4: (1300, 150),
    5: (665, 380),
    6: (985, 380),
    7: (365, 610),
    8: (665, 610),
    9: (985, 610),
    10: (235, 850),
}
EDGES = [
    (0, "h", 1),
    (1, "e", 2),
    (2, "r", 3),
    (3, "s", 4),
    (1, "i", 5),
    (5, "s", 6),
    (0, "s", 7),
    (7, "h", 8),
    (8, "e", 9),
    (0, "i", 10),
]
# Keep the enlarged trie labels clear of the completed transition curves.
TRIE_LABELS = {
    (0, 1): (240, 371),
    (1, 2): (535, 261),
    (2, 3): (821, 142),
    (3, 4): (1142, 140),
    (1, 5): (525, 337),
    (5, 6): (819, 366),
    (0, 7): (256, 510),
    (7, 8): (491, 648),
    (8, 9): (863, 648),
    (0, 10): (202, 652),
}
PATTERNS = {2: "he", 4: "hers", 6: "his", 9: "she", 10: "i"}
TEXT = "ushersheishis"
COLORS = {
    "trie": "#a8afb6",
    "label": "#168543",
    "fail": "#d39200",
    "new": "#d82535",
    "extra": "#222a35",
    "current": "#009ccc",
    "move": "#e24f98",
    "match": "#1673c9",
}
FILLS = {
    "done": "#c5eb70",
    "new": "#ffeb59",
    "current": "#a6e4f2",
    "move": "#f36a72",
    "match": "#72b5ed",
}

# Routes for failure pointers, including the root's self-loop.
FAIL_ROUTES = {
    0: "M 99 458 C 24 395 19 540 105 494",
    1: "M 336 282 Q 170 275 136 432",
    2: "M 633 139 C 366 110 182 250 119 433",
    3: "M 954 135 C 486 2 189 87 109 433",
    4: "M 1314 183 C 1420 437 678 529 399 599",
    5: "M 632 391 C 367 410 209 582 229 815",
    6: "M 952 392 C 688 436 471 507 396 591",
    7: "M 335 594 Q 247 508 164 479",
    8: "M 634 595 Q 422 513 360 335",
    9: "M 956 590 Q 752 455 673 185",
    10: "M 215 822 Q 122 692 127 508",
}

# (state, input) -> (Bezier curve, label position). Endpoints remain outside
# node circles; separate routes distinguish parallel failure/transition edges.
EXTRA_ROUTES = {
    (1, "h"): ("M 336 284 C 234 240 285 164 345 271", (286, 198)),
    (1, "s"): ("M 365 337 L 365 573", (383, 449)),
    (2, "h"): ("M 633 165 Q 478 186 395 281", (462, 207)),
    (2, "i"): ("M 659 186 C 613 639 472 846 273 849", (550, 603)),
    (2, "s"): ("M 647 182 L 389 578", (486, 397)),
    (3, "h"): ("M 953 167 Q 666 294 401 293", (710, 240)),
    (3, "i"): ("M 977 186 C 896 784 574 931 267 866", (762, 779)),
    (4, "h"): ("M 1290 186 C 1253 474 912 574 701 605", (1203, 432)),
    (4, "i"): ("M 1310 185 C 1509 923 671 1027 268 870", (1242, 763)),
    (4, "s"): ("M 1267 169 Q 823 373 397 590", (1097, 289)),
    (5, "h"): ("M 629 379 Q 481 377 398 316", (457, 389)),
    (5, "i"): ("M 656 415 C 571 779 422 885 272 858", (527, 789)),
    (6, "h"): ("M 975 415 Q 879 521 697 592", (852, 560)),
    (6, "i"): ("M 984 417 C 1038 916 503 998 267 870", (875, 845)),
    (6, "s"): ("M 968 413 C 853 754 548 727 395 633", (655, 728)),
    (7, "i"): ("M 338 636 L 255 820", (285, 721)),
    (7, "s"): ("M 397 626 C 515 625 429 744 376 647", (466, 707)),
    (8, "h"): ("M 641 584 Q 461 532 380 333", (495, 480)),
    (8, "i"): ("M 665 573 L 665 417", (684, 496)),
    (8, "s"): ("M 632 625 Q 508 696 396 630", (522, 652)),
    (9, "h"): ("M 954 593 C 825 362 583 274 401 304", (782, 372)),
    (9, "i"): ("M 974 644 C 830 989 422 1019 265 875", (789, 913)),
    (9, "r"): ("M 1004 581 Q 1117 363 1000 185", (1079, 376)),
    (9, "s"): ("M 954 630 C 753 809 474 805 386 641", (573, 797)),
    (10, "h"): ("M 244 815 L 353 335", (306, 649)),
    (10, "i"): ("M 265 871 C 352 904 264 988 244 887", (313, 952)),
    (10, "s"): ("M 262 827 L 353 645", (331, 754)),
}


def automaton():
    trie = [dict() for _ in POINTS]
    for u, char, v in EDGES:
        trie[u][char] = v
    alphabet = sorted({char for _, char, _ in EDGES})
    fail = [0] * len(trie)
    go = [dict() for _ in trie]
    order = []
    queue = deque([0])
    while queue:
        u = queue.popleft()
        order.append(u)
        # The insertion order preserves the original illustration's BFS order.
        for char, v in trie[u].items():
            fail[v] = go[fail[u]].get(char, 0) if u else 0
            queue.append(v)
        for char in alphabet:
            go[u][char] = trie[u].get(char, go[fail[u]].get(char, 0) if u else 0)
    return trie, fail, go, order


TRIE, FAIL, GO, ORDER = automaton()
EXTRAS = {
    (u, char): v
    for u in POINTS
    for char, v in GO[u].items()
    if char not in TRIE[u] and v
}
assert FAIL == [0, 0, 0, 0, 7, 10, 7, 0, 1, 2, 0]
assert set(EXTRAS) == set(EXTRA_ROUTES)


@dataclass
class Scene:
    caption: str
    done: set[int] = field(default_factory=set)
    failures: set[int] = field(default_factory=set)
    new_failures: set[int] = field(default_factory=set)
    completed: set[int] = field(default_factory=set)
    current: int | None = None
    kind: str = "new"
    move: tuple[int, str, int] | None = None
    text_index: int | None = None
    match: int | None = None
    failure_match: bool = False
    duration: float = 1.5


def label(x, y, value, color="#26313d", size=EDGE_TEXT_SIZE, anchor="middle"):
    attrs = f'x="{x}" y="{y}" text-anchor="{anchor}" font-size="{size}"'
    value = escape(str(value))
    return f'<text {attrs} fill="{color}">{value}</text>'


def path(d, kind, width=2.8, arrow=True):
    marker = f' marker-end="url(#arrow-{kind})"' if arrow else ""
    return (
        f'<path d="{d}" fill="none" stroke="{COLORS[kind]}" '
        f'stroke-width="{width}" stroke-linecap="round"{marker}/>'
    )


def line(u, v):
    x1, y1 = POINTS[u]
    x2, y2 = POINTS[v]
    dx, dy = x2 - x1, y2 - y1
    length = hypot(dx, dy)
    dx, dy = dx / length * (RADIUS + 3), dy / length * (RADIUS + 3)
    return f"M {x1 + dx:.2f} {y1 + dy:.2f} L {x2 - dx:.2f} {y2 - dy:.2f}"


def pattern_edges(state):
    parents = {v: (u, char) for u, char, v in EDGES}
    result = []
    while state:
        parent, char = parents[state]
        result.append((parent, char, state))
        state = parent
    return result


def draw(scene):
    pieces = [f'<rect width="{WIDTH}" height="{HEIGHT}" fill="white"/>']
    if scene.text_index is not None:
        for index, char in enumerate(TEXT):
            color = COLORS["new"] if index == scene.text_index else "#26313d"
            pieces.append(label(50 + index * 44, 50, char, color, INPUT_TEXT_SIZE))
        if scene.match is not None:
            pattern = PATTERNS[scene.match]
            start = scene.text_index - len(pattern) + 1
            for index, char in enumerate(pattern):
                pieces.append(
                    label(
                        50 + (start + index) * 44,
                        95,
                        char,
                        COLORS["match"],
                        MATCH_TEXT_SIZE,
                    )
                )
    # Keep a clear band above the graph for the larger matching strings.
    pieces.append(f'<g transform="translate(0,{GRAPH_TOP})">')
    for u, char, v in EDGES:
        pieces.append(path(line(u, v), "trie", 3.2, False))
    for u in sorted(scene.failures):
        kind = "new" if u in scene.new_failures else "fail"
        pieces.append(path(FAIL_ROUTES[u], kind))
    for (u, char), v in EXTRAS.items():
        if u in scene.completed:
            kind = (
                "current" if scene.kind == "current" and u == scene.current else "extra"
            )
            d, (x, y) = EXTRA_ROUTES[u, char]
            pieces.append(path(d, kind))
            pieces.append(label(x, y, char, COLORS[kind]))
    if scene.match is not None:
        for u, char, v in pattern_edges(scene.match):
            pieces.append(path(line(u, v), "match", 5, False))
        if scene.failure_match:
            u = scene.current
            while u != scene.match:
                pieces.append(path(FAIL_ROUTES[u], "match", 4))
                u = FAIL[u]
    # Draw the movement arrow above the matched path when they share an edge.
    if scene.move is not None:
        u, char, v = scene.move
        if char in TRIE[u]:
            d = line(u, v)
        elif (u, char) in EXTRA_ROUTES:
            d = EXTRA_ROUTES[u, char][0]
        else:
            # The first character, 'u', keeps the matching state at the root.
            assert u == v == 0
            d = FAIL_ROUTES[0]
        pieces.append(path(d, "move", 5))
    for u, char, v in EDGES:
        x, y = TRIE_LABELS[u, v]
        pieces.append(label(x, y, char, COLORS["label"], TRIE_TEXT_SIZE))
    for u, (x, y) in POINTS.items():
        fill = FILLS["done"] if u in scene.done else "white"
        if u == scene.current:
            fill = FILLS[scene.kind]
        if u == scene.match and scene.failure_match:
            fill = FILLS["match"]
        pieces.append(
            f'<circle cx="{x}" cy="{y}" r="{RADIUS}" '
            f'fill="{fill}" stroke="#8b959e" stroke-width="2.8"/>'
        )
        pieces.append(
            f'<text x="{x}" y="{y + 17}" text-anchor="middle" '
            f'font-size="{STATE_TEXT_SIZE}" fill="#26313d">{u}</text>'
        )
    pieces.append("</g>")
    return "\n".join(pieces)


def document(title, description, content):
    markers = []
    for kind, color in COLORS.items():
        markers.append(
            f'<marker id="arrow-{kind}" viewBox="0 0 10 10" '
            'refX="9" refY="5" markerWidth="18" markerHeight="18" '
            'orient="auto" markerUnits="userSpaceOnUse">'
            f'<path d="M 0 0 L 10 5 L 0 10" fill="none" '
            f'stroke="{color}" stroke-width="1.8"/></marker>'
        )
    return (
        f'<?xml version="1.0" encoding="UTF-8"?>\n'
        "<!-- Generated by ac-automaton.py; edit that source to regenerate. -->\n"
        f'<svg xmlns="http://www.w3.org/2000/svg" version="1.1" '
        f'width="{WIDTH}" height="{HEIGHT}" viewBox="0 0 {WIDTH} {HEIGHT}">\n'
        f"<title>{escape(title)}</title>\n<desc>{escape(description)}</desc>\n"
        "<defs>\n" + "\n".join(markers) + "\n</defs>\n"
        '<g font-family="Arial, Helvetica, sans-serif">\n'
        + content
        + "\n</g>\n</svg>\n"
    )


def animated(frames, fallback):
    duration = sum(frame.duration for frame in frames)
    # Nonanimating SVG consumers show the complete diagram; SMIL hides it.
    pieces = [
        "<g>\n"
        + draw(fallback)
        + '\n<set attributeName="visibility" to="hidden" begin="0s" dur="indefinite"/>\n</g>'
    ]
    elapsed = 0
    for i, frame in enumerate(frames):
        start, end = elapsed / duration, (elapsed + frame.duration) / duration
        if i == 0:
            times, values = f"0;{end:.8f};1", "visible;hidden;hidden"
        elif i == len(frames) - 1:
            times, values = f"0;{start:.8f};1", "hidden;visible;visible"
        else:
            times = f"0;{start:.8f};{end:.8f};1"
            values = "hidden;visible;hidden;hidden"
        pieces.append(
            f'<g visibility="hidden">\n<title>{escape(frame.caption)}</title>\n'
            + draw(frame)
            + f'\n<animate attributeName="visibility" '
            f'values="{values}" keyTimes="{times}" calcMode="discrete" '
            f'dur="{duration:g}s" repeatCount="indefinite"/>\n</g>'
        )
        elapsed += frame.duration
    return "\n".join(pieces)


def scenes():
    all_states = set(POINTS)
    fail_frames = [Scene("BFS: construct failure pointers", duration=1)]
    done = set()
    for u in ORDER:
        fail_frames.append(
            Scene(
                f"fail[{u}] = {FAIL[u]}",
                done.copy(),
                done | {u},
                {u},
                current=u,
                duration=1,
            )
        )
        done.add(u)
    fail_final = Scene("Failure pointers", all_states, all_states, duration=2)
    fail_frames.append(fail_final)

    # Initially, the root and its immediate children have failure pointers.
    known = {0, *TRIE[0].values()}
    done = {0}
    build_frames = [
        Scene(
            "BFS: complete the transition function",
            done.copy(),
            known.copy(),
            duration=2,
        )
    ]
    build_focus = None
    for u in ORDER[1:]:
        children = set(TRIE[u].values())
        known |= children
        scene = Scene(
            f"u = {u}: complete transitions; set children's failure pointers",
            done.copy(),
            known.copy(),
            children,
            done | {u},
            u,
            "current",
            duration=2,
        )
        build_frames.append(scene)
        if u == 5:
            build_focus = replace(
                scene, caption="fail[6] = trans[fail[5]][s] = trans[10][s] = 7"
            )
        done.add(u)
    completed = Scene(
        "Completed automaton (transitions to the root omitted)",
        all_states,
        all_states,
        completed=all_states,
        duration=3,
    )
    build_frames.append(completed)

    match_frames = [
        replace(completed, caption="Match: " + TEXT, text_index=-1, duration=2.5)
    ]
    u = 0
    for index, char in enumerate(TEXT):
        previous, u = u, GO[u].get(char, 0)
        matched = u
        outputs = []
        while matched:
            if matched in PATTERNS:
                outputs.append(matched)
            matched = FAIL[matched]
        basic = replace(
            completed,
            caption=f"p = trans[{previous}][{char}] = {u}",
            current=u,
            kind="move",
            move=(previous, char, u),
            text_index=index,
            duration=2.5,
        )
        if not outputs:
            match_frames.append(basic)
        else:
            for matched in outputs:
                match_frames.append(
                    replace(
                        basic,
                        match=matched,
                        failure_match=matched != u,
                        caption=basic.caption + "; match: " + PATTERNS[matched],
                    )
                )
    # Verify the full search trace, including transitions introduced by failure.
    trace = []
    u = 0
    for char in TEXT:
        u = GO[u].get(char, 0)
        trace.append(u)
    assert trace == [0, 7, 8, 9, 3, 4, 8, 9, 10, 7, 8, 5, 6]

    focus6 = next(frame for frame in fail_frames if frame.current == 6)
    static = {
        "ac-automaton1.svg": (
            replace(focus6, caption="fail[6] = 7"),
            "Failure pointer of state 6",
        ),
        "ac-automaton2.svg": (
            build_focus,
            "Computing fail[6] with completed transitions",
        ),
        "ac-automaton3.svg": (completed, "The complete AC automaton"),
        "ac-automaton4.svg": (fail_final, "All failure pointers"),
    }
    animations = {
        "ac-automaton-build-fail.svg": (
            fail_frames,
            fail_final,
            "Construct failure pointers in BFS order",
        ),
        "ac-automaton-build-transitions.svg": (
            build_frames,
            completed,
            "Construct the completed transition function",
        ),
        "ac-automaton-match.svg": (
            match_frames,
            completed,
            "Match ushersheishis with the AC automaton",
        ),
    }
    return static, animations


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--frames", type=Path, help="also export every animation frame as a static SVG"
    )
    args = parser.parse_args()
    destination = Path(__file__).resolve().parent
    static, animations = scenes()
    description = (
        "Patterns: i, he, his, she, hers. States 0 to 10 retain the article's numbering. "
        "Gray edges are trie edges; orange arrows are failure pointers. "
        "Black arrows are completed transitions; transitions to state 0 are omitted."
    )
    for name, (scene, title) in static.items():
        (destination / name).write_text(
            document(title, description, draw(scene)), encoding="utf-8"
        )
    for name, (frames, fallback, title) in animations.items():
        (destination / name).write_text(
            document(title, description, animated(frames, fallback)), encoding="utf-8"
        )
        if args.frames:
            args.frames.mkdir(parents=True, exist_ok=True)
            for index, frame in enumerate(frames):
                path = args.frames / f"{Path(name).stem}-{index:02}.svg"
                path.write_text(
                    document(frame.caption, description, draw(frame)), encoding="utf-8"
                )
    print(f"Generated {len(static)} static SVGs and {len(animations)} SVG animations.")


if __name__ == "__main__":
    main()

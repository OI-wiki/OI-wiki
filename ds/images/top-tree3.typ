#import "@preview/fletcher:0.5.1": *
#set page(height: auto, width: auto, fill: white)
#set text(
  lang: "zh",
  region: "cn",
  font: ("New Computer Modern", "Source Han Serif SC"),
)

#let node_positions = (
  A: (0, 0),
  B: (-1, 1),
  C: (0, 1),
  D: (1, 0),
  E: (-1.5, 2),
  F: (-0.5, 2),
  G: (1, 1),
  H: (1, 2),
)

#let graph(nodes, edges, caption) = {
  diagram(
    node-stroke: 1pt,
    node-fill: white,
    edge-stroke: 1pt,
    spacing: 1cm,
    ..nodes,
    ..edges,
    node((0, 1.5), caption, stroke: none),
  )
}

#let create_node(label1) = {
  node(node_positions.at(label1), [#label1], name: label(label1))
}

#let create_edge(from, to) = {
  edge(label(from), label(to))
}

#let original = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("C"),
    create_node("D"),
    create_node("E"),
    create_node("F"),
    create_node("G"),
    create_node("H"),
  ),
  (
    create_edge("A", "B"),
    create_edge("A", "C"),
    create_edge("A", "D"),
    create_edge("B", "E"),
    create_edge("B", "F"),
    create_edge("D", "G"),
    create_edge("G", "H"),
  ),
  [原树T],
)

#let compress_g = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("C"),
    create_node("D"),
    create_node("E"),
    create_node("F"),
    create_node("H"),
  ),
  (
    create_edge("A", "B"),
    create_edge("A", "C"),
    create_edge("A", "D"),
    create_edge("B", "E"),
    create_edge("B", "F"),
    create_edge("D", "H"),
  ),
  [Compress(G)],
)

#let rake_c = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("D"),
    create_node("E"),
    create_node("F"),
    create_node("H"),
  ),
  (
    create_edge("A", "B"),
    create_edge("A", "D"),
    create_edge("B", "E"),
    create_edge("B", "F"),
    create_edge("D", "H"),
  ),
  [Rake(C)],
)

#let compress_d = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("E"),
    create_node("F"),
    create_node("H"),
  ),
  (
    create_edge("A", "B"),
    create_edge("A", "H"),
    create_edge("B", "E"),
    create_edge("B", "F"),
  ),
  [Compress(D)],
)

#let rake_f = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("E"),
    create_node("H"),
  ),
  (
    create_edge("A", "B"),
    create_edge("A", "H"),
    create_edge("B", "E"),
  ),
  [Rake(F)],
)

#let compress_b = graph(
  (
    create_node("A"),
    create_node("E"),
    create_node("H"),
  ),
  (
    create_edge("A", "E"),
    create_edge("A", "H"),
  ),
  [Compress(B)],
)

#let rake_h = graph(
  (
    create_node("A"),
    create_node("E"),
  ),
  (create_edge("A", "E"),),
  [Rake(H)],
)

#grid(
  columns: (auto, auto, auto),
  row-gutter: 1cm,
  column-gutter: 1cm,
  original, compress_g, rake_c,
  compress_d, rake_f, compress_b,
  rake_h,
)

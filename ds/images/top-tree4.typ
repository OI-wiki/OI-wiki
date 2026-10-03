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
  C: (0.5, 1),
  D: (1.5, 1),
  E: (-1, 2),
  F: (-0.3, 2),
  G: (1.5, 2),
  H: (2, 3),
)

#let graph(nodes, edges, caption, highlights) = {
  diagram(
    node-stroke: 1pt,
    node-fill: white,
    edge-stroke: 1pt,
    spacing: 1cm,
    ..nodes,
    ..edges,
    highlights,
    node((0, 3.5), caption, stroke: none),
  )
}

#let create_node(label1) = {
  node(node_positions.at(label1), [#label1], name: label(label1))
}

#let create_edge(from, to) = {
  edge(label(from), label(to))
}

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
  edge(<A>, <H>, stroke: red + 2pt),
)

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
  node(
    enclose: (<C>, <D>, <G>),
    corner-radius: 10pt,
    snap: -1,
    stroke: red + 2pt,
    inset: 1em,
  ),
)

#let arrow = node((rel: (50%, 0%)), [=>], stroke: none)

#grid(
  columns: (auto, auto, auto),
  column-gutter: 0.5cm,
  rake_f, arrow, original,
)

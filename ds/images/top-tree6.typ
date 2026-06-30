#import "@preview/fletcher:0.5.1": *
#set page(height: auto, width: auto, fill: white)
#set text(
  lang: "zh",
  region: "cn",
  font: ("New Computer Modern", "Source Han Serif SC"),
)

#let node_positions0 = (
  A: (0, 0),
  B: (-1, 1),
  C: (0, 1),
  D: (1, 1.5),
  E: (-1, 4.5),
  F: (-0.5, 2),
  G: (1, 2.5),
  H: (1, 3.6),
)

#let graph(nodes, edges, caption) = {
  diagram(
    node-stroke: 1pt,
    node-fill: white,
    edge-stroke: 1pt,
    spacing: 1cm,
    ..nodes,
    ..edges,
    node((0, 3.5), caption, stroke: none),
  )
}

#let create_node(label1, node_positions: node_positions0) = {
  node(node_positions.at(label1), [#label1], name: label(label1))
}

#let create_edge(from, to, style: ()) = {
  edge(label(from), label(to), ..style)
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
    create_edge("A", "B", style: (stroke: red + 2pt)),
    create_edge("A", "C", style: (stroke: red + 2pt)),
    create_edge("A", "D", style: (stroke: red + 2pt)),
    create_edge("B", "E", style: (stroke: red + 2pt)),
    create_edge("B", "F", style: (stroke: red + 2pt)),
    create_edge("D", "G", style: (stroke: red + 2pt)),
    create_edge("G", "H", style: (stroke: red + 2pt)),
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
    create_node("G"),
    node(
      (to: <G>, rel: (0mm, 0mm)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 5em,
      width: 3em,
      outset: 10em,
      fill: none,
    ),
    create_node("H"),
  ),
  (
    create_edge("A", "B", style: (stroke: red + 2pt)),
    create_edge("A", "C", style: (stroke: red + 2pt)),
    create_edge("A", "D", style: (stroke: red + 2pt)),
    create_edge("B", "E", style: (stroke: red + 2pt)),
    create_edge("B", "F", style: (stroke: red + 2pt)),
    create_edge("D", "G"),
    create_edge("G", "H"),
  ),
  [Compress(G)],
)

#let rake_c = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("C"),
    create_node("D"),
    create_node("E"),
    create_node("F"),
    create_node("G"),
    create_node("H"),
    node(
      (to: <G>, rel: (0mm, 0mm)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 5em,
      width: 3em,
      outset: 10em,
      fill: none,
    ),
    node(
      (to: <C>, rel: (1.5em, 0.7em)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 4em,
      width: 7em,
      outset: 10em,
      fill: none,
    ),
  ),
  (
    create_edge("A", "B", style: (stroke: red + 2pt)),
    create_edge("A", "C"),
    create_edge("A", "D"),
    create_edge("B", "E", style: (stroke: red + 2pt)),
    create_edge("B", "F", style: (stroke: red + 2pt)),
    create_edge("D", "G"),
    create_edge("G", "H"),
  ),
  [Rake(C)],
)

#let compress_d = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("C"),
    create_node("D"),
    create_node("E"),
    create_node("F"),
    create_node("G"),
    create_node("H"),
    node(
      (to: <G>, rel: (-3.5em, 3em)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 10em,
      width: 10em,
      fill: none,
    ),
  ),
  (
    create_edge("A", "B", style: (stroke: red + 2pt)),
    create_edge("A", "C"),
    create_edge("A", "D"),
    create_edge("B", "E", style: (stroke: red + 2pt)),
    create_edge("B", "F", style: (stroke: red + 2pt)),
    create_edge("D", "G"),
    create_edge("G", "H"),
  ),
  [Compress(D)],
)

#let rake_f = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("C"),
    create_node("D"),
    create_node("E"),
    create_node("F"),
    create_node("G"),
    create_node("H"),
    node(
      (to: <G>, rel: (-3.5em, 3em)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 10em,
      width: 11em,
      fill: none,
    ),
    node(
      (to: <F>, rel: (-2em, 0em)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 5em,
      width: 7em,
      fill: none,
    ),
  ),
  (
    create_edge("A", "B", style: (stroke: red + 2pt)),
    create_edge("A", "C"),
    create_edge("A", "D"),
    create_edge("B", "E"),
    create_edge("B", "F"),
    create_edge("D", "G"),
    create_edge("G", "H"),
  ),
  [Rake(F)#h(3em)],
)

#let compress_b = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("C"),
    create_node("D"),
    create_node("E"),
    create_node("F"),
    create_node("G"),
    create_node("H"),
    node(
      (to: <G>, rel: (-3.5em, 3em)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 10em,
      width: 11em,
      fill: none,
    ),
    node(
      (to: <F>, rel: (-2em, 3em)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 9em,
      width: 7em,
      fill: none,
    ),
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
  [Compress(B)#h(1em)],
)

#let rake_h = graph(
  (
    create_node("A"),
    create_node("B"),
    create_node("C"),
    create_node("D"),
    create_node("E"),
    create_node("F"),
    create_node("G"),
    create_node("H"),
    node(
      (to: <G>, rel: (-6em, 1.5em)),
      stroke: red + 2pt,
      corner-radius: 1em,
      height: 14em,
      width: 16em,
      fill: none,
    ),
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

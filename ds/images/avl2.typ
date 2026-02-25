#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge

#set page(height: auto, width: auto, fill: white)

#diagram(
  node-stroke: 1pt,
  node-fill: white, 
  edge-stroke: 1pt,
  {
    let (d1, b1, e1, a1, c1) = ((2,1),(1,3),(3,3),(0,5),(2,5))
    let (b2, a2, d2, c2, e2) = ((11,1), (10,3),(12,3),(11,5),(13,5))

    node(d1, [D])
    node(b1, [B])
    node(e1, [E])
    node(a1, [A])
    node(c1, [C])

    edge(d1, b1)
    edge(d1, e1)
    edge(b1, a1)
    edge(b1, c1)
    edge(e1, (e1.at(0) - 0.6, 4.3))
    edge(e1, (e1.at(0) + 0.6, 4.3))
    edge(a1, (a1.at(0) - 0.6, 6.3))
    edge(a1, (a1.at(0) + 0.6, 6.3))
    edge(c1, (c1.at(0) - 0.6, 6.3))
    edge(c1, (c1.at(0) + 0.6, 6.3))

    edge((5, 3), (8, 3), "->", text(size: 18pt, [RightRotate(D)]))

    node(d2, [D])
    node(b2, [B])
    node(e2, [E])
    node(a2, [A])
    node(c2, [C])

    edge(b2, a2)
    edge(b2, d2)
    edge(d2, c2)
    edge(d2, e2)
    edge(e2, (e2.at(0) - 0.6, 6.3))
    edge(e2, (e2.at(0) + 0.6, 6.3))
    edge(a2, (a2.at(0) - 0.6, 4.3))
    edge(a2, (a2.at(0) + 0.6, 4.3))
    edge(c2, (c2.at(0) - 0.6, 6.3))
    edge(c2, (c2.at(0) + 0.6, 6.3))
  }
)

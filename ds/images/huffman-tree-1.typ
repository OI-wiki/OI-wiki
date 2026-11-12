#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge

#set page(height: auto, width: auto, fill: white)

#diagram(
  node-stroke: 1pt,
  node-fill: white, 
  edge-stroke: 1pt,
  {
    let (n1, n2, n3, n4, n5, n6, n7) = ((3, 1), (2, 2), (4, 2), (1, 3), (2.6, 3), (3.6, 3), (5, 3))

    node(n1, ` `)
    node(n2, ` `)
    node(n3, ` `)
    node(n4, [2])
    node(n5, [3])
    node(n6, [4])
    node(n7, [7])

    edge(n1, n2)
    edge(n1, n3)
    edge(n2, n4)
    edge(n2, n5)
    edge(n3, n6)
    edge(n3, n7)
  }
)

#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge

#set page(height: auto, width: auto, fill: white)
#let zh(str) = [#text(font: "Noto Sans")[#str]]

#grid(
  columns: 2,
  gutter: 30pt,
  [
    #diagram(
      node-stroke: 1pt,
      node-fill: white,
      edge-stroke: 1pt,
      {
        let (n100, n40, n60, n25, nB, nC, nA, nE, nD) = (
          (3, 0), (2, 1), (4, 1), (3.4, 2), (1.4, 2), (2.6, 2), (4.6, 2), (2.8, 3), (4, 3)
        )

        node(n100, [100], shape: "rect")
        node(n40, [40], shape: "rect")
        node(n60, [60], shape: "rect")
        node(n25, [25], shape: "rect")
        node(nB, [B(25)], shape: "circle")
        node(nC, [C(15)], shape: "circle")
        node(nA, [A(35)], shape: "circle")
        node(nE, [E(10)], shape: "circle")
        node(nD, [D(15)], shape: "circle")  

        edge(n100, n40)
        edge(n100, n60)
        edge(n40, nB)
        edge(n40, nC)
        edge(n60, nA)
        edge(n60, n25)
        edge(n25, nE)
        edge(n25, nD)
      }
    )
  ],
  
  [
    #table(
      columns: (auto, auto, auto),
      inset: 10pt,
      align: (center, center, center),
      table.header(
        [#zh("字符")], [#zh("频率")], [#zh("编码")]
      ),
      [A], [35], [11],
      [B], [25], [00],
      [C], [15], [01],
      [D], [15], [101],
      [E], [10], [100],
    )
  ]
)

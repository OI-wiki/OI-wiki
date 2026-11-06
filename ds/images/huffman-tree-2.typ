#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge

#set page(height: auto, width: auto, fill: white)

#diagram(
  node-stroke: 1pt,
  node-fill: white, 
  edge-stroke: 1pt,
  {
    // 第一部分
    let l1 = 0
    let (n1_1, n1_2, n1_3, n1_4) = ((l1, 1), (l1 + 0.5, 1), (l1 + 1, 1), (l1 + 1.5, 1))
    
    node(n1_1, [2])
    node(n1_2, [4])
    node(n1_3, [5])
    node(n1_4, [3])

    // 第二部分
    let l2 = 2.7
    let (n2_1, n2_2, n2_3, n2_4, n2_5) = ((l2, 1), (l2 + 0.5, 1), (l2 + 1.2, 1), (l2 + 0.9, 1.7), (l2 + 1.5, 1.7))  
    
    node(n2_1, [4])
    node(n2_2, [5])
    node(n2_3, [5], shape: "rect")
    node(n2_4, [2])
    node(n2_5, [3])

    edge(n2_3, n2_4)
    edge(n2_3, n2_5)

    // 第三部分
    let l3 = 5.7
    let (n3_1, n3_2, n3_3, n3_4, n3_5, n3_6) = ((l3, 1), (l3 + 1.2, 1), (l3 - 0.3, 1.7), (l3 + 0.3, 1.7), (l3 + 0.9, 1.7), (l3 + 1.5, 1.7))

    node(n3_1, [5], shape: "rect")
    node(n3_2, [9], shape: "rect")
    node(n3_3, [2])
    node(n3_4, [3])
    node(n3_5, [4])
    node(n3_6, [5])
    
    edge(n3_1, n3_3)
    edge(n3_1, n3_4)
    edge(n3_2, n3_5)
    edge(n3_2, n3_6)

    // 第四部分
    let l4 = 9.3
    let (n4_1, n4_2, n4_3, n4_4, n4_5, n4_6, n4_7) = ((l4, 0.3), (l4 - 0.6, 1), (l4 + 0.6, 1), (l4 - 0.9, 1.7), (l4 - 0.3, 1.7), (l4 + 0.3, 1.7), (l4 + 0.9, 1.7))

    node(n4_1, [14], shape: "rect")
    node(n4_2, [5], shape: "rect")
    node(n4_3, [9], shape: "rect")
    node(n4_4, [2])
    node(n4_5, [3])
    node(n4_6, [4])
    node(n4_7, [5])

    edge(n4_1, n4_2)
    edge(n4_1, n4_3)
    edge(n4_2, n4_4)
    edge(n4_2, n4_5)
    edge(n4_3, n4_6)
    edge(n4_3, n4_7)
  }
)

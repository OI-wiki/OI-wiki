#set page(width: auto, height: auto, margin: 0.5cm)
#set text(font: "Noto Sans CJK SC", 12pt)

#table(
  columns: 9,
  align: right,
  row-gutter: 5pt,
  stroke: (x, y) => (
    y: if x > 0 { 0.6pt },
    left: if calc.rem(x, (8 / (calc.pow(2, y)))) == 1 { 0.6pt },
    right: if calc.rem(x, (8 / (calc.pow(2, y)))) == 0 { 0.6pt },
  ),
  [*原数组*], text(red)[$1$], $5$, $6$, text(red)[$3$], $8$, text(red)[$4$], $4$, text(red)[$2$],
  [*第一层*], text(red)[$1$], $3$, $4$, text(red)[$2$], text(red)[$5$], $6$, $8$, text(red)[$4$],
  [*第二层*], text(red)[$1$], $2$, text(red)[$3$], $4$, $5$, text(red)[$4$], text(red)[$6$], $8$,
  [#text(8pt)[（$log n$）]*第三层*], $1$, $2$, $3$, $4$, $4$, $5$, $6$, $8$,
)

#pagebreak()

#table(
  columns: 8,
  row-gutter: 10pt,
  stroke: (x, y) => (
    y: if x + y >= 2 and x + 4 * y <= 6 { 1pt + yellow },
    left: if x + y == 2 { 1pt + yellow },
    right: if x + 4 * y == 6 { 1pt + yellow },
  ),
  text(red)[$1$], $5$, $6$, text(red)[$underline(3)$], $8$, text(red)[$underline(4)$], $4$, text(red)[$2$],
  text(red)[$1$], $underline(3)$, $underline(4)$, text(red)[$2$], // text(silver)[$5$], text(silver)[$6$], text(silver)[$8$], text(silver)[$4$],
)

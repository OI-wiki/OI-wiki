#set page(width: auto, height: auto, margin: 0.5cm)
#set text(font: "Noto Sans CJK SC", 12pt)
#set table(stroke: 0.6pt, align: center)

#let valid(colspan) = table.cell(colspan: colspan, fill: rgb("#57be6a"), text(white, 14pt)[*合法*])
#let invalid(colspan) = table.cell(colspan: colspan, fill: rgb("#e75e58"), text(white, 14pt)[*不合法*])
#let dots = [$dots.h$] * 2

#table(
  columns: 7 * (1.8cm,),
  valid(3), invalid(4),
  [最小值], [$"L"$], [$"MID"$],
  [$"R"$], dots, dots, [最大值],
)

#align(center, text(14pt)[或者])

#table(
  columns: 7 * (1.8cm,),
  valid(4), invalid(3),
  [最小值], dots, dots, [$"L"$],
  [$"MID"$], [$"R"$], [最大值],
)

#pagebreak()

#table(
  columns: 7 * (1.8cm,),
  valid(3), invalid(4),
  [最小值], dots, [$"L,MID"$],
  [$"R"$], dots, dots, [最大值],
)

#align(center, text(14pt)[或者])

#table(
  columns: 7 * (1.8cm,),
  valid(4), invalid(3),
  [最小值], dots, dots, [$"L"$],
  [$"MID,R"$], dots, [最大值],
)

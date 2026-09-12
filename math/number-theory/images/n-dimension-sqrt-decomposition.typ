#set page(width: 15.4cm, height: 7.3cm, margin: 0cm)
#set text(font: "Noto Sans CJK SC", 7pt)

#let pair-sum((x1, y1), (x2, y2)) = (x1 + x2, y1 + y2)

#let (dx0, dy0) = (2.5, 0.5)
#let dx = (10, 7, 11, 12, 18, 25, 7, 8)
#for i in range(dx.len()) {
  dx.at(i) = if i > 0 { dx.at(i - 1) } else { 0 } + dx.at(i) * 0.05
}
#let dy = 0.35

#let point((x, y)) = (
  (
    if x == 0 { 0 } else { dx0 + if x > 1 { dx.at(x - 2) } else { 0 } } * 1cm,
    (y * dy + dy0) * 1cm,
  )
)
#let point-pair-transform((x, y), step) = pair-sum((x, y), if step > 0 {
  (step, 0)
} else { (0, -step) })

#let line-draw(start, step: 1, color: black) = place(
  line(
    start: point(start),
    end: point(point-pair-transform(start, step)),
    stroke: color + 1.5pt,
  ),
)

#let lines-draw(start, steps, color) = {
  let line-start = start
  for step in steps {
    line-draw(line-start, step: step, color: color)
    line-start = point-pair-transform(line-start, step)
  }
}

#scale(200%)[
  #let grid = 0
  #while grid <= dx.len() {
    place(
      line(
        start: ((dx0 + if grid >= 1 { dx.at(grid - 1) } else { 0 }) * 1cm, 0cm),
        length: 3.65cm,
        angle: 90deg,
        stroke: blue + 0.5pt,
      ),
    )
    grid += 1
  }
  
  #lines-draw((0, 0), (1, -3, 3, -2, 3, -4), black)
  #lines-draw((0, 1), (2, -3, 3, -3, 3, -2), red)
  #lines-draw((0, 2), (3, -4, 3, -2, 3, -1), green)
  
  #place(
    top + left,
    dx: (dx0 * 1cm - 9 * 7.2pt) / 2,
    dy: 1.8cm,
    text()[蓝色细线代表数论分\ 块的边界\ 这样分就可以让每一\ 块里面的 $floor(n_j / i)$ 相同],
  )
]

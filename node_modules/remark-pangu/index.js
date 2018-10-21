'use strict'

var visit = require('unist-util-visit')
var is = require('unist-util-is')
var pangu = require('pangu')

// List of Markdown AST: <https://github.com/syntax-tree/mdast>
// AST Explorer: <https://astexplorer.net/#/gist/7a794a8fc43b2e75e27024c85fb77aad/0934495eb735dffdf739dc7943f7848940070f8e>
//
// AST we should format:
// 1. text node:
//    * paragraph children
//    * blockquote children
//    * heading children
//    * emphasis children
//    * strong children
//    * listItems children
//    * tableCell children
//    * delete children
//    * link children
//    * image children
//    * footnote children
// 2. inlineCode value
// 3. link title
// 4. image title/alt
// 5. imageReference alt
// 6. definition title
//
//
// AST we ignored:
// 1. YAML
// 2. html (it can contain link: <a> <img>)
// 3. 临接情况
//     1. 粗体：我的a**粗体**
//     2. 强调：我的a*强调*
//     3. ...

function format(value) {
  if (!value) return value
  return pangu.spacing(value)
}

function visitor(node) {
  if (is('text', node) || is('inlineCode', node)) {
    node.value = format(node.value)
  }

  if (is('link', node) || is('image', node) || is('definition', node)) {
    node.title = format(node.title)
  }

  if (is('image', node) || is('imageReference', node)) {
    node.alt = format(node.alt)
  }
}

module.exports = function attacher() {
  return function transformer(tree, file) {
    visit(tree, visitor)
  }
}

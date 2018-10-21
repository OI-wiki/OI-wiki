/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module definition-spacing
 * @fileoverview
 *   Warn when consecutive white space is used in a definition.
 *
 * @example {"name": "valid.md"}
 *
 *   [example domain]: http://example.com "Example Domain"
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   [example····domain]: http://example.com "Example Domain"
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   1:1-1:57: Do not use consecutive white-space in definition labels
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:definition-spacing', definitionSpacing)

var label = /^\s*\[((?:\\[\s\S]|[^[\]])+)]/
var reason = 'Do not use consecutive white-space in definition labels'

function definitionSpacing(tree, file) {
  var contents = String(file)

  visit(tree, ['definition', 'footnoteDefinition'], validate)

  function validate(node) {
    var start = position.start(node).offset
    var end = position.end(node).offset

    if (
      !generated(node) &&
      /[ \t\n]{2,}/.test(contents.slice(start, end).match(label)[1])
    ) {
      file.message(reason, node)
    }
  }
}

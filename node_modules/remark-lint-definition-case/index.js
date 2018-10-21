/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module definition-case
 * @fileoverview
 *   Warn when definition labels are not lower-case.
 *
 * @example {"name": "valid.md"}
 *
 *   [example]: http://example.com "Example Domain"
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   [Example]: http://example.com "Example Domain"
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   1:1-1:47: Do not use upper-case characters in definition labels
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:definition-case', definitionCase)

var label = /^\s*\[((?:\\[\s\S]|[^[\]])+)]/
var reason = 'Do not use upper-case characters in definition labels'

function definitionCase(tree, file) {
  var contents = String(file)

  visit(tree, ['definition', 'footnoteDefinition'], validate)

  /* Validate a node, either a normal definition or
   * a footnote definition. */
  function validate(node) {
    var start = position.start(node).offset
    var end = position.end(node).offset
    var value

    if (!generated(node)) {
      value = contents.slice(start, end).match(label)[1]

      if (value !== value.toLowerCase()) {
        file.message(reason, node)
      }
    }
  }
}

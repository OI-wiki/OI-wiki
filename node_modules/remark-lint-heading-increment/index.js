/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module heading-increment
 * @fileoverview
 *   Warn when headings increment with more than 1 level at a time.
 *
 * @example {"name": "valid.md"}
 *
 *   # Alpha
 *
 *   ## Bravo
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   # Charlie
 *
 *   ### Delta
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   3:1-3:10: Heading levels should increment by one level at a time
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:heading-increment', headingIncrement)

var reason = 'Heading levels should increment by one level at a time'

function headingIncrement(tree, file) {
  var prev = null

  visit(tree, 'heading', visitor)

  function visitor(node) {
    var depth

    if (!generated(node)) {
      depth = node.depth

      if (prev && depth > prev + 1) {
        file.message(reason, node)
      }

      prev = depth
    }
  }
}

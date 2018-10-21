/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module no-duplicate-headings
 * @fileoverview
 *   Warn when duplicate headings are found.
 *
 * @example {"name": "valid.md"}
 *
 *   # Foo
 *
 *   ## Bar
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   # Foo
 *
 *   ## Foo
 *
 *   ## [Foo](http://foo.com/bar)
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   3:1-3:7: Do not use headings with similar content (1:1)
 *   5:1-5:29: Do not use headings with similar content (3:1)
 */

'use strict'

var rule = require('unified-lint-rule')
var position = require('unist-util-position')
var generated = require('unist-util-generated')
var visit = require('unist-util-visit')
var stringify = require('unist-util-stringify-position')
var toString = require('mdast-util-to-string')

module.exports = rule('remark-lint:no-duplicate-headings', noDuplicateHeadings)

var reason = 'Do not use headings with similar content'

function noDuplicateHeadings(tree, file) {
  var map = {}

  visit(tree, 'heading', visitor)

  function visitor(node) {
    var value
    var duplicate

    if (!generated(node)) {
      value = toString(node).toUpperCase()
      duplicate = map[value]

      if (duplicate && duplicate.type === 'heading') {
        file.message(
          reason + ' (' + stringify(position.start(duplicate)) + ')',
          node
        )
      }

      map[value] = node
    }
  }
}

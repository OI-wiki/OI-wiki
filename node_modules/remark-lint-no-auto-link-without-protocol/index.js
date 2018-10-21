/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module no-auto-link-without-protocol
 * @fileoverview
 *   Warn for angle-bracketed links without protocol.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   adds a protocol where needed.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md"}
 *
 *   <http://www.example.com>
 *   <mailto:foo@bar.com>
 *
 *   Most markdown vendors don’t recognize the following as a link:
 *   <www.example.com>
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   <foo@bar.com>
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   1:1-1:14: All automatic links must start with a protocol
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')
var toString = require('mdast-util-to-string')

module.exports = rule(
  'remark-lint:no-auto-link-without-protocol',
  noAutoLinkWithoutProtocol
)

var start = position.start
var end = position.end

/* Protocol expression. See:
 * http://en.wikipedia.org/wiki/URI_scheme#Generic_syntax */
var protocol = /^[a-z][a-z+.-]+:\/?/i

var reason = 'All automatic links must start with a protocol'

function noAutoLinkWithoutProtocol(tree, file) {
  visit(tree, 'link', visitor)

  function visitor(node) {
    var children

    if (!generated(node)) {
      children = node.children

      if (
        start(node).column === start(children[0]).column - 1 &&
        end(node).column === end(children[children.length - 1]).column + 1 &&
        !protocol.test(toString(node))
      ) {
        file.message(reason, node)
      }
    }
  }
}

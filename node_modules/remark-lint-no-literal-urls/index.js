/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module no-literal-urls
 * @fileoverview
 *   Warn when URLs without angle-brackets are used.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   never creates literal URLs and always uses angle-brackets.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md"}
 *
 *   <http://foo.bar/baz>
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   http://foo.bar/baz
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   1:1-1:19: Don’t use literal URLs without angle brackets
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')
var toString = require('mdast-util-to-string')

module.exports = rule('remark-lint:no-literal-urls', noLiteralURLs)

var start = position.start
var end = position.end
var mailto = 'mailto:'
var reason = 'Don’t use literal URLs without angle brackets'

function noLiteralURLs(tree, file) {
  visit(tree, 'link', visitor)

  function visitor(node) {
    var children = node.children
    var value = toString(node)

    if (
      !generated(node) &&
      start(node).column === start(children[0]).column &&
      end(node).column === end(children[children.length - 1]).column &&
      (node.url === mailto + value || node.url === value)
    ) {
      file.message(reason, node)
    }
  }
}

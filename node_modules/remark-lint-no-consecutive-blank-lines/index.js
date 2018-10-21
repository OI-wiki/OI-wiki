/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module no-consecutive-blank-lines
 * @fileoverview
 *   Warn for too many consecutive blank lines.  Knows about the extra line
 *   needed between a list and indented code, and two lists.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   always uses one blank line between blocks if possible, or two lines when
 *   needed.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md"}
 *
 *   Foo...
 *   ␊
 *   ...Bar.
 *
 * @example {"name": "valid-for-code.md"}
 *
 *   Paragraph.
 *
 *   *   List
 *   ␊
 *   ␊
 *       bravo();
 *
 * @example {"name": "empty-document.md"}
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   Foo...
 *   ␊
 *   ␊
 *   ...Bar
 *   ␊
 *   ␊
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   4:1: Remove 1 line before node
 *   4:7: Remove 2 lines after node
 */

'use strict'

var rule = require('unified-lint-rule')
var plural = require('plur')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule(
  'remark-lint:no-consecutive-blank-lines',
  noConsecutiveBlankLines
)

function noConsecutiveBlankLines(tree, file) {
  visit(tree, visitor)

  function visitor(node) {
    var children = node.children
    var head
    var tail

    if (!generated(node) && children) {
      head = children[0]

      if (head && !generated(head)) {
        /* Compare parent and first child. */
        compare(position.start(node), position.start(head), 0)

        /* Compare between each child. */
        children.forEach(visitChild)

        tail = children[children.length - 1]

        /* Compare parent and last child. */
        if (tail !== head && !generated(tail)) {
          compare(position.end(node), position.end(tail), 1)
        }
      }
    }
  }

  /* Compare the difference between `start` and `end`,
   * and warn when that difference exceeds `max`. */
  function compare(start, end, max) {
    var diff = end.line - start.line
    var lines = Math.abs(diff) - max
    var reason

    if (lines > 0) {
      reason =
        'Remove ' +
        lines +
        ' ' +
        plural('line', lines) +
        ' ' +
        (diff > 0 ? 'before' : 'after') +
        ' node'

      file.message(reason, end)
    }
  }

  function visitChild(child, index, all) {
    var prev = all[index - 1]
    var max = 2

    if (prev && !generated(prev) && !generated(child)) {
      if (
        (prev.type === 'list' && child.type === 'list') ||
        (child.type === 'code' && prev.type === 'list' && !child.lang)
      ) {
        max++
      }

      compare(position.end(prev), position.start(child), max)
    }
  }
}

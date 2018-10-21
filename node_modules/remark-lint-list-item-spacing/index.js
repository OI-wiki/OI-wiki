/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module list-item-spacing
 * @fileoverview
 *   Warn when list looseness is incorrect, such as being tight
 *   when it should be loose, and vice versa.
 *
 *   According to the [`markdown-style-guide`](http://www.cirosantilli.com/markdown-style-guide/),
 *   if one or more list-items in a list spans more than one line,
 *   the list is required to have blank lines between each item.
 *   And otherwise, there should not be blank lines between items.
 *
 *   By default, all items must be “loose” (a blank line must be between
 *   them) if one or more items are multiline (span more than one line).
 *   Otherwise, the list must be tight (no blank line must be between
 *   items).
 *
 *   If you pass `{checkBlanks: true}`, all items must be “loose” if one or
 *   more items contain blank lines.  Otherwise, the list must be tight.
 *
 * @example {"name": "valid.md"}
 *
 *   A tight list:
 *
 *   -   item 1
 *   -   item 2
 *   -   item 3
 *
 *   A loose list:
 *
 *   -   Wrapped
 *       item
 *
 *   -   item 2
 *
 *   -   item 3
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   A tight list:
 *
 *   -   Wrapped
 *       item
 *   -   item 2
 *   -   item 3
 *
 *   A loose list:
 *
 *   -   item 1
 *
 *   -   item 2
 *
 *   -   item 3
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   4:9-5:1: Missing new line after list item
 *   5:11-6:1: Missing new line after list item
 *   11:1-12:1: Extraneous new line after list item
 *   13:1-14:1: Extraneous new line after list item
 *
 * @example {"name": "valid.md", "setting": {"checkBlanks": true}}
 *
 *   A tight list:
 *
 *   -   item 1
 *       - item 1.A
 *   -   item 2
 *       > Blockquote
 *
 *   A loose list:
 *
 *   -   item 1
 *
 *       - item 1.A
 *
 *   -   item 2
 *
 *       > Blockquote
 *
 * @example {"name": "invalid.md", "setting": {"checkBlanks": true}, "label": "input"}
 *
 *   A tight list:
 *
 *   -   item 1
 *
 *       - item 1.A
 *   -   item 2
 *
 *       > Blockquote
 *   -   item 3
 *
 *   A loose list:
 *
 *   -   item 1
 *       - item 1.A
 *
 *   -   item 2
 *       > Blockquote
 *
 * @example {"name": "invalid.md", "setting": {"checkBlanks": true}, "label": "output"}
 *
 *   5:15-6:1: Missing new line after list item
 *   8:17-9:1: Missing new line after list item
 *   15:1-16:1: Extraneous new line after list item
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:list-item-spacing', listItemSpacing)

var start = position.start
var end = position.end

var reasonLoose = 'Missing new line after list item'
var reasonTight = 'Extraneous new line after list item'

function listItemSpacing(tree, file, pref) {
  var blanks = pref && typeof pref === 'object' && Boolean(pref.checkBlanks)
  var fn = blanks ? inferBlankLine : inferMultiline

  visit(tree, 'list', visitor)

  function visitor(node) {
    var tight = true
    var indent
    var children
    var length
    var index
    var child
    var next

    if (!generated(node)) {
      children = node.children
      length = children.length
      index = -1

      while (++index < length) {
        if (fn(children[index])) {
          tight = false
          break
        }
      }

      indent = start(node).column
      child = children[0]
      index = 0

      while (++index < length) {
        next = children[index]

        if (end(child).column > indent !== tight) {
          file.message(tight ? reasonTight : reasonLoose, {
            start: end(child),
            end: start(next)
          })
        }

        child = next
      }
    }
  }
}

function inferBlankLine(node) {
  var children = node.children
  var child = children[0]
  var length = children.length
  var index = 0
  var next

  while (++index < length) {
    next = children[index]

    /* All children in `listItem`s are block. */
    if (start(next).line - end(child).line > 1) {
      return true
    }

    child = next
  }

  return false
}

function inferMultiline(node) {
  var children = node.children
  return end(children[children.length - 1]).line - start(children[0]).line > 0
}

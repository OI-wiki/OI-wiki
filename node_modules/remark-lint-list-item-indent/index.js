/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module list-item-indent
 * @fileoverview
 *   Warn when the spacing between a list item’s bullet and its content
 *   violates a given style.
 *
 *   Options: `'tab-size'`, `'mixed'`, or `'space'`, default: `'tab-size'`.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   uses `'tab-size'` (named `'tab'` there) by default to ensure markdown is
 *   seen the same way across vendors. This can be configured with the
 *   [`listItemIndent`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionslistitemindent)
 *   option. This rule’s `'space'` option is named `'1'` there.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md"}
 *
 *   *···List
 *   ····item.
 *
 *   Paragraph.
 *
 *   11.·List
 *   ····item.
 *
 *   Paragraph.
 *
 *   *···List
 *   ····item.
 *
 *   *···List
 *   ····item.
 *
 * @example {"name": "valid.md", "setting": "mixed"}
 *
 *   *·List item.
 *
 *   Paragraph.
 *
 *   11.·List item
 *
 *   Paragraph.
 *
 *   *···List
 *   ····item.
 *
 *   *···List
 *   ····item.
 *
 * @example {"name": "valid.md", "setting": "space"}
 *
 *   *·List item.
 *
 *   Paragraph.
 *
 *   11.·List item
 *
 *   Paragraph.
 *
 *   *·List
 *   ··item.
 *
 *   *·List
 *   ··item.
 *
 * @example {"name": "invalid.md", "setting": "space", "label": "input"}
 *
 *   *···List
 *   ····item.
 *
 * @example {"name": "invalid.md", "setting": "space", "label": "output"}
 *
 *    1:5: Incorrect list-item indent: remove 2 spaces
 *
 * @example {"name": "invalid.md", "setting": "tab-size", "label": "input"}
 *
 *   *·List
 *   ··item.
 *
 * @example {"name": "invalid.md", "setting": "tab-size", "label": "output"}
 *
 *    1:3: Incorrect list-item indent: add 2 spaces
 *
 * @example {"name": "invalid.md", "setting": "mixed", "label": "input"}
 *
 *   *···List item.
 *
 * @example {"name": "invalid.md", "setting": "mixed", "label": "output"}
 *
 *    1:5: Incorrect list-item indent: remove 2 spaces
 *
 * @example {"name": "invalid.md", "setting": "invalid", "label": "output", "config": {"positionless": true}}
 *
 *    1:1: Invalid list-item indent style `invalid`: use either `'tab-size'`, `'space'`, or `'mixed'`
 */

'use strict'

var rule = require('unified-lint-rule')
var plural = require('plur')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:list-item-indent', listItemIndent)

var start = position.start

var styles = {'tab-size': true, mixed: true, space: true}

function listItemIndent(tree, file, pref) {
  var contents = String(file)

  pref = typeof pref === 'string' ? pref : 'tab-size'

  if (styles[pref] !== true) {
    file.fail(
      'Invalid list-item indent style `' +
        pref +
        "`: use either `'tab-size'`, `'space'`, or `'mixed'`"
    )
  }

  visit(tree, 'list', visitor)

  function visitor(node) {
    var loose = node.loose

    if (!generated(node)) {
      node.children.forEach(visitItem)
    }

    function visitItem(item) {
      var head = item.children[0]
      var final = start(head)
      var marker
      var bulletSize
      var style
      var diff
      var reason

      marker = contents
        .slice(start(item).offset, final.offset)
        .replace(/\[[x ]?]\s*$/i, '')

      bulletSize = marker.trimRight().length

      style =
        pref === 'tab-size' || (pref === 'mixed' && loose)
          ? Math.ceil(bulletSize / 4) * 4
          : bulletSize + 1

      if (marker.length !== style) {
        diff = style - marker.length

        reason =
          'Incorrect list-item indent: ' +
          (diff > 0 ? 'add' : 'remove') +
          ' ' +
          Math.abs(diff) +
          ' ' +
          plural('space', diff)

        file.message(reason, final)
      }
    }
  }
}

/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module emphasis-marker
 * @fileoverview
 *   Warn for violating emphasis markers.
 *
 *   Options: `'consistent'`, `'*'`, or `'_'`, default: `'consistent'`.
 *
 *   `'consistent'` detects the first used emphasis style and warns when
 *   subsequent emphasis use different styles.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   formats emphasis using an underscore (`_`) by default. Pass
 *   [`emphasis: '*'`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsemphasis)
 *   to use asterisks instead.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"setting": "*", "name": "valid.md"}
 *
 *   *foo*
 *
 * @example {"setting": "*", "name": "invalid.md", "label": "input"}
 *
 *   _foo_
 *
 * @example {"setting": "*", "name": "invalid.md", "label": "output"}
 *
 *   1:1-1:6: Emphasis should use `*` as a marker
 *
 * @example {"setting": "_", "name": "valid.md"}
 *
 *   _foo_
 *
 * @example {"setting": "_", "name": "invalid.md", "label": "input"}
 *
 *   *foo*
 *
 * @example {"setting": "_", "name": "invalid.md", "label": "output"}
 *
 *   1:1-1:6: Emphasis should use `_` as a marker
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   *foo*
 *   _bar_
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   2:1-2:6: Emphasis should use `*` as a marker
 *
 * @example {"setting": "invalid", "name": "invalid.md", "label": "output", "config": {"positionless": true}}
 *
 *   1:1: Invalid emphasis marker `invalid`: use either `'consistent'`, `'*'`, or `'_'`
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:emphasis-marker', emphasisMarker)

var markers = {null: true, '*': true, _: true}

function emphasisMarker(tree, file, pref) {
  var contents = String(file)

  pref = typeof pref === 'string' && pref !== 'consistent' ? pref : null

  if (markers[pref] !== true) {
    file.fail(
      'Invalid emphasis marker `' +
        pref +
        "`: use either `'consistent'`, `'*'`, or `'_'`"
    )
  }

  visit(tree, 'emphasis', visitor)

  function visitor(node) {
    var marker

    if (!generated(node)) {
      marker = contents.charAt(position.start(node).offset)

      if (pref) {
        if (marker !== pref) {
          file.message('Emphasis should use `' + pref + '` as a marker', node)
        }
      } else {
        pref = marker
      }
    }
  }
}

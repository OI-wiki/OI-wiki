/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module strong-marker
 * @fileoverview
 *   Warn for violating strong markers.
 *
 *   Options: `'consistent'`, `'*'`, or `'_'`, default: `'consistent'`.
 *
 *   `'consistent'` detects the first used strong style and warns when subsequent
 *   strongs use different styles.
 *
 *   Note: strong is also called “importance”.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   formats importance using an asterisk (`*`) by default. Pass
 *   [`strong: '_'`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsstrong)
 *   to use underscores instead.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md"}
 *
 *   **foo** and **bar**.
 *
 * @example {"name": "also-valid.md"}
 *
 *   __foo__ and __bar__.
 *
 * @example {"name": "valid.md", "setting": "*"}
 *
 *   **foo**.
 *
 * @example {"name": "valid.md", "setting": "_"}
 *
 *   __foo__.
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   **foo** and __bar__.
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   1:13-1:20: Strong should use `*` as a marker
 *
 * @example {"name": "invalid.md", "label": "output", "setting": "!", "config": {"positionless": true}}
 *
 *   1:1: Invalid strong marker `!`: use either `'consistent'`, `'*'`, or `'_'`
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:strong-marker', strongMarker)

var markers = {'*': true, _: true, null: true}

function strongMarker(tree, file, pref) {
  var contents = String(file)

  pref = typeof pref === 'string' && pref !== 'consistent' ? pref : null

  if (markers[pref] !== true) {
    file.fail(
      'Invalid strong marker `' +
        pref +
        "`: use either `'consistent'`, `'*'`, or `'_'`"
    )
  }

  visit(tree, 'strong', visitor)

  function visitor(node) {
    var marker = contents.charAt(position.start(node).offset)

    if (!generated(node)) {
      if (pref) {
        if (marker !== pref) {
          file.message('Strong should use `' + pref + '` as a marker', node)
        }
      } else {
        pref = marker
      }
    }
  }
}

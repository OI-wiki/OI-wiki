/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module rule-style
 * @fileoverview
 *   Warn when the horizontal rules violate a given or detected style.
 *
 *   Options: `string`, either a valid markdown rule, or `'consistent'`,
 *   default: `'consistent'`.
 *
 *   `'consistent'` detects the first used rule style and warns when subsequent
 *   rules use different styles.
 *
 *   Note: horizontal rules are also called “thematic break”.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   has three settings that define how rules are created:
 *
 *   *   [`rule`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsrule)
 *       (default: `*`) — Marker to use
 *   *   [`ruleRepetition`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsrulerepetition)
 *       (default: `3`) — Number of markers to use
 *   *   [`ruleSpaces`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsrulespaces)
 *       (default: `true`) — Whether to pad markers with spaces
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md", "setting": "* * *"}
 *
 *   * * *
 *
 *   * * *
 *
 * @example {"name": "valid.md", "setting": "_______"}
 *
 *   _______
 *
 *   _______
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   ***
 *
 *   * * *
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   3:1-3:6: Rules should use `***`
 *
 * @example {"name": "invalid.md", "label": "output", "setting": "!!!", "config": {"positionless": true}}
 *
 *   1:1: Invalid preferred rule-style: provide a valid markdown rule, or `'consistent'`
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:rule-style', ruleStyle)

var start = position.start
var end = position.end

function ruleStyle(tree, file, pref) {
  var contents = String(file)

  pref = typeof pref === 'string' && pref !== 'consistent' ? pref : null

  if (pref !== null && /[^-_* ]/.test(pref)) {
    file.fail(
      "Invalid preferred rule-style: provide a valid markdown rule, or `'consistent'`"
    )
  }

  visit(tree, 'thematicBreak', visitor)

  function visitor(node) {
    var initial = start(node).offset
    var final = end(node).offset
    var rule

    if (!generated(node)) {
      rule = contents.slice(initial, final)

      if (pref) {
        if (rule !== pref) {
          file.message('Rules should use `' + pref + '`', node)
        }
      } else {
        pref = rule
      }
    }
  }
}

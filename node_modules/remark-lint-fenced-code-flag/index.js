/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module fenced-code-flag
 * @fileoverview
 *   Check fenced code-block flags.
 *
 *   Options: `Array.<string>` or `Object`, optional.
 *
 *   Providing an array is as passing `{flags: Array}`.
 *
 *   The object can have an array of `'flags'` which are deemed valid.
 *   In addition it can have the property `allowEmpty` (`boolean`, default:
 *   `false`) which signifies whether or not to warn for fenced code-blocks
 *   without language flags.
 *
 * @example {"name": "valid.md"}
 *
 *   ```alpha
 *   bravo();
 *   ```
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   ```
 *   alpha();
 *   ```
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   1:1-3:4: Missing code-language flag
 *
 * @example {"name": "valid.md", "setting": {"allowEmpty": true}}
 *
 *   ```
 *   alpha();
 *   ```
 *
 * @example {"name": "invalid.md", "setting": {"allowEmpty": false}, "label": "input"}
 *
 *   ```
 *   alpha();
 *   ```
 *
 * @example {"name": "invalid.md", "setting": {"allowEmpty": false}, "label": "output"}
 *
 *   1:1-3:4: Missing code-language flag
 *
 * @example {"name": "valid.md", "setting": ["alpha"]}
 *
 *   ```alpha
 *   bravo();
 *   ```
 *
 * @example {"name": "invalid.md", "setting": ["charlie"], "label": "input"}
 *
 *   ```alpha
 *   bravo();
 *   ```
 *
 * @example {"name": "invalid.md", "setting": ["charlie"], "label": "output"}
 *
 *   1:1-3:4: Invalid code-language flag
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:fenced-code-flag', fencedCodeFlag)

var start = position.start
var end = position.end

var fence = /^ {0,3}([~`])\1{2,}/
var reasonInvalid = 'Invalid code-language flag'
var reasonMissing = 'Missing code-language flag'

function fencedCodeFlag(tree, file, pref) {
  var contents = String(file)
  var allowEmpty = false
  var flags = []

  if (typeof pref === 'object' && !('length' in pref)) {
    allowEmpty = Boolean(pref.allowEmpty)
    pref = pref.flags
  }

  if (typeof pref === 'object' && 'length' in pref) {
    flags = String(pref).split(',')
  }

  visit(tree, 'code', visitor)

  function visitor(node) {
    var value

    if (!generated(node)) {
      if (node.lang) {
        if (flags.length !== 0 && flags.indexOf(node.lang) === -1) {
          file.message(reasonInvalid, node)
        }
      } else {
        value = contents.slice(start(node).offset, end(node).offset)

        if (!allowEmpty && fence.test(value)) {
          file.message(reasonMissing, node)
        }
      }
    }
  }
}

/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module no-file-name-irregular-characters
 * @fileoverview
 *   Warn when file names contain irregular characters: characters other than
 *   alpha-numericals, dashes, and dots (full-stops).
 *
 *   Options: `RegExp` or `string`, default: `'\\.a-zA-Z0-9-'`.
 *
 *   If a string is given, it will be wrapped in
 *   `new RegExp('[^' + preferred + ']')`.
 *
 *   Any match by the wrapped or given expressions creates a message.
 *
 * @example {"name": "plug-ins.md"}
 *
 * @example {"name": "plugins.md"}
 *
 * @example {"name": "plug_ins.md", "label": "output", "config": {"positionless": true}}
 *
 *   1:1: Do not use `_` in a file name
 *
 * @example {"name": "README.md", "label": "output", "setting": "\\.a-z0-9", "config": {"positionless": true}}
 *
 *   1:1: Do not use `R` in a file name
 *
 * @example {"name": "plug ins.md", "label": "output", "config": {"positionless": true}}
 *
 *   1:1: Do not use ` ` in a file name
 */

'use strict'

var rule = require('unified-lint-rule')

module.exports = rule(
  'remark-lint:no-file-name-irregular-characters',
  noFileNameIrregularCharacters
)

var expression = /[^\\.a-zA-Z0-9-]/

function noFileNameIrregularCharacters(tree, file, pref) {
  var style = pref || expression
  var match

  if (typeof style === 'string') {
    style = new RegExp('[^' + style + ']')
  }

  match = file.stem && file.stem.match(style)

  if (match) {
    file.message('Do not use `' + match[0] + '` in a file name')
  }
}

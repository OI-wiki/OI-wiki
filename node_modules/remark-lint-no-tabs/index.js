/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module no-tabs
 * @fileoverview
 *   Warn when hard tabs are used instead of spaces.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   uses spaces where tabs are used for indentation, but retains tabs used in
 *   content.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md"}
 *
 *   Foo Bar
 *
 *   ····Foo
 *
 * @example {"name": "invalid.md", "label": "input", "config": {"positionless": true}}
 *
 *   »Here's one before a code block.
 *
 *   Here's a tab:», and here is another:».
 *
 *   And this is in `inline»code`.
 *
 *   >»This is in a block quote.
 *
 *   *»And...
 *
 *   »1.»in a list.
 *
 *   And this is a tab as the last character.»
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   1:1: Use spaces instead of hard-tabs
 *   3:14: Use spaces instead of hard-tabs
 *   3:37: Use spaces instead of hard-tabs
 *   5:23: Use spaces instead of hard-tabs
 *   7:2: Use spaces instead of hard-tabs
 *   9:2: Use spaces instead of hard-tabs
 *   11:1: Use spaces instead of hard-tabs
 *   11:4: Use spaces instead of hard-tabs
 *   13:41: Use spaces instead of hard-tabs
 */

'use strict'

var rule = require('unified-lint-rule')
var location = require('vfile-location')

module.exports = rule('remark-lint:no-tabs', noTabs)

var reason = 'Use spaces instead of hard-tabs'

function noTabs(tree, file) {
  var content = String(file)
  var position = location(file).toPosition
  var index = content.indexOf('\t')

  while (index !== -1) {
    file.message(reason, position(index))
    index = content.indexOf('\t', index + 1)
  }
}

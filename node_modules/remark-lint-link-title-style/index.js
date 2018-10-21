/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module link-title-style
 * @fileoverview
 *   Warn when link and definition titles occur with incorrect quotes.
 *
 *   Options: `'consistent'`, `'"'`, `'\''`, or `'()'`, default: `'consistent'`.
 *
 *   `'consistent'` detects the first used quote style and warns when subsequent
 *   titles use different styles.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   uses single quotes for titles if they contain a double quote, and double
 *   quotes otherwise.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md", "setting": "\""}
 *
 *   [Example](http://example.com#without-title)
 *   [Example](http://example.com "Example Domain")
 *   ![Example](http://example.com "Example Domain")
 *
 *   [Example]: http://example.com "Example Domain"
 *
 *   You can use parens in URLs if they’re not a title (see GH-166):
 *
 *   [Example](#Heading-(optional))
 *
 * @example {"name": "invalid.md", "label": "input", "setting": "\""}
 *
 *   [Example]: http://example.com 'Example Domain'
 *
 * @example {"name": "invalid.md", "label": "output", "setting": "\""}
 *
 *   1:31-1:47: Titles should use `"` as a quote
 *
 * @example {"name": "valid.md", "setting": "'"}
 *
 *   [Example](http://example.com#without-title)
 *   [Example](http://example.com 'Example Domain')
 *   ![Example](http://example.com 'Example Domain')
 *
 *   [Example]: http://example.com 'Example Domain'
 *
 * @example {"name": "invalid.md", "label": "input", "setting": "'"}
 *
 *   [Example]: http://example.com "Example Domain"
 *
 * @example {"name": "invalid.md", "label": "output", "setting": "'"}
 *
 *   1:31-1:47: Titles should use `'` as a quote
 *
 * @example {"name": "valid.md", "setting": "()"}
 *
 *   [Example](http://example.com#without-title)
 *   [Example](http://example.com (Example Domain))
 *   ![Example](http://example.com (Example Domain))
 *
 *   [Example]: http://example.com (Example Domain)
 *
 * @example {"name": "invalid.md", "label": "input", "setting": "()"}
 *
 *   [Example](http://example.com 'Example Domain')
 *
 * @example {"name": "invalid.md", "label": "output", "setting": "()"}
 *
 *   1:30-1:46: Titles should use `()` as a quote
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   [Example](http://example.com "Example Domain")
 *   [Example](http://example.com 'Example Domain')
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   2:30-2:46: Titles should use `"` as a quote
 *
 * @example {"name": "invalid.md", "setting": ".", "label": "output", "config": {"positionless": true}}
 *
 *   1:1: Invalid link title style marker `.`: use either `'consistent'`, `'"'`, `'\''`, or `'()'`
 */

'use strict'

var rule = require('unified-lint-rule')
var vfileLocation = require('vfile-location')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:link-title-style', linkTitleStyle)

var own = {}.hasOwnProperty

var start = position.start
var end = position.end

var markers = {
  '"': '"',
  "'": "'",
  ')': '('
}

function linkTitleStyle(tree, file, pref) {
  var contents = String(file)
  var location = vfileLocation(file)

  pref = typeof pref === 'string' && pref !== 'consistent' ? pref : null
  pref = pref === '()' || pref === '(' ? ')' : pref

  if (pref && !own.call(markers, pref)) {
    file.fail(
      'Invalid link title style marker `' +
        pref +
        "`: use either `'consistent'`, `'\"'`, `'\\''`, or `'()'`"
    )
  }

  visit(tree, ['link', 'image', 'definition'], validate)

  function validate(node) {
    var tail
    var begin
    var last
    var first
    var final
    var initial
    var reason

    if (generated(node)) {
      return
    }

    last = end(node).offset - 1
    tail = node.children ? node.children[node.children.length - 1] : null
    begin = tail ? end(tail) : start(node)

    if (node.type !== 'definition') {
      last--
    }

    /* Skip back to before whitespace */
    while (last) {
      final = contents.charAt(last)

      /* istanbul ignore if - remark before 8.0.0 */
      if (/\s/.test(final)) {
        last--
      } else {
        break
      }
    }

    /* Exit if the final marker is not a known marker. */
    if (!(final in markers)) {
      return
    }

    initial = markers[final]

    /* Find the starting delimiter */
    first = contents.lastIndexOf(initial, last - 1)

    /* Exit if there’s no starting delimiter, the starting delimiter
     * is before the start of the node, or if it’s not preceded by whitespace. */
    if (first <= begin || !/\s/.test(contents.charAt(first - 1))) {
      return
    }

    if (pref) {
      if (pref !== final) {
        reason =
          'Titles should use `' + (pref === ')' ? '()' : pref) + '` as a quote'

        file.message(reason, {
          start: location.toPosition(first),
          end: location.toPosition(last + 1)
        })
      }
    } else {
      pref = final
    }
  }
}

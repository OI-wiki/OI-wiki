/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module fenced-code-marker
 * @fileoverview
 *   Warn for violating fenced code markers.
 *
 *   Options: `` '`' ``, `'~'`, or `'consistent'`, default: `'consistent'`.
 *
 *   `'consistent'` detects the first used fenced code marker style and warns
 *   when subsequent fenced code-blocks use different styles.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   formats fences using a backtick (`` '`' ``) by default. Pass
 *   [`fence: '~'`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsfence)
 *   to use tildes instead.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md"}
 *
 *   Indented code blocks are not affected by this rule:
 *
 *       bravo();
 *
 * @example {"name": "valid.md", "setting": "`"}
 *
 *   ```alpha
 *   bravo();
 *   ```
 *
 *   ```
 *   charlie();
 *   ```
 *
 * @example {"name": "valid.md", "setting": "~"}
 *
 *   ~~~alpha
 *   bravo();
 *   ~~~
 *
 *   ~~~
 *   charlie();
 *   ~~~
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   ```alpha
 *   bravo();
 *   ```
 *
 *   ~~~
 *   charlie();
 *   ~~~
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   5:1-7:4: Fenced code should use ` as a marker
 *
 * @example {"name": "invalid.md", "setting": "!", "label": "output", "config": {"positionless": true}}
 *
 *   1:1: Invalid fenced code marker `!`: use either `'consistent'`, `` '`' ``, or `'~'`
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:fenced-code-marker', fencedCodeMarker)

var markers = {
  '`': true,
  '~': true,
  null: true
}

function fencedCodeMarker(tree, file, pref) {
  var contents = String(file)

  pref = typeof pref === 'string' && pref !== 'consistent' ? pref : null

  if (markers[pref] !== true) {
    file.fail(
      'Invalid fenced code marker `' +
        pref +
        "`: use either `'consistent'`, `` '`' ``, or `'~'`"
    )
  }

  visit(tree, 'code', visitor)

  function visitor(node) {
    var marker

    if (!generated(node)) {
      marker = contents
        .substr(position.start(node).offset, 4)
        .trimLeft()
        .charAt(0)

      /* Ignore unfenced code blocks. */
      if (markers[marker] === true) {
        if (pref) {
          if (marker !== pref) {
            file.message(
              'Fenced code should use ' + pref + ' as a marker',
              node
            )
          }
        } else {
          pref = marker
        }
      }
    }
  }
}

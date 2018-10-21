/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module heading-style
 * @fileoverview
 *   Warn when a heading does not conform to a given style.
 *
 *   Options: `'consistent'`, `'atx'`, `'atx-closed'`, or `'setext'`,
 *   default: `'consistent'`.
 *
 *   `'consistent'` detects the first used heading style and warns when
 *   subsequent headings use different styles.
 *
 *   ## Fix
 *
 *   [`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
 *   formats headings as ATX by default. This can be configured with the
 *   [`setext`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionssetext)
 *   and [`closeAtx`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionscloseatx)
 *   options.
 *
 *   See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
 *   on how to automatically fix warnings for this rule.
 *
 * @example {"name": "valid.md", "setting": "atx"}
 *
 *   # Alpha
 *
 *   ## Bravo
 *
 *   ### Charlie
 *
 * @example {"name": "valid.md", "setting": "atx-closed"}
 *
 *   # Delta ##
 *
 *   ## Echo ##
 *
 *   ### Foxtrot ###
 *
 * @example {"name": "valid.md", "setting": "setext"}
 *
 *   Golf
 *   ====
 *
 *   Hotel
 *   -----
 *
 *   ### India
 *
 * @example {"name": "invalid.md", "label": "input"}
 *
 *   Juliett
 *   =======
 *
 *   ## Kilo
 *
 *   ### Lima ###
 *
 * @example {"name": "invalid.md", "label": "output"}
 *
 *   4:1-4:8: Headings should use setext
 *   6:1-6:13: Headings should use setext
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var style = require('mdast-util-heading-style')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:heading-style', headingStyle)

var types = ['atx', 'atx-closed', 'setext']

function headingStyle(tree, file, pref) {
  pref = types.indexOf(pref) === -1 ? null : pref

  visit(tree, 'heading', visitor)

  function visitor(node) {
    if (!generated(node)) {
      if (pref) {
        if (style(node, pref) !== pref) {
          file.message('Headings should use ' + pref, node)
        }
      } else {
        pref = style(node, pref)
      }
    }
  }
}

/**
 * @author Titus Wormer
 * @copyright 2015 Titus Wormer
 * @license MIT
 * @module maximum-line-length
 * @fileoverview
 *   Warn when lines are too long.
 *
 *   Options: `number`, default: `80`.
 *
 *   Ignores nodes that cannot be wrapped, such as headings, tables,
 *   code, and definitions.
 *
 *   Ignores images, links, and inline code if they start before the wrap, end
 *   after the wrap, and there’s no white-space after them.
 *
 * @example {"name": "valid.md", "config": {"positionless": true}}
 *
 *   This line is simply not toooooooooooooooooooooooooooooooooooooooooooo
 *   long.
 *
 *   This is also fine: <http://this-long-url-with-a-long-domain.co.uk/a-long-path?query=variables>
 *
 *   <http://this-link-is-fine.com>
 *
 *   `alphaBravoCharlieDeltaEchoFoxtrotGolfHotelIndiaJuliettKiloLimaMikeNovemberOscarPapaQuebec.romeo()`
 *
 *   [foo](http://this-long-url-with-a-long-domain-is-valid.co.uk/a-long-path?query=variables)
 *
 *   <http://this-long-url-with-a-long-domain-is-valid.co.uk/a-long-path?query=variables>
 *
 *   ![foo](http://this-long-url-with-a-long-domain-is-valid.co.uk/a-long-path?query=variables)
 *
 *   | An | exception | is | line | length | in | long | tables | because | those | can’t | just |
 *   | -- | --------- | -- | ---- | ------ | -- | ---- | ------ | ------- | ----- | ----- | ---- |
 *   | be | helped    |    |      |        |    |      |        |         |       |       | .    |
 *
 *   The following is also fine, because there is no white-space.
 *
 *   <http://this-long-url-with-a-long-domain-is-invalid.co.uk/a-long-path?query=variables>.
 *
 *   In addition, definitions are also fine:
 *
 *   [foo]: <http://this-long-url-with-a-long-domain-is-invalid.co.uk/a-long-path?query=variables>
 *
 * @example {"name": "invalid.md", "setting": 80, "label": "input", "config": {"positionless": true}}
 *
 *   This line is simply not tooooooooooooooooooooooooooooooooooooooooooooooooooooooo
 *   long.
 *
 *   Just like thiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiis one.
 *
 *   And this one is also very wrong: because the link starts aaaaaaafter the column: <http://line.com>
 *
 *   <http://this-long-url-with-a-long-domain-is-invalid.co.uk/a-long-path?query=variables> and such.
 *
 *   And this one is also very wrong: because the code starts aaaaaaafter the column: `alpha.bravo()`
 *
 *   `alphaBravoCharlieDeltaEchoFoxtrotGolfHotelIndiaJuliettKiloLimaMikeNovemberOscar.papa()` and such.
 *
 * @example {"name": "invalid.md", "setting": 80, "label": "output", "config": {"positionless": true}}
 *
 *   4:86: Line must be at most 80 characters
 *   6:99: Line must be at most 80 characters
 *   8:97: Line must be at most 80 characters
 *   10:97: Line must be at most 80 characters
 *   12:99: Line must be at most 80 characters
 *
 * @example {"name": "valid-mixed-line-endings.md", "setting": 10, "config": {"positionless": true}}
 *
 *   0123456789␍␊
 *   0123456789␊
 *   01234␍␊
 *   01234␊
 *
 * @example {"name": "invalid-mixed-line-endings.md", "setting": 10, "label": "input", "config": {"positionless": true}}
 *
 *   012345678901␍␊
 *   012345678901␊
 *   01234567890␍␊
 *   01234567890␊
 *
 * @example {"name": "invalid-mixed-line-endings.md", "setting": 10, "label": "output", "config": {"positionless": true}}
 *
 *   1:13: Line must be at most 10 characters
 *   2:13: Line must be at most 10 characters
 *   3:12: Line must be at most 10 characters
 *   4:12: Line must be at most 10 characters
 */

'use strict'

var rule = require('unified-lint-rule')
var visit = require('unist-util-visit')
var position = require('unist-util-position')
var generated = require('unist-util-generated')

module.exports = rule('remark-lint:maximum-line-length', maximumLineLength)

var start = position.start
var end = position.end

function maximumLineLength(tree, file, pref) {
  var style = typeof pref === 'number' && !isNaN(pref) ? pref : 80
  var content = String(file)
  var lines = content.split(/\r?\n/)
  var length = lines.length
  var index = -1
  var lineLength

  visit(tree, ['heading', 'table', 'code', 'definition'], ignore)
  visit(tree, ['link', 'image', 'inlineCode'], inline)

  /* Iterate over every line, and warn for violating lines. */
  while (++index < length) {
    lineLength = lines[index].length

    if (lineLength > style) {
      file.message('Line must be at most ' + style + ' characters', {
        line: index + 1,
        column: lineLength + 1
      })
    }
  }

  /* Finally, whitelist some inline spans, but only if they occur at or after
   * the wrap.  However, when they do, and there’s white-space after it, they
   * are not whitelisted. */
  function inline(node, pos, parent) {
    var next = parent.children[pos + 1]
    var initial
    var final

    /* istanbul ignore if - Nothing to whitelist when generated. */
    if (generated(node)) {
      return
    }

    initial = start(node)
    final = end(node)

    /* No whitelisting when starting after the border, or ending before it. */
    if (initial.column > style || final.column < style) {
      return
    }

    /* No whitelisting when there’s white-space after
     * the link. */
    if (
      next &&
      start(next).line === initial.line &&
      (!next.value || /^(.+?[ \t].+?)/.test(next.value))
    ) {
      return
    }

    whitelist(initial.line - 1, final.line)
  }

  function ignore(node) {
    /* istanbul ignore else - Hard to test, as we only run this case on `position: true` */
    if (!generated(node)) {
      whitelist(start(node).line - 1, end(node).line)
    }
  }

  /* Whitelist from `initial` to `final`, zero-based. */
  function whitelist(initial, final) {
    while (initial < final) {
      lines[initial++] = ''
    }
  }
}

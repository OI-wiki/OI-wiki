function locator (value, fromIndex) {
  return value.indexOf('$', fromIndex)
}

const ESCAPED_INLINE_MATH = /^\\\$/
const INLINE_MATH = /^\$((?:\\\$|[^$])+)\$/
const INLINE_MATH_DOUBLE = /^\$\$((?:\\\$|[^$])+)\$\$/

module.exports = function inlinePlugin (opts) {
  function inlineTokenizer (eat, value, silent) {
    let isDouble = true
    let match = INLINE_MATH_DOUBLE.exec(value)
    if (!match) {
      match = INLINE_MATH.exec(value)
      isDouble = false
    }
    const escaped = ESCAPED_INLINE_MATH.exec(value)

    if (escaped) {
      /* istanbul ignore if - never used (yet) */
      if (silent) {
        return true
      }
      return eat(escaped[0])({
        type: 'text',
        value: '$'
      })
    }

    if (value.slice(-2) === '\\$') {
      return eat(value)({
        type: 'text',
        value: value.slice(0, -2) + '$'
      })
    }

    if (match) {
      /* istanbul ignore if - never used (yet) */
      if (silent) {
        return true
      }

      const endingDollarInBackticks = match[0].includes('`') && value.slice(match[0].length).includes('`')
      if (endingDollarInBackticks) {
        const toEat = value.slice(0, value.indexOf('`'))
        return eat(toEat)({
          type: 'text',
          value: toEat
        })
      }

      const trimmedContent = match[1].trim()

      return eat(match[0])({
        type: 'inlineMath',
        value: trimmedContent,
        data: {
          hName: 'span',
          hProperties: {
            className: 'inlineMath' + (isDouble && opts.inlineMathDouble ? ' inlineMathDouble' : '')
          },
          hChildren: [
            {
              type: 'text',
              value: trimmedContent
            }
          ]
        }
      })
    }
  }
  inlineTokenizer.locator = locator

  const Parser = this.Parser

  // Inject inlineTokenizer
  const inlineTokenizers = Parser.prototype.inlineTokenizers
  const inlineMethods = Parser.prototype.inlineMethods
  inlineTokenizers.math = inlineTokenizer
  inlineMethods.splice(inlineMethods.indexOf('text'), 0, 'math')

  const Compiler = this.Compiler

  // Stringify for math inline
  if (Compiler != null) {
    const visitors = Compiler.prototype.visitors
    visitors.inlineMath = function (node) {
      return '$' + node.value + '$'
    }
  }
}

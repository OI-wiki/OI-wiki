const inlinePlugin = require('./inline')
const blockPlugin = require('./block')

module.exports = function mathPlugin (opts = {}) {
  blockPlugin.call(this, opts)
  inlinePlugin.call(this, opts)
}

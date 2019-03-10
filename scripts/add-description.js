const fs = require('fs-extra')
const path = require('path')
const marked = require('marked')
const striptags = require('striptags')
const packageJson = require('../package')

const root = path.resolve(__dirname, '../')

const generateDescription = (str) => {
  return `---\ndescription: ${striptags(marked(str).toString()).split('\n').toString().substring(0, 200).trim()}\n---\n`
}

function addDescription (doc = path.resolve(root, packageJson.directories.doc)) {
  fs.readdirSync(doc).forEach(file => {
    const pth = path.resolve(doc, file)
    const stat = fs.statSync(pth)
    if (stat.isDirectory()) {
      // if file is dir
      addDescription(pth)
    } else if (stat.isFile() && /.md$/.test(file)) {
      // // if file is file
      let data = fs.readFileSync(pth, { encoding: 'utf-8' })
        .toString()
      const description = generateDescription(data)
      data = description + data
      fs.writeFileSync(pth, data, { encoding: 'utf-8' })
    }
  })
}

module.exports = addDescription

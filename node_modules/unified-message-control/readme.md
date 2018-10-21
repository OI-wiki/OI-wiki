# unified-message-control [![Build Status][build-badge]][build-status] [![Coverage Status][coverage-badge]][coverage-status] [![Chat][chat-badge]][chat]

Enable, disable, and ignore messages with [**unified**][unified].

## Installation

[npm][]:

```bash
npm install unified-message-control
```

## Usage

Say we have the following file, `example.md`:

```markdown
<!--foo ignore-->

## Heading
```

And our script, `example.js`, looks as follows:

```javascript
var vfile = require('to-vfile')
var report = require('vfile-reporter')
var remark = require('remark')
var control = require('unified-message-control')
var mdastMarker = require('mdast-comment-marker')

remark()
  .use(warn)
  .use(control, {name: 'foo', marker: mdastMarker, test: 'html'})
  .process(vfile.readSync('example.md'), function(err, file) {
    console.error(report(err || file))
  })

function warn() {
  return function(tree, file) {
    file.message('Whoops!', tree.children[1], 'foo:thing')
  }
}
```

Now, running `node example` yields:

```markdown
example.md: no issues found
```

## API

### `unified.use(control, options)`

Let comment markers control messages from a certain sources.

##### Options

###### `options.name`

`string` — Name of markers that can control the message sources.

For example, `{name: 'alpha'}` controls `alpha` markers:

```markdown
<!--alpha ignore-->
```

###### `options.marker`

`function` — function that returns a [comment marker object][marker]
for a matched comment, and `null` for a non-matched comment.

###### `options.test`

(`Function`, `string`, `Object`, or `Array.<Test>`)
—  When `string`, works like passing `function (node) {return
node.type === test}`.
When `array`, checks any one of the subtests pass.
When `object`, checks that all keys in `test` are in `node`,
and that they have (strictly) equal values

###### `options.known`

`Array.<string>`, optional — List of allowed `ruleId`s.  When given, a warning
is shown when someone tries to control an unknown rule.

For example, `{name: 'alpha', known: ['bravo']}` results in a warning if
`charlie` is configured:

```markdown
<!--alpha ignore charlie-->
```

###### `options.reset`

`boolean`, default: `false` — Whether to treat all messages as turned off
initially.

###### `options.enable`

`Array.<string>`, optional — List of allowed `ruleId`s used when `reset: true`
to initially turn on.  By default (`reset: false`), all rules are turned on.

###### `options.disable`

`Array.<string>`, optional — List of disallowed `ruleId`s used when
`reset: false` to initially turn off.

###### `options.sources`

`string` or `Array.<string>`, optional — One or more sources which markers by
the specified `name` can control.  Defaults to `options.name`.

### Markers

###### `disable`

The **disable** marker turns off all messages of the given rule
identifiers.  When without identifiers, all messages are turned
off.

For example, to turn off certain messages:

```md
<!--lint disable list-item-bullet-indent strong-marker-->

*   **foo**

A paragraph, and now another list.

  * __bar__
```

###### `enable`

The **enable** marker turns on all messages of the given rule
identifiers.  When without identifiers, all messages are turned
on.

For example, to enable certain messages:

```md
<!--lint enable strong-marker-->

**foo** and __bar__.
```

###### `ignore`

The **ignore** marker turns off all messages of the given rule
identifiers occurring in the following node.  When without
identifiers, all messages are turned off.

After the end of the following node, messages are allowed again.

For example, to turn off certain messages for the next node:

```md
<!--lint ignore list-item-bullet-indent strong-marker-->

*   **foo**
  * __bar__
```

## Contribute

See [`contributing.md` in `unified/unified`][contributing] for ways to get
started.

This organisation has a [Code of Conduct][coc].  By interacting with this
repository, organisation, or community you agree to abide by its terms.

## License

[MIT][license] © [Titus Wormer][author]

<!-- Definitions -->

[build-badge]: https://img.shields.io/travis/unifiedjs/unified-message-control.svg

[build-status]: https://travis-ci.org/unifiedjs/unified-message-control

[coverage-badge]: https://img.shields.io/codecov/c/github/unifiedjs/unified-message-control.svg

[coverage-status]: https://codecov.io/github/unifiedjs/unified-message-control

[chat-badge]: https://img.shields.io/gitter/room/unifiedjs/Lobby.svg

[chat]: https://gitter.im/unifiedjs/Lobby

[license]: LICENSE

[author]: http://wooorm.com

[npm]: https://docs.npmjs.com/cli/install

[marker]: https://github.com/syntax-tree/mdast-comment-marker#marker

[unified]: https://github.com/unifiedjs/unified

[contributing]: https://github.com/unifiedjs/unified/blob/master/contributing.md

[coc]: https://github.com/unifiedjs/unified/blob/master/code-of-conduct.md

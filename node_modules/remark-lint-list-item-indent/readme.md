<!--This file is generated-->

# remark-lint-list-item-indent

Warn when the spacing between a list item’s bullet and its content
violates a given style.

Options: `'tab-size'`, `'mixed'`, or `'space'`, default: `'tab-size'`.

## Fix

[`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
uses `'tab-size'` (named `'tab'` there) by default to ensure markdown is
seen the same way across vendors. This can be configured with the
[`listItemIndent`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionslistitemindent)
option. This rule’s `'space'` option is named `'1'` there.

See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
on how to automatically fix warnings for this rule.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) | `'mixed'` |
| [`remark-preset-lint-recommended`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-recommended) | `'tab-size'` |

## Example

##### `valid.md`

###### In

Note: `·` represents a space.

```markdown
*···List
····item.

Paragraph.

11.·List
····item.

Paragraph.

*···List
····item.

*···List
····item.
```

###### Out

No messages.

##### `valid.md`

When configured with `'mixed'`.

###### In

Note: `·` represents a space.

```markdown
*·List item.

Paragraph.

11.·List item

Paragraph.

*···List
····item.

*···List
····item.
```

###### Out

No messages.

##### `invalid.md`

When configured with `'mixed'`.

###### In

Note: `·` represents a space.

```markdown
*···List item.
```

###### Out

```text
1:5: Incorrect list-item indent: remove 2 spaces
```

##### `valid.md`

When configured with `'space'`.

###### In

Note: `·` represents a space.

```markdown
*·List item.

Paragraph.

11.·List item

Paragraph.

*·List
··item.

*·List
··item.
```

###### Out

No messages.

##### `invalid.md`

When configured with `'space'`.

###### In

Note: `·` represents a space.

```markdown
*···List
····item.
```

###### Out

```text
1:5: Incorrect list-item indent: remove 2 spaces
```

##### `invalid.md`

When configured with `'tab-size'`.

###### In

Note: `·` represents a space.

```markdown
*·List
··item.
```

###### Out

```text
1:3: Incorrect list-item indent: add 2 spaces
```

##### `invalid.md`

When configured with `'invalid'`.

###### Out

```text
1:1: Invalid list-item indent style `invalid`: use either `'tab-size'`, `'space'`, or `'mixed'`
```

## Install

```sh
npm install remark-lint-list-item-indent
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-list-item-indent",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-list-item-indent readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-list-item-indent'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

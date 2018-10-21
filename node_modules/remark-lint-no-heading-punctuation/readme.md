<!--This file is generated-->

# remark-lint-no-heading-punctuation

Warn when a heading ends with a a group of characters.

Options: `string`, default: `'.,;:!?'`.

Note: these are added to a regex, in a group (`'[' + char + ']'`), be careful
for escapes and dashes.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) | `':.'` |

## Example

##### `valid.md`

###### In

```markdown
# Hello
```

###### Out

No messages.

##### `invalid.md`

###### In

```markdown
# Hello:

# Hello?

# Hello!

# Hello,

# Hello;
```

###### Out

```text
1:1-1:9: Don’t add a trailing `:` to headings
3:1-3:9: Don’t add a trailing `?` to headings
5:1-5:9: Don’t add a trailing `!` to headings
7:1-7:9: Don’t add a trailing `,` to headings
9:1-9:9: Don’t add a trailing `;` to headings
```

##### `valid.md`

When configured with `',;:!?'`.

###### In

```markdown
# Hello...
```

###### Out

No messages.

## Install

```sh
npm install remark-lint-no-heading-punctuation
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-no-heading-punctuation",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-no-heading-punctuation readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-no-heading-punctuation'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

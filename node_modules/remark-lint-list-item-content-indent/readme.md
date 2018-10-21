<!--This file is generated-->

# remark-lint-list-item-content-indent

Warn when the content of a list item has mixed indentation.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-consistent`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-consistent) |  |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) |  |

## Example

##### `valid.md`

###### In

Note: `·` represents a space.

```markdown
1.·[x] Alpha
···1. Bravo
```

###### Out

No messages.

##### `invalid.md`

###### In

Note: `·` represents a space.

```markdown
1.·[x] Charlie
····1. Delta
```

###### Out

```text
2:5: Don’t use mixed indentation for children, remove 1 space
```

## Install

```sh
npm install remark-lint-list-item-content-indent
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-list-item-content-indent",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-list-item-content-indent readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-list-item-content-indent'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

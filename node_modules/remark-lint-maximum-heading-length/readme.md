<!--This file is generated-->

# remark-lint-maximum-heading-length

Warn when headings are too long.

Options: `number`, default: `60`.

Ignores markdown syntax, only checks the plain text content.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) |  |

## Example

##### `invalid.md`

When configured with `40`.

###### In

```markdown
# Alpha bravo charlie delta echo foxtrot golf hotel
```

###### Out

```text
1:1-1:52: Use headings shorter than `40`
```

##### `valid.md`

###### In

```markdown
# Alpha bravo charlie delta echo foxtrot golf hotel

# ![Alpha bravo charlie delta echo foxtrot golf hotel](http://example.com/nato.png)
```

###### Out

No messages.

## Install

```sh
npm install remark-lint-maximum-heading-length
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-maximum-heading-length",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-maximum-heading-length readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-maximum-heading-length'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

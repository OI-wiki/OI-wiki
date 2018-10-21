<!--This file is generated-->

# remark-lint-code-block-style

Warn when code-blocks do not adhere to a given style.

Options: `'consistent'`, `'fenced'`, or `'indented'`, default: `'consistent'`.

`'consistent'` detects the first used code-block style and warns when
subsequent code-blocks uses different styles.

## Fix

[`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
formats code blocks using a fence if they have a language flag and
indentation if not. Pass
[`fences: true`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsfences)
to always use fences for code blocks.

See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
on how to automatically fix warnings for this rule.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-consistent`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-consistent) | `'consistent'` |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) | `'fenced'` |

## Example

##### `valid.md`

When configured with `'indented'`.

###### In

```markdown
    alpha();

Paragraph.

    bravo();
```

###### Out

No messages.

##### `invalid.md`

When configured with `'indented'`.

###### In

````markdown
```
alpha();
```

Paragraph.

```
bravo();
```
````

###### Out

```text
1:1-3:4: Code blocks should be indented
7:1-9:4: Code blocks should be indented
```

##### `valid.md`

When configured with `'fenced'`.

###### In

````markdown
```
alpha();
```

Paragraph.

```
bravo();
```
````

###### Out

No messages.

##### `invalid.md`

When configured with `'fenced'`.

###### In

```markdown
    alpha();

Paragraph.

    bravo();
```

###### Out

```text
1:1-1:13: Code blocks should be fenced
5:1-5:13: Code blocks should be fenced
```

##### `invalid.md`

###### In

````markdown
    alpha();

Paragraph.

```
bravo();
```
````

###### Out

```text
5:1-7:4: Code blocks should be indented
```

##### `invalid.md`

When configured with `'invalid'`.

###### Out

```text
1:1: Invalid code block style `invalid`: use either `'consistent'`, `'fenced'`, or `'indented'`
```

## Install

```sh
npm install remark-lint-code-block-style
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-code-block-style",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-code-block-style readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-code-block-style'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

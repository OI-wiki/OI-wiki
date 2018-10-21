<!--This file is generated-->

# remark-lint-table-pipes

Warn when table rows are not fenced with pipes.

## Fix

[`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
creates fenced rows with initial and final pipes by default. Pass
[`looseTable: true`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsloosetable)
to not use row fences.

See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
on how to automatically fix warnings for this rule.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) |  |

## Example

##### `valid.md`

###### In

```markdown
| A     | B     |
| ----- | ----- |
| Alpha | Bravo |
```

###### Out

No messages.

##### `invalid.md`

###### In

```markdown
A     | B
----- | -----
Alpha | Bravo
```

###### Out

```text
1:1: Missing initial pipe in table fence
1:10: Missing final pipe in table fence
3:1: Missing initial pipe in table fence
3:14: Missing final pipe in table fence
```

## Install

```sh
npm install remark-lint-table-pipes
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-table-pipes",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-table-pipes readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-table-pipes'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

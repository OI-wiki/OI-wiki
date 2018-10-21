<!--This file is generated-->

# remark-lint-no-emphasis-as-heading

Warn when emphasis (including strong), instead of a heading, introduces
a paragraph.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) |  |

## Example

##### `valid.md`

###### In

```markdown
# Foo

Bar.
```

###### Out

No messages.

##### `invalid.md`

###### In

```markdown
*Foo*

Bar.

__Qux__

Quux.
```

###### Out

```text
1:1-1:6: Don’t use emphasis to introduce a section, use a heading
5:1-5:8: Don’t use emphasis to introduce a section, use a heading
```

## Install

```sh
npm install remark-lint-no-emphasis-as-heading
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-no-emphasis-as-heading",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-no-emphasis-as-heading readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-no-emphasis-as-heading'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

<!--This file is generated-->

# remark-lint-no-duplicate-headings

Warn when duplicate headings are found.

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

## Bar
```

###### Out

No messages.

##### `invalid.md`

###### In

```markdown
# Foo

## Foo

## [Foo](http://foo.com/bar)
```

###### Out

```text
3:1-3:7: Do not use headings with similar content (1:1)
5:1-5:29: Do not use headings with similar content (3:1)
```

## Install

```sh
npm install remark-lint-no-duplicate-headings
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-no-duplicate-headings",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-no-duplicate-headings readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-no-duplicate-headings'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

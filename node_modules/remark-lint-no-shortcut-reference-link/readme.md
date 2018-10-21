<!--This file is generated-->

# remark-lint-no-shortcut-reference-link

Warn when shortcut reference links are used.

Shortcut references render as links when a definition is found, and as
plain text without definition.  Sometimes, you don’t intend to create a
link from the reference, but this rule still warns anyway.  In that case,
you can escape the reference like so: `\[foo]`.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) |  |
| [`remark-preset-lint-recommended`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-recommended) |  |

## Example

##### `valid.md`

###### In

```markdown
[foo][]

[foo]: http://foo.bar/baz
```

###### Out

No messages.

##### `invalid.md`

###### In

```markdown
[foo]

[foo]: http://foo.bar/baz
```

###### Out

```text
1:1-1:6: Use the trailing [] on reference links
```

## Install

```sh
npm install remark-lint-no-shortcut-reference-link
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-no-shortcut-reference-link",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-no-shortcut-reference-link readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-no-shortcut-reference-link'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

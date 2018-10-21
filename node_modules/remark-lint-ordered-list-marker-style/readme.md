<!--This file is generated-->

# remark-lint-ordered-list-marker-style

Warn when the list-item marker style of ordered lists violate a given
style.

Options: `'consistent'`, `'.'`, or `')'`, default: `'consistent'`.

`'consistent'` detects the first used list style and warns when subsequent
lists use different styles.

Note: `)` is only supported in CommonMark.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-consistent`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-consistent) | `'consistent'` |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) | `'.'` |
| [`remark-preset-lint-recommended`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-recommended) | `'.'` |

## Example

##### `valid.md`

###### In

```markdown
1.  Foo


1.  Bar

Unordered lists are not affected by this rule.

* Foo
```

###### Out

No messages.

##### `invalid.md`

###### In

```markdown
1.  Foo

2)  Bar
```

###### Out

```text
3:1-3:8: Marker style should be `.`
```

##### `valid.md`

When configured with `'.'`.

###### In

```markdown
1.  Foo

2.  Bar
```

###### Out

No messages.

##### `valid.md`

When configured with `')'`.

###### In

```markdown
<!-- This requires commonmark. -->

1)  Foo

2)  Bar
```

###### Out

No messages.

##### `invalid.md`

When configured with `'!'`.

###### Out

```text
1:1: Invalid ordered list-item marker style `!`: use either `'.'` or `')'`
```

## Install

```sh
npm install remark-lint-ordered-list-marker-style
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-ordered-list-marker-style",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-ordered-list-marker-style readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-ordered-list-marker-style'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

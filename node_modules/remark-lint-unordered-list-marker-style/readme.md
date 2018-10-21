<!--This file is generated-->

# remark-lint-unordered-list-marker-style

Warn when the list-item marker style of unordered lists violate a given
style.

Options: `'consistent'`, `'-'`, `'*'`, or `'*'`, default: `'consistent'`.

`'consistent'` detects the first used list style and warns when subsequent
lists use different styles.

## Fix

[`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
formats unordered lists using a hyphen-minus (`-`) by default. Pass
[`bullet: '*'` or `bullet: '+'`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsbullet)
to use asterisks or plusses instead.

See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
on how to automatically fix warnings for this rule.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) | `'-'` |

## Example

##### `valid.md`

###### In

```markdown
By default (`'consistent'`), if the file uses only one marker,
that’s OK.

* Foo
* Bar
* Baz

Ordered lists are not affected.

1. Foo
2. Bar
3. Baz
```

###### Out

No messages.

##### `invalid.md`

###### In

```markdown
* Foo
- Bar
+ Baz
```

###### Out

```text
2:1-2:6: Marker style should be `*`
3:1-3:6: Marker style should be `*`
```

##### `valid.md`

When configured with `'*'`.

###### In

```markdown
* Foo
```

###### Out

No messages.

##### `valid.md`

When configured with `'-'`.

###### In

```markdown
- Foo
```

###### Out

No messages.

##### `valid.md`

When configured with `'+'`.

###### In

```markdown
+ Foo
```

###### Out

No messages.

##### `invalid.md`

When configured with `'!'`.

###### Out

```text
1:1: Invalid unordered list-item marker style `!`: use either `'-'`, `'*'`, or `'+'`
```

## Install

```sh
npm install remark-lint-unordered-list-marker-style
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-unordered-list-marker-style",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-unordered-list-marker-style readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-unordered-list-marker-style'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

<!--This file is generated-->

# remark-lint-ordered-list-marker-value

Warn when the list-item marker values of ordered lists violate a
given style.

Options: `'single'`, `'one'`, or `'ordered'`, default: `'ordered'`.

When set to `'ordered'`, list-item bullets should increment by one,
relative to the starting point.  When set to `'single'`, bullets should
be the same as the relative starting point.  When set to `'one'`, bullets
should always be `1`.

## Fix

[`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
retains the number of the first list-item bullet, and by default
increments the other items. Pass
[`incrementListMarker: false`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify#optionsincrementlistmarker)
to not increment further list-items.

See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
on how to automatically fix warnings for this rule.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) | `'one'` |

## Example

##### `valid.md`

###### In

```markdown
The default value is `ordered`, so unless changed, the below
is OK.

1.  Foo
2.  Bar
3.  Baz

Paragraph.

3.  Alpha
4.  Bravo
5.  Charlie

Unordered lists are not affected by this rule.

*   Anton
```

###### Out

No messages.

##### `valid.md`

When configured with `'one'`.

###### In

```markdown
1.  Foo
1.  Bar
1.  Baz

Paragraph.

1.  Alpha
1.  Bravo
1.  Charlie
```

###### Out

No messages.

##### `invalid.md`

When configured with `'one'`.

###### In

```markdown
1.  Foo
2.  Bar
```

###### Out

```text
2:1-2:8: Marker should be `1`, was `2`
```

##### `also-invalid.md`

When configured with `'one'`.

###### In

```markdown
2.  Foo
1.  Bar
```

###### Out

```text
1:1-1:8: Marker should be `1`, was `2`
```

##### `valid.md`

When configured with `'single'`.

###### In

```markdown
1.  Foo
1.  Bar
1.  Baz

Paragraph.

3.  Alpha
3.  Bravo
3.  Charlie
```

###### Out

No messages.

##### `valid.md`

When configured with `'ordered'`.

###### In

```markdown
1.  Foo
2.  Bar
3.  Baz

Paragraph.

3.  Alpha
4.  Bravo
5.  Charlie
```

###### Out

No messages.

##### `invalid.md`

When configured with `'ordered'`.

###### In

```markdown
1.  Foo
1.  Bar
```

###### Out

```text
2:1-2:8: Marker should be `2`, was `1`
```

##### `invalid.md`

When configured with `'invalid'`.

###### Out

```text
1:1: Invalid ordered list-item marker value `invalid`: use either `'ordered'` or `'one'`
```

## Install

```sh
npm install remark-lint-ordered-list-marker-value
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-ordered-list-marker-value",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-ordered-list-marker-value readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-ordered-list-marker-value'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

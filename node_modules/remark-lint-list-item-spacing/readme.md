<!--This file is generated-->

# remark-lint-list-item-spacing

Warn when list looseness is incorrect, such as being tight
when it should be loose, and vice versa.

According to the [`markdown-style-guide`](http://www.cirosantilli.com/markdown-style-guide/),
if one or more list-items in a list spans more than one line,
the list is required to have blank lines between each item.
And otherwise, there should not be blank lines between items.

By default, all items must be “loose” (a blank line must be between
them) if one or more items are multiline (span more than one line).
Otherwise, the list must be tight (no blank line must be between
items).

If you pass `{checkBlanks: true}`, all items must be “loose” if one or
more items contain blank lines.  Otherwise, the list must be tight.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) |  |

## Example

##### `valid.md`

###### In

```markdown
A tight list:

-   item 1
-   item 2
-   item 3

A loose list:

-   Wrapped
    item

-   item 2

-   item 3
```

###### Out

No messages.

##### `invalid.md`

###### In

```markdown
A tight list:

-   Wrapped
    item
-   item 2
-   item 3

A loose list:

-   item 1

-   item 2

-   item 3
```

###### Out

```text
4:9-5:1: Missing new line after list item
5:11-6:1: Missing new line after list item
11:1-12:1: Extraneous new line after list item
13:1-14:1: Extraneous new line after list item
```

##### `valid.md`

When configured with `{ checkBlanks: true }`.

###### In

```markdown
A tight list:

-   item 1
    - item 1.A
-   item 2
    > Blockquote

A loose list:

-   item 1

    - item 1.A

-   item 2

    > Blockquote
```

###### Out

No messages.

##### `invalid.md`

When configured with `{ checkBlanks: true }`.

###### In

```markdown
A tight list:

-   item 1

    - item 1.A
-   item 2

    > Blockquote
-   item 3

A loose list:

-   item 1
    - item 1.A

-   item 2
    > Blockquote
```

###### Out

```text
5:15-6:1: Missing new line after list item
8:17-9:1: Missing new line after list item
15:1-16:1: Extraneous new line after list item
```

## Install

```sh
npm install remark-lint-list-item-spacing
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-list-item-spacing",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-list-item-spacing readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-list-item-spacing'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

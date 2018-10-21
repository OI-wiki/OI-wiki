<!--This file is generated-->

# remark-lint-no-tabs

Warn when hard tabs are used instead of spaces.

## Fix

[`remark-stringify`](https://github.com/remarkjs/remark/tree/master/packages/remark-stringify)
uses spaces where tabs are used for indentation, but retains tabs used in
content.

See [Using remark to fix your markdown](https://github.com/remarkjs/remark-lint#using-remark-to-fix-your-markdown)
on how to automatically fix warnings for this rule.

## Presets

This rule is not included in any default preset

## Example

##### `valid.md`

###### In

Note: `·` represents a space.

```markdown
Foo Bar

····Foo
```

###### Out

No messages.

##### `invalid.md`

###### In

Note: `»` represents a tab.

```markdown
»Here's one before a code block.

Here's a tab:», and here is another:».

And this is in `inline»code`.

>»This is in a block quote.

*»And...

»1.»in a list.

And this is a tab as the last character.»
```

###### Out

```text
1:1: Use spaces instead of hard-tabs
3:14: Use spaces instead of hard-tabs
3:37: Use spaces instead of hard-tabs
5:23: Use spaces instead of hard-tabs
7:2: Use spaces instead of hard-tabs
9:2: Use spaces instead of hard-tabs
11:1: Use spaces instead of hard-tabs
11:4: Use spaces instead of hard-tabs
13:41: Use spaces instead of hard-tabs
```

## Install

```sh
npm install remark-lint-no-tabs
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-no-tabs",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-no-tabs readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-no-tabs'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

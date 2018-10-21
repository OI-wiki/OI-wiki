<!--This file is generated-->

# remark-lint-no-file-name-irregular-characters

Warn when file names contain irregular characters: characters other than
alpha-numericals, dashes, and dots (full-stops).

Options: `RegExp` or `string`, default: `'\\.a-zA-Z0-9-'`.

If a string is given, it will be wrapped in
`new RegExp('[^' + preferred + ']')`.

Any match by the wrapped or given expressions creates a message.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) |  |

## Example

##### `plug-ins.md`

###### Out

No messages.

##### `plugins.md`

###### Out

No messages.

##### `plug_ins.md`

###### Out

```text
1:1: Do not use `_` in a file name
```

##### `plug ins.md`

###### Out

```text
1:1: Do not use ` ` in a file name
```

##### `README.md`

When configured with `'\\.a-z0-9'`.

###### Out

```text
1:1: Do not use `R` in a file name
```

## Install

```sh
npm install remark-lint-no-file-name-irregular-characters
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-no-file-name-irregular-characters",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-no-file-name-irregular-characters readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-no-file-name-irregular-characters'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

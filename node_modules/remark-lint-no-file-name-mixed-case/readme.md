<!--This file is generated-->

# remark-lint-no-file-name-mixed-case

Warn when a file name uses mixed case: both upper- and lower case
characters.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) |  |

## Example

##### `README.md`

###### Out

No messages.

##### `readme.md`

###### Out

No messages.

##### `Readme.md`

###### Out

```text
1:1: Do not mix casing in file names
```

## Install

```sh
npm install remark-lint-no-file-name-mixed-case
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-no-file-name-mixed-case",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-no-file-name-mixed-case readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-no-file-name-mixed-case'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

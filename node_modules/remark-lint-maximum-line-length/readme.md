<!--This file is generated-->

# remark-lint-maximum-line-length

Warn when lines are too long.

Options: `number`, default: `80`.

Ignores nodes that cannot be wrapped, such as headings, tables,
code, and definitions.

Ignores images, links, and inline code if they start before the wrap, end
after the wrap, and there’s no white-space after them.

## Presets

This rule is included in the following presets:

| Preset | Setting |
| ------ | ------- |
| [`remark-preset-lint-markdown-style-guide`](https://github.com/remarkjs/remark-lint/tree/master/packages/remark-preset-lint-markdown-style-guide) | `80` |

## Example

##### `valid-mixed-line-endings.md`

When configured with `10`.

###### In

Note: `␍␊` represents a carriage return and a line feed.

Note: `␊` represents a line feed.

```markdown
0123456789␍␊
0123456789␊
01234␍␊
01234␊
```

###### Out

No messages.

##### `invalid-mixed-line-endings.md`

When configured with `10`.

###### In

Note: `␍␊` represents a carriage return and a line feed.

Note: `␊` represents a line feed.

```markdown
012345678901␍␊
012345678901␊
01234567890␍␊
01234567890␊
```

###### Out

```text
1:13: Line must be at most 10 characters
2:13: Line must be at most 10 characters
3:12: Line must be at most 10 characters
4:12: Line must be at most 10 characters
```

##### `invalid.md`

When configured with `80`.

###### In

```markdown
This line is simply not tooooooooooooooooooooooooooooooooooooooooooooooooooooooo
long.

Just like thiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiis one.

And this one is also very wrong: because the link starts aaaaaaafter the column: <http://line.com>

<http://this-long-url-with-a-long-domain-is-invalid.co.uk/a-long-path?query=variables> and such.

And this one is also very wrong: because the code starts aaaaaaafter the column: `alpha.bravo()`

`alphaBravoCharlieDeltaEchoFoxtrotGolfHotelIndiaJuliettKiloLimaMikeNovemberOscar.papa()` and such.
```

###### Out

```text
4:86: Line must be at most 80 characters
6:99: Line must be at most 80 characters
8:97: Line must be at most 80 characters
10:97: Line must be at most 80 characters
12:99: Line must be at most 80 characters
```

##### `valid.md`

###### In

```markdown
This line is simply not toooooooooooooooooooooooooooooooooooooooooooo
long.

This is also fine: <http://this-long-url-with-a-long-domain.co.uk/a-long-path?query=variables>

<http://this-link-is-fine.com>

`alphaBravoCharlieDeltaEchoFoxtrotGolfHotelIndiaJuliettKiloLimaMikeNovemberOscarPapaQuebec.romeo()`

[foo](http://this-long-url-with-a-long-domain-is-valid.co.uk/a-long-path?query=variables)

<http://this-long-url-with-a-long-domain-is-valid.co.uk/a-long-path?query=variables>

![foo](http://this-long-url-with-a-long-domain-is-valid.co.uk/a-long-path?query=variables)

| An | exception | is | line | length | in | long | tables | because | those | can’t | just |
| -- | --------- | -- | ---- | ------ | -- | ---- | ------ | ------- | ----- | ----- | ---- |
| be | helped    |    |      |        |    |      |        |         |       |       | .    |

The following is also fine, because there is no white-space.

<http://this-long-url-with-a-long-domain-is-invalid.co.uk/a-long-path?query=variables>.

In addition, definitions are also fine:

[foo]: <http://this-long-url-with-a-long-domain-is-invalid.co.uk/a-long-path?query=variables>
```

###### Out

No messages.

## Install

```sh
npm install remark-lint-maximum-line-length
```

## Usage

You probably want to use it on the CLI through a config file:

```diff
 ...
 "remarkConfig": {
   "plugins": [
     ...
     "lint",
+    "lint-maximum-line-length",
     ...
   ]
 }
 ...
```

Or use it on the CLI directly

```sh
remark -u lint -u lint-maximum-line-length readme.md
```

Or use this on the API:

```diff
 var remark = require('remark');
 var report = require('vfile-reporter');

 remark()
   .use(require('remark-lint'))
+  .use(require('remark-lint-maximum-line-length'))
   .process('_Emphasis_ and **importance**', function (err, file) {
     console.error(report(err || file));
   });
```

## License

[MIT](https://github.com/remarkjs/remark-lint/blob/master/LICENSE) © [Titus Wormer](http://wooorm.com)

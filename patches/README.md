# Patches

为了保证与 mkdocs 的兼容性，我们 patch 了 `mdast-util-to-markdown`。具体变化如下

- 使用 2 space style 的 hardbreak
- 避免 escape `&`
- 避免将等号视为 heading

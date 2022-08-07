#!/usr/bin/env bash

set -eo pipefail

shopt -s globstar
wget https://file.mgt.moe/minify-html-cli -O /tmp/minify-html
chmod +x /tmp/minify-html
/tmp/minify-html --keep-closing-tags --minify-css ./site/**/*.html

#!/usr/bin/env bash

set -eo pipefail

shopt -s globstar
wget https://wilsonl.in/minify-html/bin/0.11.1-linux-x86_64 -O /tmp/minify-html
chmod +x /tmp/minify-html
/tmp/minify-html --keep-closing-tags --minify-css ./site/**/*.html

#!/usr/bin/env bash

set -eo pipefail

shopt -s globstar
wget https://github.com/wilsonzlin/minify-html/releases/download/v0.15.0/minhtml-0.15.0-x86_64-unknown-linux-gnu -O /tmp/minify-html
chmod +x /tmp/minify-html
/tmp/minify-html --keep-closing-tags --minify-css ./site/**/*.html

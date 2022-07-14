#!/usr/bin/env bash

set -eo pipefail

DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

"$DIRNAME"/install-theme.sh

git rev-parse --short HEAD | xargs -I % sed -i "s/githash: ''/githash: '%'/g" mkdocs.yml

sed -i "s#  - 'assets/vendor/mathjax/MathJax.js?config=TeX-MML-AM_CHTML'##g" mkdocs.yml

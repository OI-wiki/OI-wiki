#!/usr/bin/env bash

set -eo pipefail

DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

"$DIRNAME"/install-theme.sh

git rev-parse --short HEAD | xargs -I % sed -i "s/githash: ''/githash: '%'/g" mkdocs.yml

if [[ "$PREBUILD_NETLIFY" != "1" ]]; then
    # Will NOT Use Mathjax for Deploy
    sed -i "s#  - 'assets/vendor/mathjax/MathJax.js?config=TeX-MML-AM_CHTML'##g" mkdocs.yml
fi

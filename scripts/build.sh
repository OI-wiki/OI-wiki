#!/usr/bin/env bash
set -euo pipefail
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=24OI
REPO=OI-wiki
# This probably should match an email for one of your users.
EMAIL=sirius.caffrey@gmail.com
INSTALL_THEME='./scripts/install_theme.sh'

chmod +x "$INSTALL_THEME" && "$INSTALL_THEME"

git rev-parse --short HEAD | xargs -I % sed -i "s/githash: ''/githash: '%'/g" mkdocs.yml
#Will NOT Use Mathjax for Deploy
sed -i "s#  - 'assets/vendor/mathjax/MathJax.js?config=TeX-MML-AM_CHTML'##g" mkdocs.yml

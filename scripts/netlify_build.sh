#!/usr/bin/env bash
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=24OI
REPO=OI-wiki
# This probably should match an email for one of your users.
EMAIL=sirius.caffrey@gmail.com
INSTALL_THEME='./scripts/install_theme.sh'

set -e

chmod +x $INSTALL_THEME && $INSTALL_THEME

git rev-parse --short HEAD | xargs -I % sed -i "s/githash: ''/githash: '%'/g" mkdocs.yml
# sed -i "s/- 'https:\/\/cdnjs.loli.net\/ajax\/libs\/mathjax\/2.7.5\/MathJax.js?config=TeX-MML-AM_CHTML'//g" mkdocs.yml

mkdocs build -v

# find ./site -type f -name '*.html' -exec node --max_old_space_size=512 ./scripts/render_math.js {} \;

# find ./site -type f -name "*.html" -exec sed -i -E 's/([^"]*)(assets[^"]*)/https:\/\/cdn-for-oi-wiki.billchn.com\/\2/g' {} +

# npx gulp minify
# try to avoid netlify timeout

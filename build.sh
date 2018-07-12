#!/usr/bin/env bash
# Push HTML files to gh-pages automatically.

# Fill this out with the correct org/repo
ORG=Ir1d
REPO=OI-wiki
# This probably should match an email for one of your users.
EMAIL=sirius.caffrey@gmail.com

set -e

# Clone Theme for Editing
git clone --depth 1 https://github.com/squidfunk/mkdocs-material.git
sed -i "s/name: 'material'/name : null\n  custom_dir: 'mkdocs-material\/material'/g" mkdocs.yml

# Change Google CDN to loli.net
sed -i 's/fonts.gstatic.com/gstatic.loli.net/g' mkdocs-material/material/base.html
sed -i 's/fonts.googleapis.com/fonts.loli.net/g' mkdocs-material/material/base.html

mkdocs build
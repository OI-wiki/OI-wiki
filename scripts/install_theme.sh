#!/usr/bin/env bash

set -e

if [ ! -d "mkdocs-material" ] ; then
  git clone --depth=1 https://github.com/OI-wiki/mkdocs-material.git
fi

bash scripts/install_theme_vendor.sh

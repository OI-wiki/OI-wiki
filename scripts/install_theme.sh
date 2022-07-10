#!/usr/bin/env bash

set -euo pipefail

THEME_NAME="mkdocs-material"
if [ ! -d "$THEME_NAME" ] ; then
  git clone --depth=1 "${THEME_REPO:-https://github.com/OI-wiki/mkdocs-material.git}" "$THEME_NAME"
fi

bash scripts/install_theme_vendor.sh

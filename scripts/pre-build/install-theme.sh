#!/usr/bin/env bash

set -euo pipefail

DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

THEME_NAME="mkdocs-material"
if [ ! -d "$THEME_NAME" ] ; then
  git clone --depth=1 "${THEME_REPO:-https://github.com/OI-wiki/mkdocs-material.git}" "$THEME_NAME"
fi

"$DIRNAME"/install-theme-vendor.sh

#!/usr/bin/env bash

set -eo pipefail

DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

THEME_NAME="mkdocs-material"

# Clear undesired cahces under netlify
if [[ "$PREBUILD_NETLIFY" == "1" ]]; then
  rm -rf -- "$THEME_NAME"
fi

if [ ! -d "$THEME_NAME" ] ; then
  git clone --depth=1 "${THEME_REPO:-https://github.com/OI-wiki/mkdocs-material.git}" "$THEME_NAME"
fi
git -C "$THEME_NAME" log -1

"$DIRNAME"/install-theme-vendor.sh

#!/usr/bin/env bash

set -eo pipefail

DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

THEME_NAME="mkdocs-material"

# Clear undesired cahces under netlify
if [[ "$PREBUILD_NETLIFY" == "1" ]]; then
  rm -rf -- "$THEME_NAME"
fi

git submodule update --init --recursive
git -C "$THEME_NAME" log -1

"$DIRNAME"/install-theme-vendor.sh

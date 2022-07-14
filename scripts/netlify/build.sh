#!/usr/bin/env bash

set -e

DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

source "$DIRNAME"/install-python.sh

# Install dependencies
pipenv install
yarn --frozen-lockfile --production

# Install themes and etc.
PREBUILD_NETLIFY=1 scripts/pre-build/pre-build.sh

pipenv run mkdocs build -v

# Post-build scripts
scripts/post-build/commits-info/render-commits-info.sh
scripts/post-build/minify-html/minify-html.sh

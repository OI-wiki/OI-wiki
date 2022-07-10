#!/usr/bin/env bash

set -e

# Install dependencies
pip install -r requirements.txt
yarn --frozen-lockfile --production

# Install themes and etc.
PREBUILD_NETLIFY=1 scripts/pre-build/pre-build.sh

mkdocs build -v

# Post-build scripts
scripts/post-build/commits-info/render-commits-info.sh

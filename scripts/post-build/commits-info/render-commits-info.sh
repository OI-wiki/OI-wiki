#!/usr/bin/env bash

set -e

REPO="OI-wiki/OI-wiki"
DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

wget "https://raw.githubusercontent.com/$REPO/authors-cache/authors.json" -O "authors.json"

export NODE_OPTIONS='--max-old-space-size=3049'
yarn ts-node-esm "$DIRNAME/update-authors-cache.ts" # Update authors cache (incrementally)
yarn ts-node-esm "$DIRNAME/render-commits-info.ts" site

#!/usr/bin/env bash

set -e

# Install uv if not available (Netlify should have it via pip install uv)
if ! command -v uv &> /dev/null; then
    pip install uv
fi

# Install dependencies
uv sync --index-url ${PYPI_MIRROR:-https://pypi.org/simple/}
yarn --frozen-lockfile --production

# Install themes and etc.
PREBUILD_NETLIFY=1 scripts/pre-build/pre-build.sh

uv run mkdocs build -v

# Post-build scripts
export NODE_OPTIONS="--max_old_space_size=3072"
node --loader ts-node/esm scripts/post-build/html-postprocess.ts commits-info math external-links

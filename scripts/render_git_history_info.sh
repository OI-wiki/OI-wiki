#!/bin/bash -e

wget https://raw.githubusercontent.com/OI-wiki/OI-wiki/authors-cache/authors.json

node scripts/fetch-authors.cjs # Update authors cache (incrementally)
node scripts/html-postprocess.cjs site

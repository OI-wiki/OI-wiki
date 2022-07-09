#!/bin/bash -e

wget https://raw.githubusercontent.com/OI-wiki/OI-wiki/authors-cache/authors.json

node scripts/fetch-authors.js # Update authors cache (incrementally)
node scripts/html-postprocess.js site

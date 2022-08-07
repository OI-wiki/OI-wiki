#!/usr/bin/env bash

set -euo pipefail

DIRNAME="$(dirname -- "${BASH_SOURCE[0]}")"

INPUT_FILE="site/sitemap.xml"
OUTPUT_FILE="$(mktemp "/tmp/sitemap-XXXXXXXX.txt")"
pipenv run python "$DIRNAME/convert-sitemap.py" "$INPUT_FILE" "$OUTPUT_FILE"

URL="http://data.zz.baidu.com/urls?site=$SITE&token=$BAIDU_TOKEN"
curl -H 'Content-Type: text/plain' --data-binary "@$OUTPUT_FILE" "$URL"

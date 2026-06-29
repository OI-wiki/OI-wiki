set -euo pipefail

VENDOR_DIR="mkdocs-material/material/templates/assets/vendor"
rm -rf "$VENDOR_DIR"

function _when_error() {
	echo -e "\nOops! Failed to fetch vendor resources!"
	if [[ -d "$TEMP_DIR" ]]; then
		echo "Check the temp directory: $TEMP_DIR"
	fi
}
trap _when_error ERR

# MathJax (will be removed on production build)
TEMP_DIR="$(mktemp -d -t "download-mathjax-XXXXXXXX")"
MATHJAX_URL=${MATHJAX_URL:-"https://registry.npmjs.org/mathjax/-/mathjax-4.0.0.tgz"}
echo "Downloading MathJax to $TEMP_DIR"
echo "URL: $MATHJAX_URL"
curl "$MATHJAX_URL" | tar -C "$TEMP_DIR" -xzf -
FILE_TARGET_PATH="$VENDOR_DIR/mathjax"
FILE_SOURCE_PATH="$TEMP_DIR/package"
mkdir -p "$(dirname "$FILE_TARGET_PATH")"
cp -r "$FILE_SOURCE_PATH" "$FILE_TARGET_PATH"
rm -rf "$TEMP_DIR"

set -euo pipefail

VENDOR_DIR="mkdocs-material/material/assets/vendor"
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
MATHJAX_URL=${MATHJAX_URL:-"https://registry.npmjs.org/mathjax/-/mathjax-3.2.2.tgz"}
echo "Downloading MathJax to $TEMP_DIR"
echo "URL: $MATHJAX_URL"
MATHJAX_REQUIRED_FILES=(
	"es5"
)
curl "$MATHJAX_URL" | tar -C "$TEMP_DIR" -xzf -
for FILE in "${MATHJAX_REQUIRED_FILES[@]}"; do
	FILE_TARGET_PATH="$VENDOR_DIR/mathjax/$FILE"
	FILE_SOURCE_PATH="$TEMP_DIR/package/$FILE"
	mkdir -p "$(dirname "$FILE_TARGET_PATH")"
	cp -r "$FILE_SOURCE_PATH" "$FILE_TARGET_PATH"
done
rm -rf "$TEMP_DIR"

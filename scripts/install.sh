#!/bin/bash

set -eu -o pipefail

ARCH=$(uname -m)
REPO="ydreiz/xpico"
TAG="${TAG:-}"

case "$ARCH" in
    x86_64)
        FILE_ARCH="x86_64"
        ;;
    aarch64|arm64)
        FILE_ARCH="arm64"
        ;;
    *)
        echo "Not supported architecture: $ARCH"
        exit 1
        ;;
esac


if [ "$TAG" = "" ]; then
    TAG=$(curl -s "https://api.github.com/repos/$REPO/releases/latest" | grep '"tag_name":' | sed -E 's/.*"([^"]+)".*/\1/')
    if [ "$TAG" = "" ]; then
        echo "Error: Unable to retrieve the tag. Please check your connection or enter the tag manually."
        exit 1
    fi
fi

FILENAME="xpico-$FILE_ARCH.tar.gz"
URL="https://github.com/$REPO/releases/download/$TAG/$FILENAME"
INSTALL_DIR="$HOME/.local/bin"
TMP_DIR=$(mktemp -d)

trap 'rm -rf "$TMP_DIR"' EXIT

if ! curl -L --fail "$URL" -o "$TMP_DIR/$FILENAME"; then
    echo "Error: The file could not be downloaded. The tag '$TAG' or the architecture '$FILE_ARCH' may not exist."
    exit 1
fi

tar -xzf "$TMP_DIR/$FILENAME" -C "$TMP_DIR"
mkdir -p "$INSTALL_DIR"

BINARY=$(find "$TMP_DIR" -type f ! -name "*.tar.gz" -executable | head -n 1)
if [ "$BINARY" != "" ]; then
    mv "$BINARY" "$INSTALL_DIR/xpico"
    chmod +x "$INSTALL_DIR/xpico"
    echo "Successfully installed: $INSTALL_DIR/xpico (version $TAG)"
else
    echo "Error: The executable file was not found in the archive."
    exit 1
fi

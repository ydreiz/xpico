#!/bin/bash

set -eu -o pipefail

DIR="$HOME/.local/bin"
EXECUTABLE="xpico"
REMOVE_PATH="$DIR/$EXECUTABLE"

rm -f "$REMOVE_PATH"

echo "Successfully uninstalled: $REMOVE_PATH"

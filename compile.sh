#!/usr/bin/env sh

# Move to the app directory
cd "$(dirname "$(readlink -f "$0")")" || exit

OUTPUT="calc"
SOURCES="src/main.c"

# Compile the app
exec gcc $SOURCES -std=c90 -pedantic -Wall -Wextra -o $OUTPUT "$@"
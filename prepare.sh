#!/bin/sh

set -ue

THIS="$(readlink -f "$0")"
HERE="$(cd "$(dirname "$THIS")"; pwd)"
SRC="$HERE/template.cpp"

for dest in "$@"; do
	cp -nv "$SRC" "$dest"
done

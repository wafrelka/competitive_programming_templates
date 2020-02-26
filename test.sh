#!/bin/bash

set -u
ulimit -c 0

GXX="g++ --std=c++11 -O2 -Wall -Wextra -Wshadow -Wno-unused-result -fsanitize=undefined,address -DWAFDAYO"

src="$1"
dest="./${1%.cpp}.bin"
shift 1

print_log() { echo -e "\e[${2:-}m$1\e[m" >&2; }
print_em() { print_log "$1" "1"; }
print_fail() { print_log "$1" "31;1"; }

if [ ! -f "$dest" ] || [ "$src" -nt "$dest" ]; then
	print_log "===> compiling..."
	$GXX "$src" -o "$dest"
	gxx_ok="$?"
	if [ "$gxx_ok" -ne "0" ]; then
		print_fail "===> compilation failed"
		exit 1
	fi
	print_log "===> compiled"
else
	print_log "===> compilation skipped"
fi

run() {
	in_file="$1"
	name="$2"
	print_em "[$name]"
	if [ "" != "$in_file" ]; then
		"./$dest" < "$in_file"
		ok="$?"
	else
		"./$dest"
		ok="$?"
	fi
	if [ "$ok" -ne "0" ]; then
		print_fail "===> execution failed"
	fi
}

if [ "$#" -ne "0" ]; then
	for in_file in "$@"; do
		run "$in_file" "$in_file"
	done
else
	run "" "stdin"
fi

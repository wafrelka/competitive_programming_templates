#!/bin/bash

set -ue

NODES="4"

if [ $# -lt 2 ]; then
	echo "usage: $0 <problem-name> <header-num>"
	exit 1
fi

name="$1"
num="$2"
prob_dir="../$name"

if [ ! -d "$prob_dir" ]; then
	echo "'$prob_dir' not found"
	exit 1
fi

temp_dir="$(mktemp -d)"
cp "$prob_dir/$name.cpp" "$temp_dir/$name.cpp"
cp "$prob_dir/$name.$num.h" "$temp_dir/$name.h"

exec ./dcj.sh test --source "$temp_dir/$name.cpp" --nodes NODES

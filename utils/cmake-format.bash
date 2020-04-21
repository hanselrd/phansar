#!/usr/bin/env bash

cd "$(git rev-parse --show-toplevel)" || exit

tmpdir=$(mktemp -d -p /tmp cmake-format-XXXXXXXXX)
tmpf=$(mktemp -p "$tmpdir" XXXXXXXXX.fdiff)

check() {
    tmpd=$(mktemp -p "$tmpdir" XXXXXXXXX.diff)
    tmpb=$(mktemp -p "$tmpdir" XXXXXXXXX.before)
    tmpa=$(mktemp -p "$tmpdir" XXXXXXXXX.after)
    echo "$1"
    cat "$1" > "$tmpb"
    cmake-format "$1" > "$tmpa"
    diff -u "$tmpb" "$tmpa" | tee -a "$tmpd"
}

fix() {
    check "$1"
    cmake-format -i "$1"
}

### MAIN

case "$1" in
    check)
        find . -type f -regex './\(CMakeLists.txt\|cmake/.*\.cmake\|\(src\|test\|vendor\)/.*CMakeLists.txt\)$' -print0 |
        while IFS= read -r -d '' file; do
            check "$file"
        done

        find "$tmpdir" -type f -regex '.*\.\(diff\)$' -print0 |
        while IFS= read -r -d '' file; do
            tee -a "$tmpf" < "$file"
        done
        ;;
    fix)
        find . -type f -regex './\(CMakeLists.txt\|cmake/.*\.cmake\|\(src\|test\|vendor\)/.*CMakeLists.txt\)$' -print0 |
        while IFS= read -r -d '' file; do
            fix "$file"
        done
        ;;
    *)
        exit 1
        ;;
esac

cat "$tmpf"
rc=$(wc -l < "$tmpf")
rm -rf "$tmpdir"
exit "$rc"

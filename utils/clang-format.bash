#!/usr/bin/env bash

cd "$(git rev-parse --show-toplevel)" || exit

tmpdir=$(mktemp -d -p /tmp clang-format-XXXXXXXXX)
tmpf=$(mktemp -p "$tmpdir" XXXXXXXXX.fdiff)

check() {
    tmpd=$(mktemp -p "$tmpdir" XXXXXXXXX.diff)
    tmpb=$(mktemp -p "$tmpdir" XXXXXXXXX.before)
    tmpa=$(mktemp -p "$tmpdir" XXXXXXXXX.after)
    echo "$1"
    cat "$1" > "$tmpb"
    clang-format -style=file "$1" > "$tmpa"
    diff -u "$tmpb" "$tmpa" | tee -a "$tmpd"
}

fix() {
    check "$1"
    clang-format --style=file -i "$1"
}

### MAIN

case "$1" in
    check)
        find src tests -type f -regex '.*\.\(hpp\|cpp\|tpp\)' -print0 |
            while IFS= read -r -d '' file; do
                check "$file"
            done

        find "$tmpdir" -type f -regex '.*\.\(diff\)' -print0 |
            while IFS= read -r -d '' file; do
                tee -a "$tmpf" < "$file"
            done
        ;;
    fix)
        find src tests -type f -regex '.*\.\(hpp\|cpp\|tpp\)' -print0 |
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

#!/usr/bin/env bash

cd "$(git rev-parse --show-toplevel)" || exit

tmpdir=$(mktemp -d -p /tmp test-cases-XXXXXXXXX)
tmpf=$(mktemp -p "$tmpdir" XXXXXXXXX.fdiff)

check() {
    tmpd=$(mktemp -p "$tmpdir" XXXXXXXXX.diff)
    tmpb=$(mktemp -p "$tmpdir" XXXXXXXXX.before)
    tmpa=$(mktemp -p "$tmpdir" XXXXXXXXX.after)
    echo "$1"
    cur_ts_name=$(grep "TEST_CASE" < "$1" | head -n 1 | cut -d ',' -f 1)
    new_ts_name=$(grep "TEST_CASE" < "$1" | head -n 1 | cut -d '"' -f 1)'"'$(echo "$1" | cut -d '/' -f 4 | cut -d '.' -f 1)'"'
    cur_ts_tags=$(grep -oE '"\[.*\]"' < "$1" | head -n 1 | sed 's/\[/\\[/g;s/\]/\\]/g')
    new_ts_tags='"['$(echo "$1" | cut -d '/' -f 4 | cut -d '.' -f 1 | sed 's/_/][/;s/_/][/')']"'
    cat "$1" > "$tmpb"
    cat "$1" > "$tmpa"
    sed -i "s/$cur_ts_name/$new_ts_name/g" "$tmpa"
    sed -i "s/$cur_ts_tags/$new_ts_tags/g" "$tmpa"
    diff -u "$tmpb" "$tmpa" | tee -a "$tmpd"
}

fix() {
    check "$1"
    sed -i "s/$cur_ts_name/$new_ts_name/g" "$1"
    sed -i "s/$cur_ts_tags/$new_ts_tags/g" "$1"
}

### MAIN

case "$1" in
    check)
        find src tests vendor -type f -regex '.*\.\(unittest.cpp\)$' -print0 |
            while IFS= read -r -d '' file; do
                check "$file"
            done

        find "$tmpdir" -type f -regex '.*\.\(diff\)$' -print0 |
            while IFS= read -r -d '' file; do
                tee -a "$tmpf" < "$file"
            done
        ;;
    fix)
        find src tests vendor -type f -regex '.*\.\(unittest\.cpp\)$' -print0 |
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

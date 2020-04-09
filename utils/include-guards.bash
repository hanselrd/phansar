#!/usr/bin/env bash

cd "$(git rev-parse --show-toplevel)" || exit

tmpdir=$(mktemp -d -p /tmp include-guards-XXXXXXXXX)
tmpf=$(mktemp -p "$tmpdir" XXXXXXXXX.fdiff)

check() {
    tmpd=$(mktemp -p "$tmpdir" XXXXXXXXX.diff)
    tmpb=$(mktemp -p "$tmpdir" XXXXXXXXX.before)
    tmpa=$(mktemp -p "$tmpdir" XXXXXXXXX.after)
    echo "$1"
    cur_ig=$(grep "#ifndef" < "$1" | head -n 1 | cut -d ' ' -f 2)
    new_ig=$(echo "$1" | cut -d "/" -f 2- | tr ./ _ | tr "[:lower:]" "[:upper:]")
    cat "$1" > "$tmpb"
    cat "$1" > "$tmpa"
    sed -i "s/$cur_ig/$new_ig/g" "$tmpa"
    diff -u "$tmpb" "$tmpa" | tee -a "$tmpd"
}

fix() {
    check "$1"
    sed -i "s/$cur_ig/$new_ig/g" "$1"
}

### MAIN

case "$1" in
    check)
        find src tests vendor -type f -regex '.*\.\(hpp\)$' -print0 |
            while IFS= read -r -d '' file; do
                check "$file"
            done

        find "$tmpdir" -type f -regex '.*\.\(diff\)$' -print0 |
            while IFS= read -r -d '' file; do
                tee -a "$tmpf" < "$file"
            done
        ;;
    fix)
        find src tests vendor -type f -regex '.*\.\(hpp\)$' -print0 |
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

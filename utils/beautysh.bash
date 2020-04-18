#!/usr/bin/env bash

cd "$(git rev-parse --show-toplevel)" || exit

tmpdir=$(mktemp -d -p /tmp beautysh-XXXXXXXXX)
tmpf=$(mktemp -p "$tmpdir" XXXXXXXXX.fdiff)

check() {
    tmpd=$(mktemp -p "$tmpdir" XXXXXXXXX.diff)
    tmpb=$(mktemp -p "$tmpdir" XXXXXXXXX.before)
    tmpa=$(mktemp -p "$tmpdir" XXXXXXXXX.after)
    echo "$1"
    cat "$1" > "$tmpb"
    beautysh -i 4 -s paronly - < "$1" > "$tmpa"
    diff -u "$tmpb" "$tmpa" | tee -a "$tmpd"
}

fix() {
    check "$1"
    beautysh -i 4 -s paronly "$1"
}

### MAIN

case "$1" in
    check)
        find utils -type f -regex '.*\.\(sh\|bash\)$' -print0 |
        while IFS= read -r -d '' file; do
            check "$file"
        done

        find "$tmpdir" -type f -regex '.*\.\(diff\)$' -print0 |
        while IFS= read -r -d '' file; do
            tee -a "$tmpf" < "$file"
        done
        ;;
    fix)
        find utils -type f -regex '.*\.\(sh\|bash\)$' -print0 |
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

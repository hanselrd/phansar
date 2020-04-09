#!/usr/bin/env bash

cd "$(git rev-parse --show-toplevel)" || exit

tmpdir=$(mktemp -d -p /tmp clang-tidy-XXXXXXXXX)
tmpf=$(mktemp -p "$tmpdir" XXXXXXXXX.fdiff)

runclangtidy() {
    clangtidychecks="-*,bugprone-*,-bugprone-lambda-function-name,-bugprone-sizeof-expression,cert-*,clang-analyzer-*,google-explicit-constructor,modernize-*,performance-*,portability-*,readability-*"
    clangtidyheaderfilter=".*"
    clangtidyextraarg="-Wno-unknown-warning-option"
    clangtidyfiles="$PWD/{src,tests,vendor}"

    bash -c "./utils/run-clang-tidy.py -checks=$clangtidychecks -header-filter=$clangtidyheaderfilter -extra-arg=$clangtidyextraarg $* $clangtidyfiles"
}

### MAIN

case "$1" in
    check)
        runclangtidy -export-fixes="$tmpf"
        ;;
    fix)
        runclangtidy -fix -format
        ;;
    *)
        exit 1
        ;;
esac

cat "$tmpf"
rc=$(wc -l < "$tmpf")
rm -rf "$tmpdir"
exit "$rc"

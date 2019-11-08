#!/usr/bin/env sh

cd $(git rev-parse --show-toplevel)
tmpd=$(mktemp) # diff
tmpb=$(mktemp) # before
tmpa=$(mktemp) # after
find src/ tests/ -type f -regex '.*\.\(hpp\|cpp\|tpp\)' -print0 |
    while IFS= read -r -d '' file; do
        echo $file
        cat $file > $tmpb
        clang-format -style=file $file > $tmpa
        diff -u $tmpb $tmpa | tee -a $tmpd
    done
cat $tmpd
exit $(cat $tmpd | wc -l)

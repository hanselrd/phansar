#!/usr/bin/env sh

cd $(git rev-parse --show-toplevel)
tmpd=$(mktemp) # diff
tmpb=$(mktemp) # before
tmpa=$(mktemp) # after
find src/ tests/ -type f -regex '.*\.\(hpp\)' -print0 |
    while IFS= read -r -d '' file; do
        echo $file
        cur_ig=$(cat $file | grep "#ifndef" | head -n 1 | cut -d ' ' -f 2)
        new_ig=$(echo $file | cut -d "/" -f 2- | tr ./ _ | tr [a-z] [A-Z])
        cat $file > $tmpb
        cat $file > $tmpa
        sed -i "s/$cur_ig/$new_ig/g" $tmpa
        diff -u $tmpb $tmpa | tee -a $tmpd
    done
cat $tmpd
exit $(cat $tmpd | wc -l)

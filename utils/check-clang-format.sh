#!/usr/bin/env sh

cd $(git rev-parse --show-toplevel)
tmpd=$(mktemp) # diff
tmpu=$(mktemp) # unformatted
tmpf=$(mktemp) # formatted
find src/ tests/ -type f -regex '.*\.\(hpp\|cpp\|tpp\)' -print0 \
    | xargs -0 -I{} sh -c "echo {}; cat {} > $tmpu; clang-format -style=file {} > $tmpf; diff -u $tmpu $tmpf | tee -a $tmpd"
cat $tmpd
exit $(cat $tmpd | wc -l)

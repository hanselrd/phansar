#!/usr/bin/env sh

tmpfile_unformatted=$(mktemp)
tmpfile_formatted=$(mktemp)
find src/ -regex '.*\.\(hpp\|cpp\|tpp\)' -exec cat {} \; > $tmpfile_unformatted
find src/ -regex '.*\.\(hpp\|cpp\|tpp\)' -exec clang-format -style=file {} \; > $tmpfile_formatted
diff -u $tmpfile_unformatted $tmpfile_formatted

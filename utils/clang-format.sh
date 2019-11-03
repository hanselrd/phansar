#!/usr/bin/env sh

find src/ -regex '.*\.\(hpp\|cpp\|tpp\)' -exec clang-format -style=file -i {} \;

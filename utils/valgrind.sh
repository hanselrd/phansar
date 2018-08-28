#!/usr/bin/env sh

valgrind --leak-check=full --track-origins=yes --show-reachable=yes ${1}

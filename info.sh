#!/usr/bin/env sh

echo "Number of unique words: "
cat out | tr " " "\n" | sort | uniq -c | wc -l | tr -d " "

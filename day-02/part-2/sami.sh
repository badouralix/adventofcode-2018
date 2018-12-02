#!/usr/bin/env bash

input=($(echo $1 | tr ' ' '\n'))
length=${#input[0]}

for i in $(seq 1 $((length - 2))); do
    res=$(echo "${input[@]}" | tr ' ' '\n' | cut -c -$i,$(($i+2))- | sort | uniq -c | grep 2)
    if [[ -n $res ]]; then
        echo $res | cut -f2 -d' '
        exit 0
    fi
done

echo "NOT FOUND"
exit 1

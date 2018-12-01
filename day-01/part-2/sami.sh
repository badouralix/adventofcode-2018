#!/usr/bin/env bash

result=0
declare -A seen
input=$1

while true;
do
    for delta in $input; do
        result=$(($result + $delta))

        if [[ -z "${seen["$result"]}" ]]; then
            seen["$result"]="ok"
        else
            echo "$result"
            exit 0
        fi
    done
done

echo "NOT FOUND"
exit 1

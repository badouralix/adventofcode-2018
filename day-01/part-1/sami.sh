#!/bin/bash

result=0
while read line
do
    result=$(($result + $line))
done < "${1:-/dev/stdin}"

echo $result

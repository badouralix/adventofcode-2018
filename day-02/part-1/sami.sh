#!/usr/bin/env bash

# Returns two_occur_found, three_occyr_found
count_occur() {
    local counter
    local two=0
    local three=0
    local c
    declare -A counter
    for i in $(seq 1 ${#1}); do
        c="${1:$i-1:1}"

        # Increment the counter for this char
        counter[$c]=$((${counter[$c]:-0} + 1))
    done

    for i in "${!counter[@]}"
    do
        case ${counter[$i]} in
            2)
                two=1
                ;;
            3)
                three=1
                ;;
        esac
    done

    echo $two $three
}

checksum() {
    echo $(($1 * $2))
}

input=$1
two_count=0
three_count=0

for word in $input; do
    case $(count_occur $word) in
        "1 0")
            two_count=$(($two_count + 1))
            ;;
        "0 1")
            three_count=$(($three_count + 1))
            ;;
        "1 1")
            two_count=$(($two_count + 1))
            three_count=$(($three_count + 1))
            ;;
    esac
done

checksum $two_count $three_count

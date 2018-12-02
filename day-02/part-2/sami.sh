#!/usr/bin/env bash

# Returns the common chars for the given two words if they have only one different char
# Otherwise returns an empty string
compare_words() {
    local c1
    local c2
    local error
    local common

    for i in $(seq 1 ${#1}); do
        c1="${1:$i-1:1}"
        c2="${2:$i-1:1}"

        if [[ $c1 == $c2 ]]; then
            common+=$c1
            # We already saw one error
        elif [[ $c1 != $c2 ]] && [[ -n $error ]]; then
            return
        else [[ $c1 != $c2 ]]
            error=1
        fi
    done

    echo $common
}


input=$1

for w1 in $input; do
    for w2 in $input; do
        # Make sure we don't process twice the same pair of words
        if [[ $w2 > $w1 ]]; then
            common=$(compare_words $w1 $w2)
            if [[ -n $common ]]; then
                echo $common
                exit 0
            fi
        fi
    done
done

echo "NOT FOUND"
exit 1

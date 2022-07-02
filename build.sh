#!/bin/bash

set -ev

# source $HOME/.cargo/env
export PATH=$PATH:~/.cargo/bin:$GOROOT/bin
export PYENV_VERSION=3.8

run_from_diff() {
    echo "$1" | grep "day-" | cut -d "/" -f1 | cut -d "-" -f2 | sort | uniq | xargs -I{} ./aoc run -fntd {}
}

run_from_inputs() {
    for day in $1; do echo "$day"; done | sort | uniq | xargs -I{} ./aoc run -fntd {}
}

# Note: we cannot use "git branch --show-current" as GitHub rewrites the history in actions
if [ "$GITHUB_EVENT_NAME" == "workflow_dispatch" ];
then
    run_from_inputs "$INPUT_DAYS"
elif [ "$GITHUB_EVENT_NAME" == "pull_request" ];
then
    # Check the diff with master
    run_from_diff "$(git --no-pager diff --name-only origin/master --)"
else
    # Check the diff of the last commit
    run_from_diff "$(git --no-pager diff --name-only HEAD HEAD^ --)"
fi

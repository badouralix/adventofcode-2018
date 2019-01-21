#!/bin/bash

set -ev

# Install Rust if not present via cache
if [ ! -d $HOME/.cargo/bin ] || [ ! -d $HOME/.rustup/ ]
then
    curl https://sh.rustup.rs -sSf -o rustup.sh
    sh rustup.sh -y
fi
export PATH=$PATH:~/.cargo/bin

export PYENV_VERSION=3.7

npm install
pip install --user -r requirements.txt
git --no-pager diff --name-only HEAD^ | grep "day-" | cut -d "/" -f1 | cut -d "-" -f2 | sort | uniq | xargs -I{} ./aoc run -fd {}

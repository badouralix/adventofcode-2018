#!/bin/bash

set -ev

npm install
pip install -r requirements.txt

git --no-pager diff --name-only ${TRAVIS_COMMIT_RANGE} | grep "day-" | cut -d "/" -f1 | cut -d "-" -f2 | sort | uniq | xargs -I{} python run.py -fd {}

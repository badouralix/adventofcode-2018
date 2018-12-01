# Advent of code 2018 submissions

⁣    🌟  
    🎄  
   🎄🎄  
  🎄🎄🎄  
 🎄🎄🎄🎄  
🎄🎄🎄🎄🎄  
  🎁🎁🎁  

These are proposed submissions for the [Advent of Code 2018](http://adventofcode.com/2018).

The solutions are automatically tested with travis.

[![Build Status](https://travis-ci.org/badouralix/advent-of-code-2018.svg?branch=master)](https://travis-ci.org/badouralix/advent-of-code-2018)

## Usage

To run submissions use `run.py` script

```text
usage: run.py [-h] [--last] [-d DAY] [-p PART] [-a AUTHORS] [-i IGNORE]
              [-l LANGUAGES] [-f] [-r] [-s]

Run contest submissions

optional arguments:
  -h, --help            show this help message and exit
  --last                Run submissions from last day
  -d DAY, --day DAY     Run submissions for specific day
  -p PART, --part PART  Run submissions for specific day part
  -a AUTHORS, --authors AUTHORS
                        Run submissions from specific authors, ex: user1,user2
  -i IGNORE, --ignore IGNORE
                        Ignore submissions from specific authors
  -l LANGUAGES, --languages LANGUAGES
                        Run submissions written in specific languages, ex:
                        js,py, supported: c cpp go js py rb rs
  -f, --force           Force running submissions even if tool is missing
  -r, --restricted      Restrict each author to their input only
  -s, --silent          Disable debug mode
```

## Contribute

For now we support `c`, `c++`, `javascript`, `go`, `python 3`, `ruby`, and `rust (stable)`.

You can use `create.py` tool to create a new empty submission:

```text
usage: create.py [-h] [-p {1,2}] [-l {c,cpp,go,js,py,rb,rs}] author day

Creates new empty submission

positional arguments:
  author                Name of author (github login)
  day                   Day of problem (between 1 and 25)

optional arguments:
  -h, --help            show this help message and exit
  -p {1,2}, --part {1,2}
                        Create submission for one day part only
  -l {c,cpp,go,js,py,rb,rs}, --language {c,cpp,go,js,py,rb,rs}
                        Use specified language
```

### Using python

If you don't use `create.py` tool you should follow this convention:

```bash
day-[number]/part-[number]/[your_login].py          # your submission code
day-[number]/part-[number]/inputs/[your_login].txt  # your input file
```

Your submission code should inherit from the `SubmissionPy` class from `runners.python` module:

```python
from runners.python import SubmissionPy

class MyAwesomeSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
```

You can add other functions & modules if you need to. Any external dependency should be added to `requirements.txt`.

## History

- [Advent of Code 2017](https://github.com/lypnol/adventofcode-2017)
- [Advent of Code 2016](https://github.com/lypnol/adventofcode-2016)

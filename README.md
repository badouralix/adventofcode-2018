# Advent of code 2018 solutions

⁣    🌟  
    🎄  
   🎄🎄  
  🎄🎄🎄  
 🎄🎄🎄🎄  
🎄🎄🎄🎄🎄  
  🎁🎁🎁  

These are proposed solutions for the [Advent of Code 2018](http://adventofcode.com/2018).

The solutions are automatically tested with travis.

[![Build Status](https://travis-ci.org/badouralix/advent-of-code-2018.svg?branch=master)](https://travis-ci.org/badouralix/advent-of-code-2018)

## Usage

use `./aoc` script

```text
usage: aoc <command> [<args>]

aoc commands are:
   run      Runs submissions
   create   Creates a new submission
   config   Configures user's parameters
```

### Examples

**Run last problem**

```
./aoc run
```

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Running submissions for day 04:

* part 2:
---------------------------------------------------
Avg over all inputs
---------------------------------------------------
----------  ----------  -----------  ---
silvestre      78452        1.99 ms  py
degemer        43695        2.39 ms  py
jules          23037        2.49 ms  py
david          36371        2.94 ms  py
thomas          9763        2.97 ms  py
ayoub         136461        5.85 ms  cpp
evqna          49137        6.65 ms  cpp
badouralix     51232        7.26 ms  go
tpxp           41668      133.63 ms  rb
----------  ----------  -----------  ---
```

**Run specific problems from specific users**

```
./aoc run -d 1 -d 2 -p 1 -a ayoub -a david
```

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Running submissions for day 01:

* part 1:
---------------------------------------------------
Avg over all inputs
---------------------------------------------------
-----  -------  -----------  ---
david    543        0.46 ms  py
ayoub    445        4.94 ms  cpp
-----  -------  -----------  ---
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Running submissions for day 02:

* part 1:
---------------------------------------------------
Avg over all inputs
---------------------------------------------------
-----  --------  -----------  ---
david    5658        1.22 ms  py
ayoub    6448        4.84 ms  cpp
-----  --------  -----------  ---
```

You can use `-r` to run each submission on it's own input, or `-e` to print non-aggregated results.  
see `./aoc run -h` for full arguments description.

## Contribute

For now we support `c`, `c++`, `javascript`, `go`, `python 3`, `ruby`, `rust (stable)` and `bash` scripts.

You can use `./aoc create` tool to create a new empty submission:

```text
usage: aoc create [-h] [-a AUTHOR] [-d DAY] [-p PART]
                  [-l {c,cpp,go,js,py,rb,rs,sh}]

Create a new submission

optional arguments:
  -a AUTHOR, --author AUTHOR
                        submission author
  -d DAY, --day DAY     problem day
  -p PART, --part PART  problem part
  -l {c,cpp,go,js,py,rb,rs,sh}, --language {c,cpp,go,js,py,rb,rs,sh}
                        submission language
```

you can also use `./aoc config` to setup your local profile
```text
usage: aoc config [-h] username {c,cpp,go,js,py,rb,rs,sh}

Configures user parameters

positional arguments:
  username              prefered username
  {c,cpp,go,js,py,rb,rs,sh}
                        prefered programming language
```

### Using python

If you don't use `create.py` tool you should follow this convention:

```bash
day-[number]/part-[number]/[username].py    # your submission code
day-[number]/input/[username].txt           # your input file
```

Your submission code should inherit from the `SubmissionPy` class from `runners.python` module:

```python
from tool.runners.python import SubmissionPy

class MyAwesomeSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
```

You can add other functions & modules if you need to. Any external dependency should be added to `requirements.txt`.

Once you tested your solution you can submit it by making a PR.

## History

- [Advent of Code 2017](https://github.com/lypnol/adventofcode-2017)
- [Advent of Code 2016](https://github.com/lypnol/adventofcode-2016)

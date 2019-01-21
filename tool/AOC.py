#!/usr/bin/env python3

import argparse
import sys

from tool.config import config, CONFIG
from tool.run import run
from tool.create import create
import tool.discovery as discovery
from tool.utils import to_ints

COMMAND_RUN = "run"
COMMAND_CREATE = "create"
COMMAND_CONFIG = "config"

SUPPORTED_LANGUAGES = discovery.get_supported_languages()

DAY_RANGE = [i for i in range(1, 26)]
PART_RANGE = [1, 2]


class AOC(object):

    def __init__(self):
        parser = argparse.ArgumentParser(
            description='Advent of code solutions tool',
            usage='''aoc <command> [<args>]

aoc commands are:
   {}      Runs submissions
   {}   Creates a new submission
   {}   Configures user's parameters
'''.format(COMMAND_RUN, COMMAND_CREATE, COMMAND_CONFIG))
        parser.add_argument('command', help='Command to run', choices=[COMMAND_RUN, COMMAND_CREATE, COMMAND_CONFIG])
        args = parser.parse_args(sys.argv[1:2])
        getattr(self, args.command)(sys.argv[2:])

    @staticmethod
    def run(argv):
        parser = argparse.ArgumentParser(
            prog='aoc run',
            description='Runs submissions')
        parser.add_argument("-d", "--day", help="problem day", action="append")
        parser.add_argument("-p", "--part", help="problem part", action="append")
        parser.add_argument("-a", "--author", help="restrict to author", action="append")
        parser.add_argument("-i", "--ignore-author", help="ignore author", action="append")
        parser.add_argument("-r", "--restricted", help="run each submission on its own input only", action="store_true", default=False)
        parser.add_argument("-e", "--expand", help="prints non-aggregated results on all inputs", action="store_true", default=False)
        parser.add_argument("-l", "--language", help="submission language", action="append", choices=SUPPORTED_LANGUAGES)
        parser.add_argument("-f", "--force", help="force running submissions even if language is not supported", action="store_true", default=False)
        parser.add_argument("-s", "--silent", help="disable debug mode", action="store_true", default=False)
        parser.add_argument("--all", help="runs all submissions of all days all parts", action="store_true", default=False)

        args = parser.parse_args(argv)

        run(to_ints(args.day), to_ints(args.part), args.author, args.ignore_author, args.language, args.force, args.silent, args.all, args.restricted, args.expand)

    @staticmethod
    def create(argv):
        parser = argparse.ArgumentParser(
            prog='aoc create',
            description='Create a new submission')
        parser.add_argument("-a", "--author", help="submission author", type=str, default=CONFIG.user)
        parser.add_argument("-d", "--day", help="problem day", type=int)
        parser.add_argument("-p", "--part", help="problem part", type=int)
        parser.add_argument("-l", "--language", help="submission language", type=str, choices=SUPPORTED_LANGUAGES, default=CONFIG.language)

        args = parser.parse_args(argv)
        create(args.day, args.part, args.author, args.language)

    @staticmethod
    def config(argv):
        parser = argparse.ArgumentParser(
            prog='aoc config',
            description='Configures user parameters')
        parser.add_argument("username", help="prefered username", type=str)
        parser.add_argument("language", help="prefered programming language", type=str, choices=SUPPORTED_LANGUAGES)

        args = parser.parse_args(argv)
        config(args.username, args.language)

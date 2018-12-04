#!/usr/bin/env python3

# stdlib
import argparse
import datetime
import glob
import inspect
import os.path
import sys
import traceback

from importlib.machinery import SourceFileLoader
from os import walk

# submissions
from runners.bash import SubmissionBash
from runners.c import SubmissionC
from runners.cpp import SubmissionCpp
from runners.go import SubmissionGo
from runners.js import SubmissionJs
from runners.python import SubmissionPy
from runners.ruby import SubmissionRb
from runners.rust import SubmissionRs
from runners.wrapper import SubmissionWrapper

# utils
from tabulate import tabulate
from utils import is_tool, tool_for_lang


show_debug = True
author_list = None
language_list = None
except_list = None
forced_mode = False
restricted_mode = False


DAY_PATH_PATTERN = 'day-[0-9]*'
CONTEST_PATH_PATTERN = 'part-[0-9]*'
ALLOWED_EXT = ['.c', '.cpp', '.go', '.js', '.py', '.rb', '.rs', '.sh']
SUPPORTED_LANGUAGES = [ext[1:] for ext in ALLOWED_EXT if is_tool(tool_for_lang(ext[1:]))]


# To print colors in terminal
class bcolors:
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


class DifferentAnswersException(Exception):
    pass


def _context_name(context_path):
    return context_path.replace('/', '_').replace('-', '_')


# Return the list of the contests
# It should be the list of the directories matching day-<a number>
def _get_days():
    return sorted(glob.glob(DAY_PATH_PATTERN), key=lambda x: abs(int(x[-2:])))


# Return the list of the contests path for the given day path
def _get_contests_path_for_day(day_path):
    return sorted(glob.glob(day_path + '/' + CONTEST_PATH_PATTERN), key=lambda x: abs(int(x[-1:])))


# Return contest number from path
def _get_constest_number(contest_path):
    return int(contest_path.split('-')[-1])


# Returns the lists of possible submission files for the given contest
def _find_submissions_for_contest(contest_path):
    submission_files = []
    for _, _, files in walk(contest_path):
        for filename in files:
            submission, ext = os.path.splitext(filename)
            if ext in ALLOWED_EXT:
                submission_files.append((submission, ext))
    return submission_files


def _load_submission(contest_path, submission, ext='.py'):
    global language_list
    if ext not in ALLOWED_EXT:
        return None
    submission_path = '%s/%s%s' % (contest_path, submission, ext)
    contest = _context_name(contest_path)
    submission_module = None
    if language_list is not None and ext[1:] not in language_list:
        return None
    if ext == '.py':
        return SubmissionPy(submission_path)
    elif ext == '.c' and (forced_mode or is_tool('gcc')):
        return SubmissionC(submission_path)
    elif ext == '.cpp' and (forced_mode or is_tool('g++')):
        return SubmissionCpp(submission_path)
    elif ext == '.go' and (forced_mode or is_tool('go')):
        return SubmissionGo(submission_path)
    elif ext == '.js' and (forced_mode or is_tool('node')):
        return SubmissionJs(submission_path)
    elif ext == '.rb' and (forced_mode or is_tool('ruby')):
        return SubmissionRb(submission_path)
    elif ext == '.rs' and (forced_mode or is_tool('cargo')):
        return SubmissionRs(submission_path)
    elif ext == '.sh':
        return SubmissionBash(submission_path)
    return None


def load_submissions_for_contest(contest_path):
    submission_files = _find_submissions_for_contest(contest_path)
    submissions = []
    for submission_file, ext in submission_files:
        author = os.path.basename(submission_file).split('.')[0]
        submission = None
        try:
            submission = _load_submission(contest_path, submission_file, ext)
        except Exception:
            if show_debug:
                print(bcolors.RED + ''.join(traceback.format_exc()) + bcolors.ENDC, file=sys.stderr)
                sys.exit(1)
        if submission is not None:
            submissions.append((author, submission))
    return submissions


def get_inputs_for_contest(contest_path):
    if not os.path.exists(os.path.join(contest_path, '..', 'input')):
        return []
    inputs = []
    for input_file in glob.glob(contest_path + '/../input/*.txt'):
        with open(input_file, 'r') as content_file:
            input_name = os.path.os.path.basename(input_file).split('.')[0].lower()
            inputs.append((input_name, content_file.read().rstrip()))
    return inputs


def _run_submission(author, submission, input):
    result = None
    try:
        result = submission.run(input)
    except Exception:
        if show_debug:
            print(bcolors.RED + "Error for author " + author + bcolors.ENDC, file=sys.stderr)
            print(bcolors.RED + ''.join(traceback.format_exc()) + bcolors.ENDC, file=sys.stderr)
            if len(submission.get_debug_stack()) > 0:
                print(bcolors.RED + "Debug trace for %s " % author, file=sys.stderr)
                stack = submission.get_debug_stack()
                print('\n'.join(submission.get_debug_stack()[:15]), file=sys.stderr)
                if len(stack) > 15:
                    print('and %s other lines...' % (len(stack) - 15), file=sys.stderr)
                print(bcolors.ENDC)
            sys.exit(1)
    return result


def _sort_leaderboard(table):
    return sorted(table, key=lambda r: r[2])


def run_submissions_for_contest(contest_path):
    print("\n" + bcolors.MAGENTA + bcolors.BOLD + "* contest %s:" % os.path.basename(contest_path) + bcolors.ENDC)
    submissions = load_submissions_for_contest(contest_path)
    inputs = get_inputs_for_contest(contest_path)
    table = []
    try:
        for input_author, input_content in inputs:
            prev_ans = None
            if not restricted_mode:
                print("---------------------------------------------------")
                print("On input from {yellow}{author}{end}".format(
                    yellow=bcolors.YELLOW,
                    end=bcolors.ENDC,
                    author=input_author))
                print("---------------------------------------------------")
                table = []
            for author, submission in submissions:
                time_before = datetime.datetime.now()
                if restricted_mode and author != input_author:
                    continue
                if author_list is not None and author not in author_list:
                    continue
                if except_list is not None and author in except_list:
                    continue
                answer = _run_submission(author, submission, input_content)
                time_after = datetime.datetime.now()
                msecs = (time_after - time_before).total_seconds() * 1000
                table.append([
                    "  {green}{author}{end}  ".format(green=bcolors.GREEN, author=author, end=bcolors.ENDC),
                    "  {blue}{answer}{end}  ".format(blue=bcolors.BLUE, answer=answer, end=bcolors.ENDC),
                    "  {msecs:8.2f} ms".format(msecs=msecs)
                ])
                table[-1].append(submission.language())

                if prev_ans is not None and prev_ans != str(answer):
                    raise DifferentAnswersException("we don't agree for {}".format(contest_path))
                prev_ans = str(answer)
            if not restricted_mode:
                print(tabulate(_sort_leaderboard(table)))
        if restricted_mode:
            print(tabulate(_sort_leaderboard(table)))
    except DifferentAnswersException as e:
        print(tabulate(_sort_leaderboard(table)))
        print(bcolors.RED, "ERROR", e, bcolors.ENDC, file=sys.stderr)
        sys.exit(1)


def run_submissions_for_day(day, day_path, part=None):
    first_run = True
    contest_paths = _get_contests_path_for_day(day_path)
    for contest_path in contest_paths:
        if part is not None and _get_constest_number(contest_path) != part:
            continue
        if except_list is not None and day in except_list:
            continue

        if first_run:
            print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
            print(bcolors.RED + bcolors.BOLD + "Running submissions for day %s:" % day + bcolors.ENDC)
            first_run = False

        run_submissions_for_contest(contest_path)
        print("\n")


def run_submissions():
    for day_path in _get_days():
        day = day_path[4:]
        run_submissions_for_day(day, day_path)


def main():
    global show_debug
    global author_list
    global language_list
    global except_list
    global forced_mode
    global restricted_mode

    day = None
    part = None

    parser = argparse.ArgumentParser(description='Run contest submissions')
    parser.add_argument("--last", help="Run submissions from last day", action="store_true")
    parser.add_argument("-d", "--day", help="Run submissions for specific day", type=int)
    parser.add_argument("-p", "--part", help="Run submissions for specific day part", type=int)
    parser.add_argument("-a", "--authors", help="Run submissions from specific authors, ex: user1,user2", type=str)
    parser.add_argument("-i", "--ignore", help="Ignore submissions from specific authors", type=str)
    parser.add_argument("-l", "--languages", help="Run submissions written in specific languages, ex: js,py, supported: " + " ".join(SUPPORTED_LANGUAGES), type=str)
    parser.add_argument("-f", "--force", help="Force running submissions even if tool is missing", action="store_true", default=False)
    parser.add_argument("-r", "--restricted", help="Restrict each author to their input only", action="store_true", default=False)
    parser.add_argument("-s", "--silent", help="Disable debug mode", action="store_true")
    args = parser.parse_args()

    restricted_mode = args.restricted
    show_debug = not args.silent

    if args.last:
        day = int(_get_days()[-1][4:])
    elif args.day:
        day = args.day

    if args.part:
        part = args.part

    if args.authors:
        author_list = args.authors.split(',')

    if args.ignore:
        except_list = args.ignore.split(',')

    if args.force:
        forced_mode = True

    if args.languages:
        language_list = args.languages.split(',')
        if any(l not in SUPPORTED_LANGUAGES for l in language_list):
            print(bcolors.RED, "ERROR", "Language not supported", bcolors.ENDC, file=sys.stderr)
            sys.exit(1)

    if day is None and part is not None:
        for day_path in _get_days():
            day = day_path[4:]
            run_submissions_for_day(day, day_path, part)
    elif day is None and part is None:
        # Full test
        run_submissions()
    elif part is None:
        run_submissions_for_day(day, 'day-%02d' % day)
    else:
        run_submissions_for_day(day, 'day-%02d' % day, part)


if __name__ == "__main__":
    main()

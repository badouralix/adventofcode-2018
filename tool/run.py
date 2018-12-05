#!/usr/bin/env python3

# stdlib
import sys
import datetime
from collections import defaultdict
from tabulate import tabulate
# project
import tool.discovery as discovery
from tool.config import CONFIG
from tool.model import Result
from tool.utils import BColor


class DifferentAnswersException(Exception):
    pass


def run(days, parts, authors, ignored_authors, languages, force, silent, all_days_parts, restricted, expand):
    problems = discovery.get_problems(days, parts, all_days_parts)
    printed_day_header = set()
    errors = []

    for problem in problems:
        if problem.day not in printed_day_header:
            printed_day_header.add(problem.day)
            print_day_header(problem)
        print_part_header(problem)

        submissions = discovery.get_submissions(problem, authors, ignored_authors, languages, force)
        inputs = discovery.get_inputs(problem)

        results_by_author = defaultdict(dict)
        results_by_input = defaultdict(dict)

        for input in inputs:
            previous = None
            for submission in submissions:
                if restricted and input.author != submission.author:
                    continue
                try:
                    result = run_submission(problem, submission, input, previous)
                    results_by_author[submission.author][input.author] = result
                    results_by_input[input.author][submission.author] = result
                    previous = result
                except Exception as e:
                    errors.append(
                        "{}ERROR: {}{}".format(BColor.RED, e, BColor.ENDC))
        if restricted:
            print_restrict_results(problem, results_by_author)
        elif expand:
            print_expanded_results(problem, results_by_input)
        else:
            print_aggregated_results(problem, results_by_author)

    for err in errors:
        print(err, file=sys.stderr)
    if errors:
        exit(1)


def run_submission(problem, submission, input, previous=None):
    start = datetime.datetime.now()
    answer = str(submission.runnable.run(input.content))
    end = datetime.datetime.now()
    msecs = (end - start).total_seconds() * 1000
    if previous is not None and answer != previous.answer:
        raise DifferentAnswersException("""different answers day:{} part:{}
input: {}
{}: {}
{}: {}""".format(
            problem.day,
            problem.part,
            input.path(),
            previous.submission.path(),
            previous.answer,
            submission.path(),
            answer))
    return Result(problem, submission, input, answer, msecs)


def print_results(results):
    results.sort(key=lambda x: x.duration)
    print(tabulate([[

        "  {color}{author}{end}  ".format(
            color=(BColor.BOLD if result.submission.author == CONFIG.user else BColor.GREEN),
            author=result.submission.author,
            end=BColor.ENDC),

        "  {color}{answer}{end}  ".format(
            color=(BColor.BOLD if result.submission.author == CONFIG.user else BColor.BLUE),
            answer=result.answer,
            end=BColor.ENDC),

        "  {color}{msecs:8.2f} ms{end}".format(
            color=BColor.BOLD,
            msecs=result.duration,
            end=BColor.ENDC),

        "  {color}{language}{end}".format(
            color=(BColor.BOLD if result.submission.author == CONFIG.user else ""),
            language=result.submission.language,
            end=BColor.ENDC,
        )
    ] for result in results]))


def print_expanded_results(problem, results_by_input):
    for input_author, submission_results in results_by_input.items():
        print("---------------------------------------------------")
        print("On input from {yellow}{author}{end}".format(
            yellow=BColor.YELLOW,
            end=BColor.ENDC,
            author=input_author))
        print("---------------------------------------------------")
        results = []
        for author, result in submission_results.items():
            results.append(result)
        print_results(results)


def print_restrict_results(problem, results_by_author):
    print("---------------------------------------------------")
    print("On own inputs")
    print("---------------------------------------------------")
    results = []
    for author, results_by_input in results_by_author.items():
        results.append(results_by_input[author])
    print_results(results)


def print_aggregated_results(problem, results_by_author):
    print("---------------------------------------------------")
    print("Avg over all inputs")
    print("---------------------------------------------------")
    results = []
    for author, results_by_input in results_by_author.items():
        res = Result(problem, None, None, None, 0)
        for input_author, result in results_by_input.items():
            res.duration += result.duration
            if author == input_author:
                res.answer = result.answer
                res.input = result.input
                res.submission = result.submission
        if len(results_by_input) > 0:
            res.duration /= len(results_by_input)
        results.append(res)
    print_results(results)


def print_day_header(problem):
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print(BColor.RED + BColor.BOLD + "Running submissions for day %02d:" % problem.day + BColor.ENDC)


def print_part_header(problem):
    print("\n" + BColor.MAGENTA + BColor.BOLD + "* part %d:" % problem.part + BColor.ENDC)
